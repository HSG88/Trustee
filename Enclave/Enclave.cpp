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
#include"glue.h"

uint32_t Decrypt(mbedtls_ecdh_context& ctxDH, uint8_t* cipherText)
{
	sgx_aes_gcm_128bit_tag_t* tag = (sgx_aes_gcm_128bit_tag_t *)cipherText;
	uint8_t* iv = cipherText + SGX_AESGCM_MAC_SIZE;
	uint8_t* bidCipher = cipherText + SGX_AESGCM_MAC_SIZE+ SGX_AESGCM_IV_SIZE;
	uint8_t* bidDhPublicKey = cipherText + 32;

	uint8_t key[32];
	uint32_t value = 0;
	//compute shared
	mbedtls_mpi_read_binary(&ctxDH.Qp.X, bidDhPublicKey, 32);
	mbedtls_mpi_lset(&ctxDH.Qp.Z, 1);
	mbedtls_ecdh_compute_shared(&ctxDH.grp, &ctxDH.z, &ctxDH.Qp, &ctxDH.d, NULL, NULL);
	mbedtls_mpi_write_binary(&ctxDH.z, key, 32);
	//decrypt bid
	sgx_rijndael128GCM_decrypt((sgx_aes_gcm_128bit_key_t*)&key, bidCipher, sizeof(value),(uint8_t*)&value, iv, SGX_AESGCM_IV_SIZE,NULL, 0,tag);
	return value;
}
void Sign(mbedtls_ecdsa_context& ctxDSA, const uint8_t *data, size_t in_len, uint8_t *rr, uint8_t *ss, uint8_t *vv)
{
	mbedtls_mpi r, s;
	mbedtls_mpi_init(&r);
	mbedtls_mpi_init(&s);
	mbedtls_ecdsa_sign_with_v(&ctxDSA.grp, &r, &s, vv, &ctxDSA.d, data, in_len, mbedtls_sgx_drbg_random, NULL);
	mbedtls_mpi_write_binary(&r, rr, 32);
	mbedtls_mpi_write_binary(&s, ss, 32);
	mbedtls_mpi_free(&r);
	mbedtls_mpi_free(&s);
}
void CreateTransaction(mbedtls_ecdsa_context& ctxDSA, uint8_t contractAddress[20], uint8_t inputHash[32], uint16_t winnerIndex, uint32_t winnerBid, uint8_t transaction[512], size_t* transactionLen)
{
	std::vector<uint8_t> tx;
	//empty nonce = 80
	tx.push_back(0x80);
	// Gas Price = 50 Gwei (0BA43B7400) len = 85
	uint8_t gasPrice[] = { '\x85', '\x0B', '\xA4', '\x3B', '\x74', '\x00' };
	for (int i = 0; i < sizeof(gasPrice); i++)
		tx.push_back(gasPrice[i]);
	// Gas Limit 4,000,000 (3D0900) len = 83
	uint8_t gasLimit[] = { '\x83', '\x3D', '\x09', '\x00' };
	for (int i = 0; i < sizeof(gasLimit); i++)
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
	Sign(ctxDSA,_tx_hash, sizeof(_tx_hash), r, s, &v);

	tx.push_back(v);
	tx.push_back(0xA0);
	for (int i = 0; i < sizeof(r); i++)
		tx.push_back(r[i]);
	tx.push_back(0xA0);
	for (int i = 0; i < sizeof(s); i++)
		tx.push_back(s[i]);
	tx[1]= tx.size()-2;
	*transactionLen = tx.size();
	std::copy(tx.begin(), tx.end(), transaction);
}
bool RecoverContexts(sgx_sealed_data_t *sealed, size_t sealedLen, mbedtls_ecdh_context& ctxDH, mbedtls_ecdsa_context& ctxDSA)
{
	uint8_t secret[64];
	uint8_t* dhPrivateKey = secret;
	uint8_t* dsaPrivateKey = secret +32;
	uint32_t secretLen = sizeof(secret);
	//make it one time only
	sgx_unseal_data(sealed, NULL, 0, secret, &secretLen);

	//init ecdh
	mbedtls_ecdh_init(&ctxDH);
	mbedtls_ecp_group_load(&ctxDH.grp, MBEDTLS_ECP_DP_CURVE25519);
	mbedtls_mpi_read_binary(&ctxDH.d, dhPrivateKey, 32);
	mbedtls_ecp_mul(&ctxDH.grp, &ctxDH.Q, &ctxDH.d, &ctxDH.grp.G, NULL, NULL);

	//init ecdsa
	mbedtls_ecdsa_init(&ctxDSA);
	mbedtls_ecp_group_load(&ctxDSA.grp, MBEDTLS_ECP_DP_SECP256K1);
	mbedtls_mpi_read_binary(&ctxDSA.d, dsaPrivateKey, 32);
	mbedtls_ecp_mul(&ctxDSA.grp, &ctxDSA.Q, &ctxDSA.d, &ctxDSA.grp.G, NULL, NULL);
	return true;
}
void GetWinner(mbedtls_ecdh_context& ctxDH, uint8_t* cipher, size_t cipherLen, uint32_t* winnerBid, uint16_t* winnerIndex)
{
	uint32_t temp;
	int count = cipherLen / 64;
	for (int i = 0; i < count; i++)
	{
		temp = Decrypt(ctxDH, cipher + i * 64);
		if (temp > *winnerBid)
		{
			*winnerBid = temp;
			*winnerIndex = i;
		}
	}
}

