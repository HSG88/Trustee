#include "Enclave_u.h"
#include <errno.h>

typedef struct ms_EnclaveStart_t {
	int ms_retval;
	sgx_sealed_data_t* ms_sealed;
	size_t* ms_len;
	uint8_t* ms_contractPublicKey;
	uint8_t* ms_address;
	uint8_t* ms_encryptPublicKey;
} ms_EnclaveStart_t;

typedef struct ms_EnclaveUnsealPrivateKeys_t {
	int ms_retval;
	sgx_sealed_data_t* ms_sealed;
} ms_EnclaveUnsealPrivateKeys_t;

typedef struct ms_EnclaveAuctionWinner_t {
	BID* ms_bids;
	size_t ms__count;
	uint8_t* ms_contractAddress;
	uint8_t* ms_transaction;
} ms_EnclaveAuctionWinner_t;

typedef struct ms_BidderEncrypt_t {
	uint8_t* ms_sgxPublicKey;
	BID* ms_bid;
} ms_BidderEncrypt_t;

typedef struct ms_ocall_mbedtls_net_connect_t {
	int ms_retval;
	mbedtls_net_context* ms_ctx;
	char* ms_host;
	char* ms_port;
	int ms_proto;
} ms_ocall_mbedtls_net_connect_t;

typedef struct ms_ocall_mbedtls_net_bind_t {
	int ms_retval;
	mbedtls_net_context* ms_ctx;
	char* ms_bind_ip;
	char* ms_port;
	int ms_proto;
} ms_ocall_mbedtls_net_bind_t;

typedef struct ms_ocall_mbedtls_net_accept_t {
	int ms_retval;
	mbedtls_net_context* ms_bind_ctx;
	mbedtls_net_context* ms_client_ctx;
	void* ms_client_ip;
	size_t ms_buf_size;
	size_t* ms_ip_len;
} ms_ocall_mbedtls_net_accept_t;

typedef struct ms_ocall_mbedtls_net_set_block_t {
	int ms_retval;
	mbedtls_net_context* ms_ctx;
} ms_ocall_mbedtls_net_set_block_t;

typedef struct ms_ocall_mbedtls_net_set_nonblock_t {
	int ms_retval;
	mbedtls_net_context* ms_ctx;
} ms_ocall_mbedtls_net_set_nonblock_t;

typedef struct ms_ocall_mbedtls_net_usleep_t {
	unsigned long int ms_usec;
} ms_ocall_mbedtls_net_usleep_t;

typedef struct ms_ocall_mbedtls_net_recv_t {
	int ms_retval;
	mbedtls_net_context* ms_ctx;
	unsigned char* ms_buf;
	size_t ms_len;
} ms_ocall_mbedtls_net_recv_t;

typedef struct ms_ocall_mbedtls_net_send_t {
	int ms_retval;
	mbedtls_net_context* ms_ctx;
	unsigned char* ms_buf;
	size_t ms_len;
} ms_ocall_mbedtls_net_send_t;

typedef struct ms_ocall_mbedtls_net_recv_timeout_t {
	int ms_retval;
	mbedtls_net_context* ms_ctx;
	unsigned char* ms_buf;
	size_t ms_len;
	uint32_t ms_timeout;
} ms_ocall_mbedtls_net_recv_timeout_t;

typedef struct ms_ocall_mbedtls_net_free_t {
	mbedtls_net_context* ms_ctx;
} ms_ocall_mbedtls_net_free_t;

