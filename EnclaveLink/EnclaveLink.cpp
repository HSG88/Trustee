#include"EnclaveLink.h"
#include "sgx_eid.h"		/* sgx_enclave_id_t */
#include "sgx_uae_service.h"
#include"Enclave_u.h"
static sgx_enclave_id_t global_eid = 0;

bool CreateEnclave()
{
	int updated;
	sgx_launch_token_t token = { 0 };
	return sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL) == SGX_SUCCESS;
}
void DestroyEnclave()
{
	sgx_destroy_enclave(global_eid);
}
int GenerateKeys(unsigned char sealed[2048], unsigned char sgxAddress[20], unsigned char dhPublicKey[32])
{
	size_t sealedLen = 0;
	EnclaveStart(global_eid, (sgx_sealed_data_t*)sealed, 2048, &sealedLen, sgxAddress, dhPublicKey);
	return sealedLen;
}
int GetAuctionWinner(unsigned char* sealed, unsigned int sealedLen, unsigned char* cipher, unsigned int cipherLen, unsigned char contractAddress[20], unsigned char transaction[512])
{
	size_t transactionLen;
	EnclaveGetAuctionWinner(global_eid, (sgx_sealed_data_t*)sealed, sealedLen, cipher, cipherLen, contractAddress, transaction, &transactionLen);
	return transactionLen;
}
