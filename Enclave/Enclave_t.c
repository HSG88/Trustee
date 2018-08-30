#include "Enclave_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */
#include "sgx_lfence.h" /* for sgx_lfence */

#include <errno.h>
#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


typedef struct ms_EnclaveStart_t {
	sgx_sealed_data_t* ms_sealed;
	size_t ms_sealedSize;
	size_t* ms_sealedLen;
	uint8_t* ms_address;
	uint8_t* ms_dhPublicKey;
} ms_EnclaveStart_t;

typedef struct ms_EnclaveGetAuctionWinner_t {
	sgx_sealed_data_t* ms_sealed;
	size_t ms_sealedLen;
	uint8_t* ms_cipher;
	size_t ms_cipherLen;
	uint8_t* ms_contractAddress;
	uint8_t* ms_transaction;
	size_t* ms_transactionLen;
} ms_EnclaveGetAuctionWinner_t;

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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_EnclaveStart(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_EnclaveStart_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_EnclaveStart_t* ms = SGX_CAST(ms_EnclaveStart_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sgx_sealed_data_t* _tmp_sealed = ms->ms_sealed;
	size_t _tmp_sealedSize = ms->ms_sealedSize;
	size_t _len_sealed = _tmp_sealedSize;
	sgx_sealed_data_t* _in_sealed = NULL;
	size_t* _tmp_sealedLen = ms->ms_sealedLen;
	size_t _len_sealedLen = sizeof(*_tmp_sealedLen);
	size_t* _in_sealedLen = NULL;
	uint8_t* _tmp_address = ms->ms_address;
	size_t _len_address = 20 * sizeof(*_tmp_address);
	uint8_t* _in_address = NULL;
	uint8_t* _tmp_dhPublicKey = ms->ms_dhPublicKey;
	size_t _len_dhPublicKey = 32 * sizeof(*_tmp_dhPublicKey);
	uint8_t* _in_dhPublicKey = NULL;

	CHECK_UNIQUE_POINTER(_tmp_sealed, _len_sealed);
	CHECK_UNIQUE_POINTER(_tmp_sealedLen, _len_sealedLen);
	CHECK_UNIQUE_POINTER(_tmp_address, _len_address);
	CHECK_UNIQUE_POINTER(_tmp_dhPublicKey, _len_dhPublicKey);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_sealed != NULL && _len_sealed != 0) {
		if ((_in_sealed = (sgx_sealed_data_t*)malloc(_len_sealed)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_sealed, 0, _len_sealed);
	}
	if (_tmp_sealedLen != NULL && _len_sealedLen != 0) {
		if ((_in_sealedLen = (size_t*)malloc(_len_sealedLen)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_sealedLen, 0, _len_sealedLen);
	}
	if (_tmp_address != NULL && _len_address != 0) {
		if ((_in_address = (uint8_t*)malloc(_len_address)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_address, 0, _len_address);
	}
	if (_tmp_dhPublicKey != NULL && _len_dhPublicKey != 0) {
		if ((_in_dhPublicKey = (uint8_t*)malloc(_len_dhPublicKey)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_dhPublicKey, 0, _len_dhPublicKey);
	}

	EnclaveStart(_in_sealed, _tmp_sealedSize, _in_sealedLen, _in_address, _in_dhPublicKey);
err:
	if (_in_sealed) {
		memcpy(_tmp_sealed, _in_sealed, _len_sealed);
		free(_in_sealed);
	}
	if (_in_sealedLen) {
		memcpy(_tmp_sealedLen, _in_sealedLen, _len_sealedLen);
		free(_in_sealedLen);
	}
	if (_in_address) {
		memcpy(_tmp_address, _in_address, _len_address);
		free(_in_address);
	}
	if (_in_dhPublicKey) {
		memcpy(_tmp_dhPublicKey, _in_dhPublicKey, _len_dhPublicKey);
		free(_in_dhPublicKey);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_EnclaveGetAuctionWinner(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_EnclaveGetAuctionWinner_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_EnclaveGetAuctionWinner_t* ms = SGX_CAST(ms_EnclaveGetAuctionWinner_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sgx_sealed_data_t* _tmp_sealed = ms->ms_sealed;
	size_t _tmp_sealedLen = ms->ms_sealedLen;
	size_t _len_sealed = _tmp_sealedLen;
	sgx_sealed_data_t* _in_sealed = NULL;
	uint8_t* _tmp_cipher = ms->ms_cipher;
	size_t _tmp_cipherLen = ms->ms_cipherLen;
	size_t _len_cipher = _tmp_cipherLen;
	uint8_t* _in_cipher = NULL;
	uint8_t* _tmp_contractAddress = ms->ms_contractAddress;
	size_t _len_contractAddress = 20 * sizeof(*_tmp_contractAddress);
	uint8_t* _in_contractAddress = NULL;
	uint8_t* _tmp_transaction = ms->ms_transaction;
	size_t _len_transaction = 512 * sizeof(*_tmp_transaction);
	uint8_t* _in_transaction = NULL;
	size_t* _tmp_transactionLen = ms->ms_transactionLen;
	size_t _len_transactionLen = sizeof(*_tmp_transactionLen);
	size_t* _in_transactionLen = NULL;

	CHECK_UNIQUE_POINTER(_tmp_sealed, _len_sealed);
	CHECK_UNIQUE_POINTER(_tmp_cipher, _len_cipher);
	CHECK_UNIQUE_POINTER(_tmp_contractAddress, _len_contractAddress);
	CHECK_UNIQUE_POINTER(_tmp_transaction, _len_transaction);
	CHECK_UNIQUE_POINTER(_tmp_transactionLen, _len_transactionLen);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_sealed != NULL && _len_sealed != 0) {
		_in_sealed = (sgx_sealed_data_t*)malloc(_len_sealed);
		if (_in_sealed == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_sealed, _tmp_sealed, _len_sealed);
	}
	if (_tmp_cipher != NULL && _len_cipher != 0) {
		_in_cipher = (uint8_t*)malloc(_len_cipher);
		if (_in_cipher == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_cipher, _tmp_cipher, _len_cipher);
	}
	if (_tmp_contractAddress != NULL && _len_contractAddress != 0) {
		_in_contractAddress = (uint8_t*)malloc(_len_contractAddress);
		if (_in_contractAddress == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_contractAddress, _tmp_contractAddress, _len_contractAddress);
	}
	if (_tmp_transaction != NULL && _len_transaction != 0) {
		if ((_in_transaction = (uint8_t*)malloc(_len_transaction)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_transaction, 0, _len_transaction);
	}
	if (_tmp_transactionLen != NULL && _len_transactionLen != 0) {
		if ((_in_transactionLen = (size_t*)malloc(_len_transactionLen)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_transactionLen, 0, _len_transactionLen);
	}

	EnclaveGetAuctionWinner(_in_sealed, _tmp_sealedLen, _in_cipher, _tmp_cipherLen, _in_contractAddress, _in_transaction, _in_transactionLen);
err:
	if (_in_sealed) free(_in_sealed);
	if (_in_cipher) free(_in_cipher);
	if (_in_contractAddress) free(_in_contractAddress);
	if (_in_transaction) {
		memcpy(_tmp_transaction, _in_transaction, _len_transaction);
		free(_in_transaction);
	}
	if (_in_transactionLen) {
		memcpy(_tmp_transactionLen, _in_transactionLen, _len_transactionLen);
		free(_in_transactionLen);
	}

	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[2];
} g_ecall_table = {
	2,
	{
		{(void*)(uintptr_t)sgx_EnclaveStart, 0},
		{(void*)(uintptr_t)sgx_EnclaveGetAuctionWinner, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[11][2];
} g_dyn_entry_table = {
	11,
	{
		{0, 0, },
		{0, 0, },
		{0, 0, },
		{0, 0, },
		{0, 0, },
		{0, 0, },
		{0, 0, },
		{0, 0, },
		{0, 0, },
		{0, 0, },
		{0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_mbedtls_net_connect(int* retval, mbedtls_net_context* ctx, const char* host, const char* port, int proto)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(*ctx);
	size_t _len_host = host ? strlen(host) + 1 : 0;
	size_t _len_port = port ? strlen(port) + 1 : 0;

	ms_ocall_mbedtls_net_connect_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_connect_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	ocalloc_size += (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) ? _len_ctx : 0;
	ocalloc_size += (host != NULL && sgx_is_within_enclave(host, _len_host)) ? _len_host : 0;
	ocalloc_size += (port != NULL && sgx_is_within_enclave(port, _len_port)) ? _len_port : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_connect_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_connect_t));

	if (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memcpy(__tmp_ctx, ctx, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
	} else if (ctx == NULL) {
		ms->ms_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (host != NULL && sgx_is_within_enclave(host, _len_host)) {
		ms->ms_host = (char*)__tmp;
		memcpy(__tmp, host, _len_host);
		__tmp = (void *)((size_t)__tmp + _len_host);
	} else if (host == NULL) {
		ms->ms_host = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (port != NULL && sgx_is_within_enclave(port, _len_port)) {
		ms->ms_port = (char*)__tmp;
		memcpy(__tmp, port, _len_port);
		__tmp = (void *)((size_t)__tmp + _len_port);
	} else if (port == NULL) {
		ms->ms_port = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_proto = proto;
	status = sgx_ocall(0, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) memcpy((void*)ctx, __tmp_ctx, _len_ctx);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_bind(int* retval, mbedtls_net_context* ctx, const char* bind_ip, const char* port, int proto)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(*ctx);
	size_t _len_bind_ip = bind_ip ? strlen(bind_ip) + 1 : 0;
	size_t _len_port = port ? strlen(port) + 1 : 0;

	ms_ocall_mbedtls_net_bind_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_bind_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	ocalloc_size += (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) ? _len_ctx : 0;
	ocalloc_size += (bind_ip != NULL && sgx_is_within_enclave(bind_ip, _len_bind_ip)) ? _len_bind_ip : 0;
	ocalloc_size += (port != NULL && sgx_is_within_enclave(port, _len_port)) ? _len_port : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_bind_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_bind_t));

	if (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memset(__tmp_ctx, 0, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
	} else if (ctx == NULL) {
		ms->ms_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (bind_ip != NULL && sgx_is_within_enclave(bind_ip, _len_bind_ip)) {
		ms->ms_bind_ip = (char*)__tmp;
		memcpy(__tmp, bind_ip, _len_bind_ip);
		__tmp = (void *)((size_t)__tmp + _len_bind_ip);
	} else if (bind_ip == NULL) {
		ms->ms_bind_ip = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (port != NULL && sgx_is_within_enclave(port, _len_port)) {
		ms->ms_port = (char*)__tmp;
		memcpy(__tmp, port, _len_port);
		__tmp = (void *)((size_t)__tmp + _len_port);
	} else if (port == NULL) {
		ms->ms_port = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_proto = proto;
	status = sgx_ocall(1, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) memcpy((void*)ctx, __tmp_ctx, _len_ctx);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_accept(int* retval, mbedtls_net_context* bind_ctx, mbedtls_net_context* client_ctx, void* client_ip, size_t buf_size, size_t* ip_len)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_bind_ctx = sizeof(*bind_ctx);
	size_t _len_client_ctx = sizeof(*client_ctx);
	size_t _len_client_ip = buf_size;
	size_t _len_ip_len = sizeof(*ip_len);

	ms_ocall_mbedtls_net_accept_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_accept_t);
	void *__tmp = NULL;

	void *__tmp_client_ctx = NULL;
	void *__tmp_client_ip = NULL;
	void *__tmp_ip_len = NULL;
	ocalloc_size += (bind_ctx != NULL && sgx_is_within_enclave(bind_ctx, _len_bind_ctx)) ? _len_bind_ctx : 0;
	ocalloc_size += (client_ctx != NULL && sgx_is_within_enclave(client_ctx, _len_client_ctx)) ? _len_client_ctx : 0;
	ocalloc_size += (client_ip != NULL && sgx_is_within_enclave(client_ip, _len_client_ip)) ? _len_client_ip : 0;
	ocalloc_size += (ip_len != NULL && sgx_is_within_enclave(ip_len, _len_ip_len)) ? _len_ip_len : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_accept_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_accept_t));

	if (bind_ctx != NULL && sgx_is_within_enclave(bind_ctx, _len_bind_ctx)) {
		ms->ms_bind_ctx = (mbedtls_net_context*)__tmp;
		memcpy(__tmp, bind_ctx, _len_bind_ctx);
		__tmp = (void *)((size_t)__tmp + _len_bind_ctx);
	} else if (bind_ctx == NULL) {
		ms->ms_bind_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (client_ctx != NULL && sgx_is_within_enclave(client_ctx, _len_client_ctx)) {
		ms->ms_client_ctx = (mbedtls_net_context*)__tmp;
		__tmp_client_ctx = __tmp;
		memset(__tmp_client_ctx, 0, _len_client_ctx);
		__tmp = (void *)((size_t)__tmp + _len_client_ctx);
	} else if (client_ctx == NULL) {
		ms->ms_client_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (client_ip != NULL && sgx_is_within_enclave(client_ip, _len_client_ip)) {
		ms->ms_client_ip = (void*)__tmp;
		__tmp_client_ip = __tmp;
		memset(__tmp_client_ip, 0, _len_client_ip);
		__tmp = (void *)((size_t)__tmp + _len_client_ip);
	} else if (client_ip == NULL) {
		ms->ms_client_ip = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_buf_size = buf_size;
	if (ip_len != NULL && sgx_is_within_enclave(ip_len, _len_ip_len)) {
		ms->ms_ip_len = (size_t*)__tmp;
		__tmp_ip_len = __tmp;
		memset(__tmp_ip_len, 0, _len_ip_len);
		__tmp = (void *)((size_t)__tmp + _len_ip_len);
	} else if (ip_len == NULL) {
		ms->ms_ip_len = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(2, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (client_ctx) memcpy((void*)client_ctx, __tmp_client_ctx, _len_client_ctx);
		if (client_ip) memcpy((void*)client_ip, __tmp_client_ip, _len_client_ip);
		if (ip_len) memcpy((void*)ip_len, __tmp_ip_len, _len_ip_len);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_set_block(int* retval, mbedtls_net_context* ctx)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(*ctx);

	ms_ocall_mbedtls_net_set_block_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_set_block_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	ocalloc_size += (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) ? _len_ctx : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_set_block_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_set_block_t));

	if (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memcpy(__tmp_ctx, ctx, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
	} else if (ctx == NULL) {
		ms->ms_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(3, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) memcpy((void*)ctx, __tmp_ctx, _len_ctx);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_set_nonblock(int* retval, mbedtls_net_context* ctx)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(*ctx);

	ms_ocall_mbedtls_net_set_nonblock_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_set_nonblock_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	ocalloc_size += (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) ? _len_ctx : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_set_nonblock_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_set_nonblock_t));

	if (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memcpy(__tmp_ctx, ctx, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
	} else if (ctx == NULL) {
		ms->ms_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(4, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) memcpy((void*)ctx, __tmp_ctx, _len_ctx);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_usleep(unsigned long int usec)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_mbedtls_net_usleep_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_usleep_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_usleep_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_usleep_t));

	ms->ms_usec = usec;
	status = sgx_ocall(5, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_recv(int* retval, mbedtls_net_context* ctx, unsigned char* buf, size_t len)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(*ctx);
	size_t _len_buf = len;

	ms_ocall_mbedtls_net_recv_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_recv_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	void *__tmp_buf = NULL;
	ocalloc_size += (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) ? _len_ctx : 0;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_recv_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_recv_t));

	if (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memcpy(__tmp_ctx, ctx, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
	} else if (ctx == NULL) {
		ms->ms_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (unsigned char*)__tmp;
		__tmp_buf = __tmp;
		memset(__tmp_buf, 0, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_len = len;
	status = sgx_ocall(6, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) memcpy((void*)ctx, __tmp_ctx, _len_ctx);
		if (buf) memcpy((void*)buf, __tmp_buf, _len_buf);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_send(int* retval, mbedtls_net_context* ctx, const unsigned char* buf, size_t len)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(*ctx);
	size_t _len_buf = len;

	ms_ocall_mbedtls_net_send_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_send_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	ocalloc_size += (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) ? _len_ctx : 0;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_send_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_send_t));

	if (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memcpy(__tmp_ctx, ctx, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
	} else if (ctx == NULL) {
		ms->ms_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (unsigned char*)__tmp;
		memcpy(__tmp, buf, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_len = len;
	status = sgx_ocall(7, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) memcpy((void*)ctx, __tmp_ctx, _len_ctx);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_recv_timeout(int* retval, mbedtls_net_context* ctx, unsigned char* buf, size_t len, uint32_t timeout)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(*ctx);
	size_t _len_buf = len;

	ms_ocall_mbedtls_net_recv_timeout_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_recv_timeout_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	void *__tmp_buf = NULL;
	ocalloc_size += (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) ? _len_ctx : 0;
	ocalloc_size += (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_recv_timeout_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_recv_timeout_t));

	if (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memcpy(__tmp_ctx, ctx, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
	} else if (ctx == NULL) {
		ms->ms_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (buf != NULL && sgx_is_within_enclave(buf, _len_buf)) {
		ms->ms_buf = (unsigned char*)__tmp;
		__tmp_buf = __tmp;
		memset(__tmp_buf, 0, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
	} else if (buf == NULL) {
		ms->ms_buf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_len = len;
	ms->ms_timeout = timeout;
	status = sgx_ocall(8, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) memcpy((void*)ctx, __tmp_ctx, _len_ctx);
		if (buf) memcpy((void*)buf, __tmp_buf, _len_buf);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_free(mbedtls_net_context* ctx)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(*ctx);

	ms_ocall_mbedtls_net_free_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_free_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	ocalloc_size += (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) ? _len_ctx : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_free_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_free_t));

	if (ctx != NULL && sgx_is_within_enclave(ctx, _len_ctx)) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memcpy(__tmp_ctx, ctx, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
	} else if (ctx == NULL) {
		ms->ms_ctx = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(9, ms);

	if (status == SGX_SUCCESS) {
		if (ctx) memcpy((void*)ctx, __tmp_ctx, _len_ctx);
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_print_string(int* retval, const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_string_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_string_t);
	void *__tmp = NULL;

	ocalloc_size += (str != NULL && sgx_is_within_enclave(str, _len_str)) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_string_t));

	if (str != NULL && sgx_is_within_enclave(str, _len_str)) {
		ms->ms_str = (char*)__tmp;
		memcpy(__tmp, str, _len_str);
		__tmp = (void *)((size_t)__tmp + _len_str);
	} else if (str == NULL) {
		ms->ms_str = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(10, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
	}
	sgx_ocfree();
	return status;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
