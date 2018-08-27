#ifndef ENCLAVE_U_H__
#define ENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */

#include "sgx_report.h"
#include "stddef.h"
#include "sgx_tseal.h"
#include "mbedtls/net_v.h"
#include "mbedtls/timing_v.h"

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BID {
	unsigned char publicKey[32];
	unsigned char cipher[32];
} BID;

int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_connect, (mbedtls_net_context* ctx, const char* host, const char* port, int proto));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_bind, (mbedtls_net_context* ctx, const char* bind_ip, const char* port, int proto));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_accept, (mbedtls_net_context* bind_ctx, mbedtls_net_context* client_ctx, void* client_ip, size_t buf_size, size_t* ip_len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_set_block, (mbedtls_net_context* ctx));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_set_nonblock, (mbedtls_net_context* ctx));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_usleep, (unsigned long int usec));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_recv, (mbedtls_net_context* ctx, unsigned char* buf, size_t len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_send, (mbedtls_net_context* ctx, const unsigned char* buf, size_t len));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_recv_timeout, (mbedtls_net_context* ctx, unsigned char* buf, size_t len, uint32_t timeout));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_free, (mbedtls_net_context* ctx));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* str));

sgx_status_t EnclaveStart(sgx_enclave_id_t eid, int* retval, sgx_sealed_data_t* sealed, size_t* len, uint8_t contractPublicKey[64], uint8_t address[20], uint8_t encryptPublicKey[32]);
sgx_status_t EnclaveUnsealPrivateKeys(sgx_enclave_id_t eid, int* retval, sgx_sealed_data_t* sealed);
sgx_status_t EnclaveAuctionWinner(sgx_enclave_id_t eid, BID* bids, size_t _count, uint8_t contractAddress[20], uint8_t transaction[204]);
sgx_status_t BidderEncrypt(sgx_enclave_id_t eid, uint8_t* sgxPublicKey, BID* bid);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
