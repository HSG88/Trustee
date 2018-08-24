#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

#include <stdlib.h>
#include <assert.h>

#if defined(__cplusplus)
extern "C" {
#endif
	int EnclaveSign(const uint8_t *data, size_t in_len, uint8_t *rr, uint8_t *ss, uint8_t *vv);


#if defined(__cplusplus)
}
#endif

#endif/* !_ENCLAVE_H_ */