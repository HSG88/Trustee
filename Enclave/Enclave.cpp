#include <stdio.h>
#include <stdarg.h>
#include<vector>
#include "Enclave_t.h"
#include "Enclave.h"
#include "sgx_trts.h"
#include "sgx_tcrypto.h"
#include "sgx_tseal.h"
#include "mbedtls/bignum.h"
#include "mbedtls/ecdsa.h"
#include "mbedtls/ecdh.h"
#include "keccak.h"
#include "debug.h"
#include "Log.h"
#include"glue.h"

static mbedtls_ecdsa_context ctxDSA;
static mbedtls_ecdh_context ctxDH;
static bool isLoaded =false;
void Dump(char* title, uint8_t *input, size_t size)
{
	printf_sgx("%s\n", title);
	for (int i = 0; i < size; i++)
		printf_sgx("%02X", input[i]);
	printf_sgx("\n");
}
uint32_t Decrypt(BID bid)
{
	uint8_t key[32];
	uint32_t value = 0;
	//compute shared
	mbedtls_mpi_read_binary(&ctxDH.Qp.X, bid.publicKey, sizeof(bid.publicKey));
	mbedtls_mpi_lset(&ctxDH.Qp.Z, 1);
	mbedtls_ecdh_compute_shared(&ctxDH.grp, &ctxDH.z, &ctxDH.Qp, &ctxDH.d, NULL, NULL);
	mbedtls_mpi_write_binary(&ctxDH.z, key, 32);

	sgx_rijndael128GCM_decrypt(
		(sgx_aes_gcm_128bit_key_t*)&key,
		bid.cipher + SGX_AESGCM_MAC_SIZE + SGX_AESGCM_IV_SIZE,
		sizeof(value),
		(uint8_t*)&value,
		bid.cipher + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE,
		NULL, 0,
		(sgx_aes_gcm_128bit_tag_t *)bid.cipher);
	return value;
}
void Sign(const uint8_t *data, size_t in_len, uint8_t *rr, uint8_t *ss, uint8_t *vv)
{
	mbedtls_mpi r, s;

	mbedtls_mpi_init(&r);
	mbedtls_mpi_init(&s);
	int ret=mbedtls_ecdsa_sign_with_v(&ctxDSA.grp, &r, &s, vv, &ctxDSA.d, data, in_len, mbedtls_sgx_drbg_random, NULL);

	mbedtls_mpi_write_binary(&r, rr, 32);
	mbedtls_mpi_write_binary(&s, ss, 32);

	mbedtls_mpi_free(&r);
	mbedtls_mpi_free(&s);
}
void CreateTransaction(uint8_t contractAddress[20], uint8_t inputHash[32], uint16_t winnerIndex, uint32_t winnerBid, uint8_t transaction[188])
{
	std::vector<uint8_t> tx;
	
	//empty nonce = 80
	tx.push_back(0x04);

	// Gas Price = 50 Gwei (0BA43B7400) len = 85
	uint8_t gasPrice[] = { '\x85', '\x0B', '\xA4', '\x3B', '\x74', '\x00' };
	for (int i = 0; i < 6; i++)
		tx.push_back(gasPrice[i]);

	// Gas Limit 2,000,000 (1E8480) len = 83
	uint8_t gasLimit[] = { '\x83', '\x1E', '\x84', '\x80' };
	for (int i = 0; i < 4; i++)
		tx.push_back(gasLimit[i]);

	//To address =contractAddress , len =94
	tx.push_back(0x94);
	for (int i = 0; i <20; i++)
		tx.push_back(contractAddress[i]);
	
	//Value = 0, len = 80
	tx.push_back(0x80);

	//Data size =100, len B7+1 , 100, data
	tx.push_back(0xB8);
	tx.push_back(0x64);

	//selector c29ae58f
	uint8_t functionSelector[] = { '\xC2', '\x9A', '\xE5', '\x8F' };
	for (int i = 0; i < sizeof(functionSelector); i++)
		tx.push_back(functionSelector[i]);
	//input hash 
	for (int i = 0; i < 32; i++)
		tx.push_back(inputHash[i]);
	//winner index
	tx.insert(tx.end(), 30, 0); //pad
	for (int i = 1; i >= 0; i--)
		tx.push_back((uint8_t)(winnerIndex >> (8 * i)));
	//winner bid
	tx.insert(tx.end(), 28, 0);
	for (int i = 3; i >= 0; i--)
		tx.push_back((uint8_t)(winnerBid >> (8 * i)));
	// prepare for signing
	tx.insert(tx.begin(), tx.size());
	tx.insert(tx.begin(), 0xF8);
	uint8_t _tx_hash[32], r[32], s[32], v;
	keccak(&tx[0], tx.size(), _tx_hash, 32);
	Sign(_tx_hash, sizeof(_tx_hash), r, s, &v);

	tx.push_back(v);
	tx.push_back(0xA0);
	for (int i = 0; i < sizeof(r); i++)
		tx.push_back(r[i]);
	tx.push_back(0xA0);
	for (int i = 0; i < sizeof(s); i++)
		tx.push_back(s[i]);
	tx[1]= tx.size()-2;
	std::copy(tx.begin(), tx.end(), transaction);
}
int EnclaveStart(sgx_sealed_data_t *sealed, size_t *len, uint8_t sgxPublicKey[64], uint8_t sgxAddress[20], uint8_t dhPublicKey[32])
{
	if(isLoaded)
		return -1;

	uint8_t dsaPrivateKey[32], dhPrivateKey[32], secret[64], tmpDHPublicKey[32], tmpDSAPublicKey[65], tmpcontractAddress[32];
	size_t buffLen = 0;

	//init DSA key-pair
	mbedtls_ecdsa_init(&ctxDSA);
#ifdef RANDOM
	mbedtls_ecdsa_genkey(&ctxDSA, MBEDTLS_ECP_DP_SECP256K1,mbedtls_sgx_drbg_random, NULL);
#else
	int ret;
	mbedtls_mpi d;
	mbedtls_mpi_init(&d);
	mbedtls_ecp_group_load(&ctxDSA.grp, MBEDTLS_ECP_DP_SECP256K1);
	ret =mbedtls_mpi_read_string(&d, 16, "698fb50bc211b45952e3be2c65904895349bef146116dddfe7a00817c7740e92");
	ret = mbedtls_mpi_copy(&ctxDSA.d, &d);
	size_t tt = mbedtls_mpi_size(&d);
	ret = mbedtls_ecp_mul(&ctxDSA.grp, &ctxDSA.Q, &ctxDSA.d, &ctxDSA.grp.G, NULL, NULL);

#endif
	mbedtls_mpi_write_binary(&ctxDSA.d, dsaPrivateKey, sizeof(dsaPrivateKey));
	mbedtls_ecp_point_write_binary(&ctxDSA.grp, &ctxDSA.Q, MBEDTLS_ECP_PF_UNCOMPRESSED, &buffLen, tmpDSAPublicKey, 65);

	//init DH key-pair
	mbedtls_ecdh_init(&ctxDH);
	mbedtls_ecp_group_load(&ctxDH.grp, MBEDTLS_ECP_DP_CURVE25519);
	mbedtls_ecdh_gen_public( &ctxDH.grp, &ctxDH.d, &ctxDH.Q, mbedtls_sgx_drbg_random, NULL );
	mbedtls_mpi_write_binary(&ctxDH.d, dhPrivateKey,sizeof(dhPrivateKey));
	mbedtls_mpi_write_binary(&ctxDH.Q.X, tmpDHPublicKey, sizeof(tmpDHPublicKey));
	
	//compute contract address
	keccak(tmpDSAPublicKey + 1, 64, tmpcontractAddress, 32);
	
	// seal the secret
	memcpy(secret,dsaPrivateKey, sizeof(dsaPrivateKey));
	memcpy(secret+sizeof(dsaPrivateKey), dhPrivateKey, sizeof(dhPrivateKey));
	buffLen = sgx_calc_sealed_data_size(0, sizeof(secret));
	sgx_sealed_data_t *sealedBuffer = (sgx_sealed_data_t *)malloc(buffLen);
	sgx_seal_data(0, NULL, sizeof(secret),secret, buffLen, sealedBuffer);
	memcpy(sealed, sealedBuffer, buffLen);	

	// copy to user space
	*len = buffLen;
	memcpy(sgxPublicKey, tmpDSAPublicKey+1, 64);
	memcpy(sgxAddress, tmpcontractAddress + 12, 20);
	memcpy(dhPublicKey,tmpDHPublicKey, 32);

	//free resources
	free(sealedBuffer);
	isLoaded = true;
	return 0;
}
int EnclaveUnsealPrivateKeys(sgx_sealed_data_t *sealed)
{
	if(isLoaded)
		return -1;

	uint8_t secret[64];
	uint32_t buffLen = sizeof(secret);
	sgx_unseal_data(sealed, NULL,0,secret,&buffLen);

	//Load DSA 
	mbedtls_ecdsa_init(&ctxDSA);
	mbedtls_ecp_group_load(&ctxDSA.grp, MBEDTLS_ECP_DP_SECP256K1);
	mbedtls_mpi_read_binary(&ctxDSA.d,secret, 32);
	mbedtls_ecp_mul(&ctxDSA.grp, &ctxDSA.Q,&ctxDSA.d, &ctxDSA.grp.G,NULL,NULL);

	//load DH
	mbedtls_ecdh_init(&ctxDH);
	mbedtls_ecp_group_load(&ctxDH.grp,MBEDTLS_ECP_DP_CURVE25519);
	mbedtls_mpi_read_binary(&ctxDH.d, secret+32, 32);
	mbedtls_ecp_mul(&ctxDH.grp,&ctxDH.Q,&ctxDH.d,&ctxDH.grp.G,NULL,NULL);
	isLoaded= true;
	return 0;
}
void EnclaveAuctionWinner(BID* bids, size_t count, uint8_t contractAddress[20], uint8_t transaction[188])
{
	uint32_t winnerBid=0,winnerIndex=0, temp;
	uint8_t inputHash[32];
	keccak((uint8_t*)bids, sizeof(BID)*count, inputHash, 32);

	for (size_t i = 0; i < count; i++)
	{
		temp = Decrypt(bids[i]);
		if (temp > winnerBid)
		{
			winnerBid = temp;
			winnerIndex = i;
		}
	}	
	printf_sgx("Highest= %02X\t Index= %02X\n", winnerBid, winnerIndex);
	CreateTransaction(contractAddress, inputHash, winnerIndex, winnerBid, transaction);
}