typedef struct ms_ocall_print_string_t {
	int ms_retval;
	char* ms_str;
} ms_ocall_print_string_t;

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_connect(void* pms)
{
	ms_ocall_mbedtls_net_connect_t* ms = SGX_CAST(ms_ocall_mbedtls_net_connect_t*, pms);
	ms->ms_retval = ocall_mbedtls_net_connect(ms->ms_ctx, (const char*)ms->ms_host, (const char*)ms->ms_port, ms->ms_proto);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_bind(void* pms)
{
	ms_ocall_mbedtls_net_bind_t* ms = SGX_CAST(ms_ocall_mbedtls_net_bind_t*, pms);
	ms->ms_retval = ocall_mbedtls_net_bind(ms->ms_ctx, (const char*)ms->ms_bind_ip, (const char*)ms->ms_port, ms->ms_proto);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_accept(void* pms)
{
	ms_ocall_mbedtls_net_accept_t* ms = SGX_CAST(ms_ocall_mbedtls_net_accept_t*, pms);
	ms->ms_retval = ocall_mbedtls_net_accept(ms->ms_bind_ctx, ms->ms_client_ctx, ms->ms_client_ip, ms->ms_buf_size, ms->ms_ip_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_set_block(void* pms)
{
	ms_ocall_mbedtls_net_set_block_t* ms = SGX_CAST(ms_ocall_mbedtls_net_set_block_t*, pms);
	ms->ms_retval = ocall_mbedtls_net_set_block(ms->ms_ctx);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_set_nonblock(void* pms)
{
	ms_ocall_mbedtls_net_set_nonblock_t* ms = SGX_CAST(ms_ocall_mbedtls_net_set_nonblock_t*, pms);
	ms->ms_retval = ocall_mbedtls_net_set_nonblock(ms->ms_ctx);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_usleep(void* pms)
{
	ms_ocall_mbedtls_net_usleep_t* ms = SGX_CAST(ms_ocall_mbedtls_net_usleep_t*, pms);
	ocall_mbedtls_net_usleep(ms->ms_usec);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_recv(void* pms)
{
	ms_ocall_mbedtls_net_recv_t* ms = SGX_CAST(ms_ocall_mbedtls_net_recv_t*, pms);
	ms->ms_retval = ocall_mbedtls_net_recv(ms->ms_ctx, ms->ms_buf, ms->ms_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_send(void* pms)
{
	ms_ocall_mbedtls_net_send_t* ms = SGX_CAST(ms_ocall_mbedtls_net_send_t*, pms);
	ms->ms_retval = ocall_mbedtls_net_send(ms->ms_ctx, (const unsigned char*)ms->ms_buf, ms->ms_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_recv_timeout(void* pms)
{
	ms_ocall_mbedtls_net_recv_timeout_t* ms = SGX_CAST(ms_ocall_mbedtls_net_recv_timeout_t*, pms);
	ms->ms_retval = ocall_mbedtls_net_recv_timeout(ms->ms_ctx, ms->ms_buf, ms->ms_len, ms->ms_timeout);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_mbedtls_net_free(void* pms)
{
	ms_ocall_mbedtls_net_free_t* ms = SGX_CAST(ms_ocall_mbedtls_net_free_t*, pms);
	ocall_mbedtls_net_free(ms->ms_ctx);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ms->ms_retval = ocall_print_string((const char*)ms->ms_str);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * func_addr[11];
} ocall_table_Enclave = {
	11,
	{
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_connect,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_bind,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_accept,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_set_block,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_set_nonblock,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_usleep,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_recv,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_send,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_recv_timeout,
		(void*)(uintptr_t)Enclave_ocall_mbedtls_net_free,
		(void*)(uintptr_t)Enclave_ocall_print_string,
	}
};

sgx_status_t EnclaveStart(sgx_enclave_id_t eid, int* retval, sgx_sealed_data_t* sealed, size_t* len, uint8_t contractPublicKey[64], uint8_t address[20], uint8_t encryptPublicKey[32])
{
	sgx_status_t status;
	ms_EnclaveStart_t ms;
	ms.ms_sealed = sealed;
	ms.ms_len = len;
	ms.ms_contractPublicKey = (uint8_t*)contractPublicKey;
	ms.ms_address = (uint8_t*)address;
	ms.ms_encryptPublicKey = (uint8_t*)encryptPublicKey;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t EnclaveUnsealPrivateKeys(sgx_enclave_id_t eid, int* retval, sgx_sealed_data_t* sealed)
{
	sgx_status_t status;
	ms_EnclaveUnsealPrivateKeys_t ms;
	ms.ms_sealed = sealed;
	status = sgx_ecall(eid, 1, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t EnclaveAuctionWinner(sgx_enclave_id_t eid, BID* bids, size_t _count, uint8_t contractAddress[20], uint8_t transaction[204])
{
	sgx_status_t status;
	ms_EnclaveAuctionWinner_t ms;
	ms.ms_bids = bids;
	ms.ms__count = _count;
	ms.ms_contractAddress = (uint8_t*)contractAddress;
	ms.ms_transaction = (uint8_t*)transaction;
	status = sgx_ecall(eid, 2, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t BidderEncrypt(sgx_enclave_id_t eid, uint8_t* sgxPublicKey, BID* bid)
{
	sgx_status_t status;
	ms_BidderEncrypt_t ms;
	ms.ms_sgxPublicKey = sgxPublicKey;
	ms.ms_bid = bid;
	status = sgx_ecall(eid, 3, &ocall_table_Enclave, &ms);
	return status;
}

