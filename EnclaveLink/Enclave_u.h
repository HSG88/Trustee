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

#ifndef OCALL_MBEDTLS_NET_CONNECT_DEFINED__
#define OCALL_MBEDTLS_NET_CONNECT_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_connect, (mbedtls_net_context* ctx, const char* host, const char* port, int proto));
#endif
#ifndef OCALL_MBEDTLS_NET_BIND_DEFINED__
#define OCALL_MBEDTLS_NET_BIND_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_bind, (mbedtls_net_context* ctx, const char* bind_ip, const char* port, int proto));
#endif
#ifndef OCALL_MBEDTLS_NET_ACCEPT_DEFINED__
#define OCALL_MBEDTLS_NET_ACCEPT_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_accept, (mbedtls_net_context* bind_ctx, mbedtls_net_context* client_ctx, void* client_ip, size_t buf_size, size_t* ip_len));
#endif
#ifndef OCALL_MBEDTLS_NET_SET_BLOCK_DEFINED__
#define OCALL_MBEDTLS_NET_SET_BLOCK_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_set_block, (mbedtls_net_context* ctx));
#endif
#ifndef OCALL_MBEDTLS_NET_SET_NONBLOCK_DEFINED__
#define OCALL_MBEDTLS_NET_SET_NONBLOCK_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_set_nonblock, (mbedtls_net_context* ctx));
#endif
#ifndef OCALL_MBEDTLS_NET_USLEEP_DEFINED__
#define OCALL_MBEDTLS_NET_USLEEP_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_usleep, (unsigned long int usec));
#endif
#ifndef OCALL_MBEDTLS_NET_RECV_DEFINED__
#define OCALL_MBEDTLS_NET_RECV_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_recv, (mbedtls_net_context* ctx, unsigned char* buf, size_t len));
#endif
#ifndef OCALL_MBEDTLS_NET_SEND_DEFINED__
#define OCALL_MBEDTLS_NET_SEND_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_send, (mbedtls_net_context* ctx, const unsigned char* buf, size_t len));
#endif
#ifndef OCALL_MBEDTLS_NET_RECV_TIMEOUT_DEFINED__
#define OCALL_MBEDTLS_NET_RECV_TIMEOUT_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_recv_timeout, (mbedtls_net_context* ctx, unsigned char* buf, size_t len, uint32_t timeout));
#endif
#ifndef OCALL_MBEDTLS_NET_FREE_DEFINED__
#define OCALL_MBEDTLS_NET_FREE_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_mbedtls_net_free, (mbedtls_net_context* ctx));
#endif
#ifndef OCALL_PRINT_STRING_DEFINED__
#define OCALL_PRINT_STRING_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* str));
#endif

sgx_status_t Encrypt(sgx_enclave_id_t eid, uint8_t sgxPK[32], uint32_t bid, uint8_t bidPK[32], uint8_t bidCT[32]);
sgx_status_t EnclaveStart(sgx_enclave_id_t eid, sgx_sealed_data_t* sealed, size_t sealedSize, size_t* sealedLen, uint8_t address[20], uint8_t dhPublicKey[32]);
sgx_status_t EnclaveGetAuctionWinner(sgx_enclave_id_t eid, sgx_sealed_data_t* sealed, size_t sealedLen, uint8_t* cipher, size_t cipherLen, uint8_t contractAddress[20], uint8_t transaction[512], size_t* transactionLen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
