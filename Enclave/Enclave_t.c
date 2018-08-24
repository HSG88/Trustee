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
	uint32_t* ms_winnerIndex;
	uint32_t* ms_winnerBid;
	uint8_t* ms_signature;
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
	size_t _len_sealed = 624;
	sgx_sealed_data_t* _in_sealed = NULL;
	size_t* _tmp_len = ms->ms_len;
	size_t _len_len = sizeof(*_tmp_len);
	size_t* _in_len = NULL;
	uint8_t* _tmp_contractPublicKey = ms->ms_contractPublicKey;
	size_t _len_contractPublicKey = 64 * sizeof(*_tmp_contractPublicKey);
	uint8_t* _in_contractPublicKey = NULL;
	uint8_t* _tmp_address = ms->ms_address;
	size_t _len_address = 20 * sizeof(*_tmp_address);
	uint8_t* _in_address = NULL;
	uint8_t* _tmp_encryptPublicKey = ms->ms_encryptPublicKey;
	size_t _len_encryptPublicKey = 32 * sizeof(*_tmp_encryptPublicKey);
	uint8_t* _in_encryptPublicKey = NULL;

	CHECK_UNIQUE_POINTER(_tmp_sealed, _len_sealed);
	CHECK_UNIQUE_POINTER(_tmp_len, _len_len);
	CHECK_UNIQUE_POINTER(_tmp_contractPublicKey, _len_contractPublicKey);
	CHECK_UNIQUE_POINTER(_tmp_address, _len_address);
	CHECK_UNIQUE_POINTER(_tmp_encryptPublicKey, _len_encryptPublicKey);

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
	if (_tmp_len != NULL && _len_len != 0) {
		if ((_in_len = (size_t*)malloc(_len_len)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_len, 0, _len_len);
	}
	if (_tmp_contractPublicKey != NULL && _len_contractPublicKey != 0) {
		if ((_in_contractPublicKey = (uint8_t*)malloc(_len_contractPublicKey)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_contractPublicKey, 0, _len_contractPublicKey);
	}
	if (_tmp_address != NULL && _len_address != 0) {
		if ((_in_address = (uint8_t*)malloc(_len_address)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_address, 0, _len_address);
	}
	if (_tmp_encryptPublicKey != NULL && _len_encryptPublicKey != 0) {
		if ((_in_encryptPublicKey = (uint8_t*)malloc(_len_encryptPublicKey)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_encryptPublicKey, 0, _len_encryptPublicKey);
	}

	ms->ms_retval = EnclaveStart(_in_sealed, _in_len, _in_contractPublicKey, _in_address, _in_encryptPublicKey);
err:
	if (_in_sealed) {
		memcpy(_tmp_sealed, _in_sealed, _len_sealed);
		free(_in_sealed);
	}
	if (_in_len) {
		memcpy(_tmp_len, _in_len, _len_len);
		free(_in_len);
	}
	if (_in_contractPublicKey) {
		memcpy(_tmp_contractPublicKey, _in_contractPublicKey, _len_contractPublicKey);
		free(_in_contractPublicKey);
	}
	if (_in_address) {
		memcpy(_tmp_address, _in_address, _len_address);
		free(_in_address);
	}
	if (_in_encryptPublicKey) {
		memcpy(_tmp_encryptPublicKey, _in_encryptPublicKey, _len_encryptPublicKey);
		free(_in_encryptPublicKey);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_EnclaveUnsealPrivateKeys(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_EnclaveUnsealPrivateKeys_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_EnclaveUnsealPrivateKeys_t* ms = SGX_CAST(ms_EnclaveUnsealPrivateKeys_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sgx_sealed_data_t* _tmp_sealed = ms->ms_sealed;
	size_t _len_sealed = 624;
	sgx_sealed_data_t* _in_sealed = NULL;

	CHECK_UNIQUE_POINTER(_tmp_sealed, _len_sealed);

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

	ms->ms_retval = EnclaveUnsealPrivateKeys(_in_sealed);
err:
	if (_in_sealed) free(_in_sealed);

	return status;
}

static sgx_status_t SGX_CDECL sgx_EnclaveAuctionWinner(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_EnclaveAuctionWinner_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_EnclaveAuctionWinner_t* ms = SGX_CAST(ms_EnclaveAuctionWinner_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	BID* _tmp_bids = ms->ms_bids;
	size_t _tmp__count = ms->ms__count;
	size_t _len_bids = _tmp__count * sizeof(*_tmp_bids);
	BID* _in_bids = NULL;
	uint32_t* _tmp_winnerIndex = ms->ms_winnerIndex;
	size_t _len_winnerIndex = sizeof(*_tmp_winnerIndex);
	uint32_t* _in_winnerIndex = NULL;
	uint32_t* _tmp_winnerBid = ms->ms_winnerBid;
	size_t _len_winnerBid = sizeof(*_tmp_winnerBid);
	uint32_t* _in_winnerBid = NULL;
	uint8_t* _tmp_signature = ms->ms_signature;
	size_t _len_signature = 32 * sizeof(*_tmp_signature);
	uint8_t* _in_signature = NULL;

	if (sizeof(*_tmp_bids) != 0 &&
		(size_t)_tmp__count > (SIZE_MAX / sizeof(*_tmp_bids))) {
		return SGX_ERROR_INVALID_PARAMETER;
	}

	CHECK_UNIQUE_POINTER(_tmp_bids, _len_bids);
	CHECK_UNIQUE_POINTER(_tmp_winnerIndex, _len_winnerIndex);
	CHECK_UNIQUE_POINTER(_tmp_winnerBid, _len_winnerBid);
	CHECK_UNIQUE_POINTER(_tmp_signature, _len_signature);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_bids != NULL && _len_bids != 0) {
		_in_bids = (BID*)malloc(_len_bids);
		if (_in_bids == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_bids, _tmp_bids, _len_bids);
	}
	if (_tmp_winnerIndex != NULL && _len_winnerIndex != 0) {
		if ((_in_winnerIndex = (uint32_t*)malloc(_len_winnerIndex)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_winnerIndex, 0, _len_winnerIndex);
	}
	if (_tmp_winnerBid != NULL && _len_winnerBid != 0) {
		if ((_in_winnerBid = (uint32_t*)malloc(_len_winnerBid)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_winnerBid, 0, _len_winnerBid);
	}
	if (_tmp_signature != NULL && _len_signature != 0) {
		if ((_in_signature = (uint8_t*)malloc(_len_signature)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_signature, 0, _len_signature);
	}

	EnclaveAuctionWinner(_in_bids, _tmp__count, _in_winnerIndex, _in_winnerBid, _in_signature);
err:
	if (_in_bids) free(_in_bids);
	if (_in_winnerIndex) {
		memcpy(_tmp_winnerIndex, _in_winnerIndex, _len_winnerIndex);
		free(_in_winnerIndex);
	}
	if (_in_winnerBid) {
		memcpy(_tmp_winnerBid, _in_winnerBid, _len_winnerBid);
		free(_in_winnerBid);
	}
	if (_in_signature) {
		memcpy(_tmp_signature, _in_signature, _len_signature);
		free(_in_signature);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_BidderEncrypt(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_BidderEncrypt_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_BidderEncrypt_t* ms = SGX_CAST(ms_BidderEncrypt_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	uint8_t* _tmp_sgxPublicKey = ms->ms_sgxPublicKey;
	size_t _len_sgxPublicKey = 32;
	uint8_t* _in_sgxPublicKey = NULL;
	BID* _tmp_bid = ms->ms_bid;
	size_t _len_bid = 64;
	BID* _in_bid = NULL;

	CHECK_UNIQUE_POINTER(_tmp_sgxPublicKey, _len_sgxPublicKey);
	CHECK_UNIQUE_POINTER(_tmp_bid, _len_bid);

	//
	// fence after pointer checks
	//
	sgx_lfence();

	if (_tmp_sgxPublicKey != NULL && _len_sgxPublicKey != 0) {
		_in_sgxPublicKey = (uint8_t*)malloc(_len_sgxPublicKey);
		if (_in_sgxPublicKey == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_sgxPublicKey, _tmp_sgxPublicKey, _len_sgxPublicKey);
	}
	if (_tmp_bid != NULL && _len_bid != 0) {
		if ((_in_bid = (BID*)malloc(_len_bid)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_bid, 0, _len_bid);
	}

	BidderEncrypt(_in_sgxPublicKey, _in_bid);
err:
	if (_in_sgxPublicKey) free(_in_sgxPublicKey);
	if (_in_bid) {
		memcpy(_tmp_bid, _in_bid, _len_bid);
		free(_in_bid);
	}

	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[4];
} g_ecall_table = {
	4,
	{
		{(void*)(uintptr_t)sgx_EnclaveStart, 0},
		{(void*)(uintptr_t)sgx_EnclaveUnsealPrivateKeys, 0},
		{(void*)(uintptr_t)sgx_EnclaveAuctionWinner, 0},
		{(void*)(uintptr_t)sgx_BidderEncrypt, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[11][4];
} g_dyn_entry_table = {
	11,
	{
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
		{0, 0, 0, 0, },
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