void EnclaveStart(sgx_sealed_data_t *sealed, size_t sealedSize, size_t* sealedLen, uint8_t sgxAddress[20], uint8_t dhPublicKey[32])
{
	mbedtls_ecdsa_context ctxDSA;
	mbedtls_ecdh_context ctxDH;
	uint8_t secret[64], tmpDHPublicKey[32], tmpDSAPublicKey[65], tmpSGXAddress[32];
	char buff[100];
	size_t tmpLen;

	//init DH key-pair
	mbedtls_ecdh_init(&ctxDH);
	mbedtls_ecp_group_load(&ctxDH.grp, MBEDTLS_ECP_DP_CURVE25519);
	mbedtls_ecdh_gen_public(&ctxDH.grp, &ctxDH.d, &ctxDH.Q, mbedtls_sgx_drbg_random, NULL);
	mbedtls_mpi_write_binary(&ctxDH.d, secret, 32);
	mbedtls_mpi_write_binary(&ctxDH.Q.X, tmpDHPublicKey, sizeof(tmpDHPublicKey));
	mbedtls_mpi_write_string(&ctxDH.d, 16, buff, 100, &tmpLen);
	printf_sgx("DH Prv: %s\n", buff);

	//init DSA key-pair
	mbedtls_ecdsa_init(&ctxDSA);
	mbedtls_ecdsa_genkey(&ctxDSA, MBEDTLS_ECP_DP_SECP256K1, mbedtls_sgx_drbg_random, NULL);
	mbedtls_mpi_write_binary(&ctxDSA.d, secret + 32, 32);
	mbedtls_ecp_point_write_binary(&ctxDSA.grp, &ctxDSA.Q, MBEDTLS_ECP_PF_UNCOMPRESSED, sealedLen, tmpDSAPublicKey, 65);

	//compute contract address
	keccak(tmpDSAPublicKey + 1, 64, tmpSGXAddress, 32);

	// seal the secret
	*sealedLen = sgx_calc_sealed_data_size(0, sizeof(secret));
	sgx_sealed_data_t *sealedBuffer = (sgx_sealed_data_t *)malloc(*sealedLen);
	sgx_seal_data(0, NULL, sizeof(secret), secret, *sealedLen, sealedBuffer);

	// copy to user space
	memcpy(sealed, sealedBuffer, *sealedLen);
	memcpy(sgxAddress, tmpSGXAddress + 12, 20);
	memcpy(dhPublicKey, tmpDHPublicKey, 32);

	//free resources
	mbedtls_ecdsa_free(&ctxDSA);
	mbedtls_ecdh_free(&ctxDH);
	free(sealedBuffer);
}
void EnclaveGetAuctionWinner(sgx_sealed_data_t *sealed, size_t sealedLen, uint8_t* cipher, size_t cipherLen, uint8_t contractAddress[20], uint8_t transaction[512], size_t* transactionLen)
{
	mbedtls_ecdh_context ctxDH;
	mbedtls_ecdsa_context ctxDSA;
	uint32_t winnerBid=0;
	uint16_t winnerIndex=0;
	uint8_t inputHash[32];

	if (!RecoverContexts(sealed, sealedLen, ctxDH, ctxDSA))
	{
		*transactionLen = 0;
		return;
	}
	GetWinner(ctxDH, cipher, cipherLen, &winnerBid, &winnerIndex);
	keccak(cipher, cipherLen, inputHash, 32);
	CreateTransaction(ctxDSA, contractAddress, inputHash, winnerIndex, winnerBid, transaction, transactionLen);
	
	mbedtls_ecdh_free(&ctxDH);
	mbedtls_ecdsa_free(&ctxDSA);
}
