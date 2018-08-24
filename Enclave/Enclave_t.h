#ifndef ENCLAVE_T_H__
#define ENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

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

int EnclaveStart(sgx_sealed_data_t* sealed, size_t* len, uint8_t contractPublicKey[64], uint8_t address[20], uint8_t encryptPublicKey[32]);
int EnclaveUnsealPrivateKeys(sgx_sealed_data_t* sealed);
void EnclaveAuctionWinner(BID* bids, size_t _count, uint32_t* winnerIndex, uint32_t* winnerBid, uint8_t signature[32]);
void BidderEncrypt(uint8_t* sgxPublicKey, BID* bid);

sgx_status_t SGX_CDECL ocall_mbedtls_net_connect(int* retval, mbedtls_net_context* ctx, const char* host, const char* port, int proto);
sgx_status_t SGX_CDECL ocall_mbedtls_net_bind(int* retval, mbedtls_net_context* ctx, const char* bind_ip, const char* port, int proto);
sgx_status_t SGX_CDECL ocall_mbedtls_net_accept(int* retval, mbedtls_net_context* bind_ctx, mbedtls_net_context* client_ctx, void* client_ip, size_t buf_size, size_t* ip_len);
sgx_status_t SGX_CDECL ocall_mbedtls_net_set_block(int* retval, mbedtls_net_context* ctx);
sgx_status_t SGX_CDECL ocall_mbedtls_net_set_nonblock(int* retval, mbedtls_net_context* ctx);
sgx_status_t SGX_CDECL ocall_mbedtls_net_usleep(unsigned long int usec);
sgx_status_t SGX_CDECL ocall_mbedtls_net_recv(int* retval, mbedtls_net_context* ctx, unsigned char* buf, size_t len);
sgx_status_t SGX_CDECL ocall_mbedtls_net_send(int* retval, mbedtls_net_context* ctx, const unsigned char* buf, size_t len);
sgx_status_t SGX_CDECL ocall_mbedtls_net_recv_timeout(int* retval, mbedtls_net_context* ctx, unsigned char* buf, size_t len, uint32_t timeout);
sgx_status_t SGX_CDECL ocall_mbedtls_net_free(mbedtls_net_context* ctx);
sgx_status_t SGX_CDECL ocall_print_string(int* retval, const char* str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
