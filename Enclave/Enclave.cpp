#include <stdio.h>
#include <stdarg.h>
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


int EnclaveStart(sgx_sealed_data_t *sealed, size_t *len, uint8_t contractPublicKey[64], uint8_t contractAddress[20], uint8_t encryptPublicKey[32])
{
	if(isLoaded)
		return -1;

	uint8_t dsaPrivateKey[32], dhPrivateKey[32], secret[64], tmpDHPublicKey[32], tmpDSAPublicKey[65], tmpcontractAddress[32];
	size_t buffLen = 0;

	//init DSA key-pair
	mbedtls_ecdsa_init(&ctxDSA);
	mbedtls_ecdsa_genkey(&ctxDSA, MBEDTLS_ECP_DP_SECP256K1,mbedtls_sgx_drbg_random, NULL);
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
	memcpy(contractPublicKey, tmpDSAPublicKey+1, 64);
	memcpy(contractAddress, tmpcontractAddress + 12, 20);
	memcpy(encryptPublicKey,tmpDHPublicKey, 32);

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

void BidderEncrypt(uint8_t* sgxPublicKey,BID* bid)
{
	uint8_t  key[32];
	BID tmpBid;
	mbedtls_ecdh_context ctx;

	//generate keys and compute shared key
	mbedtls_ecdh_init(&ctx);
	mbedtls_ecp_group_load(&ctx.grp,MBEDTLS_ECP_DP_CURVE25519);
	mbedtls_ecdh_gen_public(&ctx.grp, &ctx.d, &ctx.Q, mbedtls_sgx_drbg_random, NULL);
	mbedtls_mpi_write_binary(&ctx.Q.X, tmpBid.publicKey, sizeof(tmpBid.publicKey));
	mbedtls_mpi_lset(&ctx.Qp.Z, 1);
	mbedtls_mpi_read_binary(&ctx.Qp.X, sgxPublicKey, 32);
	mbedtls_ecdh_compute_shared(&ctx.grp,&ctx.z,&ctx.Qp, &ctx.d, NULL,NULL);
	mbedtls_mpi_write_binary(&ctx.z,key,32);

	//encrypt bid 
	uint32_t value=0;
	sgx_read_rand((unsigned char*)&value, 1);
	printf_sgx("Bid %u\n", value);

	// Generate the IV (nonce)
	sgx_read_rand(tmpBid.cipher + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE);

	sgx_rijndael128GCM_encrypt(
		(sgx_aes_gcm_128bit_key_t*)&key,
		(uint8_t *) &value, sizeof(value), 
		tmpBid.cipher + SGX_AESGCM_MAC_SIZE + SGX_AESGCM_IV_SIZE,
		tmpBid.cipher + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE,
		NULL, 0,
		(sgx_aes_gcm_128bit_tag_t *) (tmpBid.cipher));	
	//copy to user space
	memcpy(bid,&tmpBid, sizeof(BID));

	//free resources
	mbedtls_ecdh_free(&ctx);
	
}
uint32_t DecryptBid(BID bid)
{
	uint8_t key[32];
	uint32_t value=0;
	//compute shared
	mbedtls_mpi_read_binary(&ctxDH.Qp.X, bid.publicKey, sizeof(bid.publicKey));
	mbedtls_mpi_lset(&ctxDH.Qp.Z, 1);
	mbedtls_ecdh_compute_shared(&ctxDH.grp,&ctxDH.z, &ctxDH.Qp,&ctxDH.d,NULL,NULL);
	mbedtls_mpi_write_binary(&ctxDH.z,key,32);

	sgx_rijndael128GCM_decrypt(
		(sgx_aes_gcm_128bit_key_t*)&key,
		bid.cipher + SGX_AESGCM_MAC_SIZE + SGX_AESGCM_IV_SIZE,
		sizeof(value),
		(uint8_t*)&value,
		bid.cipher + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE,
		NULL, 0,
		(sgx_aes_gcm_128bit_tag_t *) bid.cipher);
	return value;
}
void EnclaveAuctionWinner(BID* bids, size_t count, uint32_t* winnerIndex, uint32_t* winnerBid, uint8_t signature[32])
{
	uint32_t max=0,maxIndex=0, temp;
	for(size_t i=0; i< count; i++)
	{
		temp=DecryptBid(bids[i]);
		if(temp>max)
			{
				max = temp;
				maxIndex = i;
			}
	}
	signature[0] = 0;
	*winnerBid = max;
	*winnerIndex =maxIndex;
}
int EnclaveSign(const uint8_t *data, size_t in_len, uint8_t *rr, uint8_t *ss, uint8_t *vv)
{
	int ret;
	mbedtls_mpi r, s;

	mbedtls_mpi_init(&r);
	mbedtls_mpi_init(&s);
	mbedtls_ecdsa_sign_with_v(&ctxDSA.grp, &r, &s, vv, &ctxDSA.d, data, in_len, mbedtls_sgx_drbg_random, NULL);

	mbedtls_mpi_write_binary(&r, rr, 32);
	mbedtls_mpi_write_binary(&s, ss, 32);

	ret = mbedtls_ecdsa_verify(&ctxDSA.grp, data, in_len, &ctxDSA.Q, &r, &s);
	if (ret != 0) 
		LL_CRITICAL("Error: mbedtls_ecdsa_verify returned %#x", ret);		
	mbedtls_mpi_free(&r);
	mbedtls_mpi_free(&s);
	return (ret);
}

//int EnclaveCreateReport(sgx_target_info_t *quote, sgx_report_t *report)
//{
//	return 0;
//}
//int EnclaveGetMR(uint8_t mr[32])
//{
//	return 0;
//}
//void dummy()
//{
//
//}