void BidderEncrypt(uint8_t* sgxPublicKey, BID* bid)
{
	uint8_t  key[32];
	BID tmpBid;
	mbedtls_ecdh_context ctx;

	//generate keys and compute shared key
	mbedtls_ecdh_init(&ctx);
	mbedtls_ecp_group_load(&ctx.grp, MBEDTLS_ECP_DP_CURVE25519);
	mbedtls_ecdh_gen_public(&ctx.grp, &ctx.d, &ctx.Q, mbedtls_sgx_drbg_random, NULL);
	mbedtls_mpi_write_binary(&ctx.Q.X, tmpBid.publicKey, sizeof(tmpBid.publicKey));
	mbedtls_mpi_lset(&ctx.Qp.Z, 1);
	mbedtls_mpi_read_binary(&ctx.Qp.X, sgxPublicKey, 32);
	mbedtls_ecdh_compute_shared(&ctx.grp, &ctx.z, &ctx.Qp, &ctx.d, NULL, NULL);
	mbedtls_mpi_write_binary(&ctx.z, key, 32);

	//encrypt bid 
	uint32_t value = 0;
	sgx_read_rand((unsigned char*)&value, 1);
	printf_sgx("Bid %u\n", value);

	// Generate the IV (nonce)
	sgx_read_rand(tmpBid.cipher + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE);

	sgx_rijndael128GCM_encrypt(
		(sgx_aes_gcm_128bit_key_t*)&key,
		(uint8_t *)&value, sizeof(value),
		tmpBid.cipher + SGX_AESGCM_MAC_SIZE + SGX_AESGCM_IV_SIZE,
		tmpBid.cipher + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE,
		NULL, 0,
		(sgx_aes_gcm_128bit_tag_t *)(tmpBid.cipher));
	//copy to user space
	memcpy(bid, &tmpBid, sizeof(BID));

	//free resources
	mbedtls_ecdh_free(&ctx);

}

