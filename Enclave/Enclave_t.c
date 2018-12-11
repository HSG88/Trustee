#include "Enclave_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */
#include "sgx_lfence.h" /* for sgx_lfence */

#include <errno.h>
#include <mbusafecrt.h> /* for memcpy_s etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_ENCLAVE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_within_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


typedef struct ms_Encrypt_t {
	uint8_t* ms_sgxPK;
	uint32_t ms_bid;
	uint8_t* ms_bidPK;
	uint8_t* ms_bidCT;
} ms_Encrypt_t;

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
	const char* ms_host;
	const char* ms_port;
	int ms_proto;
} ms_ocall_mbedtls_net_connect_t;

typedef struct ms_ocall_mbedtls_net_bind_t {
	int ms_retval;
	mbedtls_net_context* ms_ctx;
	const char* ms_bind_ip;
	const char* ms_port;
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
	const unsigned char* ms_buf;
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
	const char* ms_str;
} ms_ocall_print_string_t;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_Encrypt(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_Encrypt_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_Encrypt_t* ms = SGX_CAST(ms_Encrypt_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	uint8_t* _tmp_sgxPK = ms->ms_sgxPK;
	size_t _len_sgxPK = 32 * sizeof(uint8_t);
	uint8_t* _in_sgxPK = NULL;
	uint8_t* _tmp_bidPK = ms->ms_bidPK;
	size_t _len_bidPK = 32 * sizeof(uint8_t);
	uint8_t* _in_bidPK = NULL;
	uint8_t* _tmp_bidCT = ms->ms_bidCT;
	size_t _len_bidCT = 32 * sizeof(uint8_t);
	uint8_t* _in_bidCT = NULL;

	CHECK_UNIQUE_POINTER(_tmp_sgxPK, _len_sgxPK);
	CHECK_UNIQUE_POINTER(_tmp_bidPK, _len_bidPK);
	CHECK_UNIQUE_POINTER(_tmp_bidCT, _len_bidCT);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_sgxPK != NULL && _len_sgxPK != 0) {
		_in_sgxPK = (uint8_t*)malloc(_len_sgxPK);
		if (_in_sgxPK == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_sgxPK, _len_sgxPK, _tmp_sgxPK, _len_sgxPK)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}
	if (_tmp_bidPK != NULL && _len_bidPK != 0) {
		if ((_in_bidPK = (uint8_t*)malloc(_len_bidPK)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_bidPK, 0, _len_bidPK);
	}
	if (_tmp_bidCT != NULL && _len_bidCT != 0) {
		if ((_in_bidCT = (uint8_t*)malloc(_len_bidCT)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_bidCT, 0, _len_bidCT);
	}

	Encrypt(_in_sgxPK, ms->ms_bid, _in_bidPK, _in_bidCT);
err:
	if (_in_sgxPK) free(_in_sgxPK);
	if (_in_bidPK) {
		if (memcpy_s(_tmp_bidPK, _len_bidPK, _in_bidPK, _len_bidPK)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_bidPK);
	}
	if (_in_bidCT) {
		if (memcpy_s(_tmp_bidCT, _len_bidCT, _in_bidCT, _len_bidCT)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_bidCT);
	}

	return status;
}

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
	size_t _len_sealedLen = sizeof(size_t);
	size_t* _in_sealedLen = NULL;
	uint8_t* _tmp_address = ms->ms_address;
	size_t _len_address = 20 * sizeof(uint8_t);
	uint8_t* _in_address = NULL;
	uint8_t* _tmp_dhPublicKey = ms->ms_dhPublicKey;
	size_t _len_dhPublicKey = 32 * sizeof(uint8_t);
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
		if (memcpy_s(_tmp_sealed, _len_sealed, _in_sealed, _len_sealed)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_sealed);
	}
	if (_in_sealedLen) {
		if (memcpy_s(_tmp_sealedLen, _len_sealedLen, _in_sealedLen, _len_sealedLen)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_sealedLen);
	}
	if (_in_address) {
		if (memcpy_s(_tmp_address, _len_address, _in_address, _len_address)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_address);
	}
	if (_in_dhPublicKey) {
		if (memcpy_s(_tmp_dhPublicKey, _len_dhPublicKey, _in_dhPublicKey, _len_dhPublicKey)) {
			status = SGX_ERROR_UNEXPECTED;
		}
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
	size_t _len_contractAddress = 20 * sizeof(uint8_t);
	uint8_t* _in_contractAddress = NULL;
	uint8_t* _tmp_transaction = ms->ms_transaction;
	size_t _len_transaction = 512 * sizeof(uint8_t);
	uint8_t* _in_transaction = NULL;
	size_t* _tmp_transactionLen = ms->ms_transactionLen;
	size_t _len_transactionLen = sizeof(size_t);
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

		if (memcpy_s(_in_sealed, _len_sealed, _tmp_sealed, _len_sealed)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}
	if (_tmp_cipher != NULL && _len_cipher != 0) {
		_in_cipher = (uint8_t*)malloc(_len_cipher);
		if (_in_cipher == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_cipher, _len_cipher, _tmp_cipher, _len_cipher)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

	}
	if (_tmp_contractAddress != NULL && _len_contractAddress != 0) {
		_in_contractAddress = (uint8_t*)malloc(_len_contractAddress);
		if (_in_contractAddress == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		if (memcpy_s(_in_contractAddress, _len_contractAddress, _tmp_contractAddress, _len_contractAddress)) {
			status = SGX_ERROR_UNEXPECTED;
			goto err;
		}

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
		if (memcpy_s(_tmp_transaction, _len_transaction, _in_transaction, _len_transaction)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_transaction);
	}
	if (_in_transactionLen) {
		if (memcpy_s(_tmp_transactionLen, _len_transactionLen, _in_transactionLen, _len_transactionLen)) {
			status = SGX_ERROR_UNEXPECTED;
		}
		free(_in_transactionLen);
	}

	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[3];
} g_ecall_table = {
	3,
	{
		{(void*)(uintptr_t)sgx_Encrypt, 0},
		{(void*)(uintptr_t)sgx_EnclaveStart, 0},
		{(void*)(uintptr_t)sgx_EnclaveGetAuctionWinner, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[11][3];
} g_dyn_entry_table = {
	11,
	{
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_mbedtls_net_connect(int* retval, mbedtls_net_context* ctx, const char* host, const char* port, int proto)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(mbedtls_net_context);
	size_t _len_host = host ? strlen(host) + 1 : 0;
	size_t _len_port = port ? strlen(port) + 1 : 0;

	ms_ocall_mbedtls_net_connect_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_connect_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;

	CHECK_ENCLAVE_POINTER(ctx, _len_ctx);
	CHECK_ENCLAVE_POINTER(host, _len_host);
	CHECK_ENCLAVE_POINTER(port, _len_port);

	ocalloc_size += (ctx != NULL) ? _len_ctx : 0;
	ocalloc_size += (host != NULL) ? _len_host : 0;
	ocalloc_size += (port != NULL) ? _len_port : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_connect_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_connect_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_connect_t);

	if (ctx != NULL) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		if (memcpy_s(__tmp_ctx, ocalloc_size, ctx, _len_ctx)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_ctx);
		ocalloc_size -= _len_ctx;
	} else {
		ms->ms_ctx = NULL;
	}
	
	if (host != NULL) {
		ms->ms_host = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, host, _len_host)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_host);
		ocalloc_size -= _len_host;
	} else {
		ms->ms_host = NULL;
	}
	
	if (port != NULL) {
		ms->ms_port = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, port, _len_port)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_port);
		ocalloc_size -= _len_port;
	} else {
		ms->ms_port = NULL;
	}
	
	ms->ms_proto = proto;
	status = sgx_ocall(0, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) {
			if (memcpy_s((void*)ctx, _len_ctx, __tmp_ctx, _len_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_bind(int* retval, mbedtls_net_context* ctx, const char* bind_ip, const char* port, int proto)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(mbedtls_net_context);
	size_t _len_bind_ip = bind_ip ? strlen(bind_ip) + 1 : 0;
	size_t _len_port = port ? strlen(port) + 1 : 0;

	ms_ocall_mbedtls_net_bind_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_bind_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;

	CHECK_ENCLAVE_POINTER(ctx, _len_ctx);
	CHECK_ENCLAVE_POINTER(bind_ip, _len_bind_ip);
	CHECK_ENCLAVE_POINTER(port, _len_port);

	ocalloc_size += (ctx != NULL) ? _len_ctx : 0;
	ocalloc_size += (bind_ip != NULL) ? _len_bind_ip : 0;
	ocalloc_size += (port != NULL) ? _len_port : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_bind_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_bind_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_bind_t);

	if (ctx != NULL) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		memset(__tmp_ctx, 0, _len_ctx);
		__tmp = (void *)((size_t)__tmp + _len_ctx);
		ocalloc_size -= _len_ctx;
	} else {
		ms->ms_ctx = NULL;
	}
	
	if (bind_ip != NULL) {
		ms->ms_bind_ip = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, bind_ip, _len_bind_ip)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_bind_ip);
		ocalloc_size -= _len_bind_ip;
	} else {
		ms->ms_bind_ip = NULL;
	}
	
	if (port != NULL) {
		ms->ms_port = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, port, _len_port)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_port);
		ocalloc_size -= _len_port;
	} else {
		ms->ms_port = NULL;
	}
	
	ms->ms_proto = proto;
	status = sgx_ocall(1, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) {
			if (memcpy_s((void*)ctx, _len_ctx, __tmp_ctx, _len_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_accept(int* retval, mbedtls_net_context* bind_ctx, mbedtls_net_context* client_ctx, void* client_ip, size_t buf_size, size_t* ip_len)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_bind_ctx = sizeof(mbedtls_net_context);
	size_t _len_client_ctx = sizeof(mbedtls_net_context);
	size_t _len_client_ip = buf_size;
	size_t _len_ip_len = sizeof(size_t);

	ms_ocall_mbedtls_net_accept_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_accept_t);
	void *__tmp = NULL;

	void *__tmp_client_ctx = NULL;
	void *__tmp_client_ip = NULL;
	void *__tmp_ip_len = NULL;

	CHECK_ENCLAVE_POINTER(bind_ctx, _len_bind_ctx);
	CHECK_ENCLAVE_POINTER(client_ctx, _len_client_ctx);
	CHECK_ENCLAVE_POINTER(client_ip, _len_client_ip);
	CHECK_ENCLAVE_POINTER(ip_len, _len_ip_len);

	ocalloc_size += (bind_ctx != NULL) ? _len_bind_ctx : 0;
	ocalloc_size += (client_ctx != NULL) ? _len_client_ctx : 0;
	ocalloc_size += (client_ip != NULL) ? _len_client_ip : 0;
	ocalloc_size += (ip_len != NULL) ? _len_ip_len : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_accept_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_accept_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_accept_t);

	if (bind_ctx != NULL) {
		ms->ms_bind_ctx = (mbedtls_net_context*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, bind_ctx, _len_bind_ctx)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_bind_ctx);
		ocalloc_size -= _len_bind_ctx;
	} else {
		ms->ms_bind_ctx = NULL;
	}
	
	if (client_ctx != NULL) {
		ms->ms_client_ctx = (mbedtls_net_context*)__tmp;
		__tmp_client_ctx = __tmp;
		memset(__tmp_client_ctx, 0, _len_client_ctx);
		__tmp = (void *)((size_t)__tmp + _len_client_ctx);
		ocalloc_size -= _len_client_ctx;
	} else {
		ms->ms_client_ctx = NULL;
	}
	
	if (client_ip != NULL) {
		ms->ms_client_ip = (void*)__tmp;
		__tmp_client_ip = __tmp;
		memset(__tmp_client_ip, 0, _len_client_ip);
		__tmp = (void *)((size_t)__tmp + _len_client_ip);
		ocalloc_size -= _len_client_ip;
	} else {
		ms->ms_client_ip = NULL;
	}
	
	ms->ms_buf_size = buf_size;
	if (ip_len != NULL) {
		ms->ms_ip_len = (size_t*)__tmp;
		__tmp_ip_len = __tmp;
		memset(__tmp_ip_len, 0, _len_ip_len);
		__tmp = (void *)((size_t)__tmp + _len_ip_len);
		ocalloc_size -= _len_ip_len;
	} else {
		ms->ms_ip_len = NULL;
	}
	
	status = sgx_ocall(2, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (client_ctx) {
			if (memcpy_s((void*)client_ctx, _len_client_ctx, __tmp_client_ctx, _len_client_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
		if (client_ip) {
			if (memcpy_s((void*)client_ip, _len_client_ip, __tmp_client_ip, _len_client_ip)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
		if (ip_len) {
			if (memcpy_s((void*)ip_len, _len_ip_len, __tmp_ip_len, _len_ip_len)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_set_block(int* retval, mbedtls_net_context* ctx)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(mbedtls_net_context);

	ms_ocall_mbedtls_net_set_block_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_set_block_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;

	CHECK_ENCLAVE_POINTER(ctx, _len_ctx);

	ocalloc_size += (ctx != NULL) ? _len_ctx : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_set_block_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_set_block_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_set_block_t);

	if (ctx != NULL) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		if (memcpy_s(__tmp_ctx, ocalloc_size, ctx, _len_ctx)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_ctx);
		ocalloc_size -= _len_ctx;
	} else {
		ms->ms_ctx = NULL;
	}
	
	status = sgx_ocall(3, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) {
			if (memcpy_s((void*)ctx, _len_ctx, __tmp_ctx, _len_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_set_nonblock(int* retval, mbedtls_net_context* ctx)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(mbedtls_net_context);

	ms_ocall_mbedtls_net_set_nonblock_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_set_nonblock_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;

	CHECK_ENCLAVE_POINTER(ctx, _len_ctx);

	ocalloc_size += (ctx != NULL) ? _len_ctx : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_set_nonblock_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_set_nonblock_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_set_nonblock_t);

	if (ctx != NULL) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		if (memcpy_s(__tmp_ctx, ocalloc_size, ctx, _len_ctx)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_ctx);
		ocalloc_size -= _len_ctx;
	} else {
		ms->ms_ctx = NULL;
	}
	
	status = sgx_ocall(4, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) {
			if (memcpy_s((void*)ctx, _len_ctx, __tmp_ctx, _len_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
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
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_usleep_t);

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
	size_t _len_ctx = sizeof(mbedtls_net_context);
	size_t _len_buf = len;

	ms_ocall_mbedtls_net_recv_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_recv_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	void *__tmp_buf = NULL;

	CHECK_ENCLAVE_POINTER(ctx, _len_ctx);
	CHECK_ENCLAVE_POINTER(buf, _len_buf);

	ocalloc_size += (ctx != NULL) ? _len_ctx : 0;
	ocalloc_size += (buf != NULL) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_recv_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_recv_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_recv_t);

	if (ctx != NULL) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		if (memcpy_s(__tmp_ctx, ocalloc_size, ctx, _len_ctx)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_ctx);
		ocalloc_size -= _len_ctx;
	} else {
		ms->ms_ctx = NULL;
	}
	
	if (buf != NULL) {
		ms->ms_buf = (unsigned char*)__tmp;
		__tmp_buf = __tmp;
		memset(__tmp_buf, 0, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
		ocalloc_size -= _len_buf;
	} else {
		ms->ms_buf = NULL;
	}
	
	ms->ms_len = len;
	status = sgx_ocall(6, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) {
			if (memcpy_s((void*)ctx, _len_ctx, __tmp_ctx, _len_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
		if (buf) {
			if (memcpy_s((void*)buf, _len_buf, __tmp_buf, _len_buf)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_send(int* retval, mbedtls_net_context* ctx, const unsigned char* buf, size_t len)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(mbedtls_net_context);
	size_t _len_buf = len;

	ms_ocall_mbedtls_net_send_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_send_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;

	CHECK_ENCLAVE_POINTER(ctx, _len_ctx);
	CHECK_ENCLAVE_POINTER(buf, _len_buf);

	ocalloc_size += (ctx != NULL) ? _len_ctx : 0;
	ocalloc_size += (buf != NULL) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_send_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_send_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_send_t);

	if (ctx != NULL) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		if (memcpy_s(__tmp_ctx, ocalloc_size, ctx, _len_ctx)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_ctx);
		ocalloc_size -= _len_ctx;
	} else {
		ms->ms_ctx = NULL;
	}
	
	if (buf != NULL) {
		ms->ms_buf = (const unsigned char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, buf, _len_buf)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_buf);
		ocalloc_size -= _len_buf;
	} else {
		ms->ms_buf = NULL;
	}
	
	ms->ms_len = len;
	status = sgx_ocall(7, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) {
			if (memcpy_s((void*)ctx, _len_ctx, __tmp_ctx, _len_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_recv_timeout(int* retval, mbedtls_net_context* ctx, unsigned char* buf, size_t len, uint32_t timeout)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(mbedtls_net_context);
	size_t _len_buf = len;

	ms_ocall_mbedtls_net_recv_timeout_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_recv_timeout_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;
	void *__tmp_buf = NULL;

	CHECK_ENCLAVE_POINTER(ctx, _len_ctx);
	CHECK_ENCLAVE_POINTER(buf, _len_buf);

	ocalloc_size += (ctx != NULL) ? _len_ctx : 0;
	ocalloc_size += (buf != NULL) ? _len_buf : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_recv_timeout_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_recv_timeout_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_recv_timeout_t);

	if (ctx != NULL) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		if (memcpy_s(__tmp_ctx, ocalloc_size, ctx, _len_ctx)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_ctx);
		ocalloc_size -= _len_ctx;
	} else {
		ms->ms_ctx = NULL;
	}
	
	if (buf != NULL) {
		ms->ms_buf = (unsigned char*)__tmp;
		__tmp_buf = __tmp;
		memset(__tmp_buf, 0, _len_buf);
		__tmp = (void *)((size_t)__tmp + _len_buf);
		ocalloc_size -= _len_buf;
	} else {
		ms->ms_buf = NULL;
	}
	
	ms->ms_len = len;
	ms->ms_timeout = timeout;
	status = sgx_ocall(8, ms);

	if (status == SGX_SUCCESS) {
		if (retval) *retval = ms->ms_retval;
		if (ctx) {
			if (memcpy_s((void*)ctx, _len_ctx, __tmp_ctx, _len_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
		if (buf) {
			if (memcpy_s((void*)buf, _len_buf, __tmp_buf, _len_buf)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_mbedtls_net_free(mbedtls_net_context* ctx)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ctx = sizeof(mbedtls_net_context);

	ms_ocall_mbedtls_net_free_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_mbedtls_net_free_t);
	void *__tmp = NULL;

	void *__tmp_ctx = NULL;

	CHECK_ENCLAVE_POINTER(ctx, _len_ctx);

	ocalloc_size += (ctx != NULL) ? _len_ctx : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_mbedtls_net_free_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_mbedtls_net_free_t));
	ocalloc_size -= sizeof(ms_ocall_mbedtls_net_free_t);

	if (ctx != NULL) {
		ms->ms_ctx = (mbedtls_net_context*)__tmp;
		__tmp_ctx = __tmp;
		if (memcpy_s(__tmp_ctx, ocalloc_size, ctx, _len_ctx)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_ctx);
		ocalloc_size -= _len_ctx;
	} else {
		ms->ms_ctx = NULL;
	}
	
	status = sgx_ocall(9, ms);

	if (status == SGX_SUCCESS) {
		if (ctx) {
			if (memcpy_s((void*)ctx, _len_ctx, __tmp_ctx, _len_ctx)) {
				sgx_ocfree();
				return SGX_ERROR_UNEXPECTED;
			}
		}
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


	CHECK_ENCLAVE_POINTER(str, _len_str);

	ocalloc_size += (str != NULL) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_string_t));
	ocalloc_size -= sizeof(ms_ocall_print_string_t);

	if (str != NULL) {
		ms->ms_str = (const char*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, str, _len_str)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_str);
		ocalloc_size -= _len_str;
	} else {
		ms->ms_str = NULL;
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
