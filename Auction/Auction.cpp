// App.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <string.h>
#include <assert.h>

# include <Shlobj.h>

#include "sgx_urts.h"
#include "sgx_uae_service.h"
#include "Auction.h"
#include"Enclave_u.h"

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

int initialize_enclave(void)
{
	char token_path[MAX_PATH] = { '\0' };
	sgx_launch_token_t token = { 0 };
	sgx_status_t ret = SGX_ERROR_UNEXPECTED;
	int updated = 0;
	/* try to get the token saved in CSIDL_LOCAL_APPDATA */
	if (S_OK != SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, token_path)) {
		strncpy_s(token_path, _countof(token_path), TOKEN_FILENAME, sizeof(TOKEN_FILENAME));
	}
	else {
		strncat_s(token_path, _countof(token_path), "\\" TOKEN_FILENAME, sizeof(TOKEN_FILENAME) + 2);
	}

	/* open the token file */
	HANDLE token_handler = CreateFileA(token_path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	if (token_handler == INVALID_HANDLE_VALUE) {
		printf("Warning: Failed to create/open the launch token file \"%s\".\n", token_path);
	}
	else {
		/* read the token from saved file */
		DWORD read_num = 0;
		ReadFile(token_handler, token, sizeof(sgx_launch_token_t), &read_num, NULL);
		if (read_num != 0 && read_num != sizeof(sgx_launch_token_t)) {
			/* if token is invalid, clear the buffer */
			memset(&token, 0x0, sizeof(sgx_launch_token_t));
			printf("Warning: Invalid launch token read from \"%s\".\n", token_path);
		}
	}
	/* Step 2: call sgx_create_enclave to initialize an enclave instance */
	/* Debug Support: set 2nd parameter to 1 */
	ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);
	if (ret != SGX_SUCCESS) {
		print_error_message(ret);
		if (token_handler != INVALID_HANDLE_VALUE)
			CloseHandle(token_handler);
		return -1;
	}

	/* Step 3: save the launch token if it is updated */
	if (updated == FALSE || token_handler == INVALID_HANDLE_VALUE) {
		/* if the token is not updated, or file handler is invalid, do not perform saving */
		if (token_handler != INVALID_HANDLE_VALUE)
			CloseHandle(token_handler);
		return 0;
	}

	/* flush the file cache */
	FlushFileBuffers(token_handler);
	/* set access offset to the begin of the file */
	SetFilePointer(token_handler, 0, NULL, FILE_BEGIN);

	/* write back the token */
	DWORD write_num = 0;
	WriteFile(token_handler, token, sizeof(sgx_launch_token_t), &write_num, NULL);
	if (write_num != sizeof(sgx_launch_token_t))
		printf("Warning: Failed to save launch token to \"%s\".\n", token_path);
	CloseHandle(token_handler);
	return 0;
}




/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
	(void)(argc);
	(void)(argv);

	/* Initialize the enclave */
	if (initialize_enclave() < 0) {
		printf("Enter a character before exit ...\n");
		getchar();
		return -1;
	}

	/* Utilize SGX trusted calls*/
	sgx_sealed_data_t* sealed = (sgx_sealed_data_t*)malloc(624);
	size_t len;
	int ret;
	unsigned char pubKey[64] = { 0 }, address[20] = { 0 }, dhPublicKey[32];
	EnclaveStart(global_eid, &ret, sealed, &len, pubKey, address, dhPublicKey);
	BID bids[10];
	for (int i = 0; i<10; i++)
		BidderEncrypt(global_eid, dhPublicKey, &bids[i]);
	uint32_t index, max;
	uint8_t sig[32];
	EnclaveAuctionWinner(global_eid, bids, 10, &index, &max, sig);
	printf("Winner = %u with index =%u\n", max, index);

	/* Destroy the enclave */
	sgx_destroy_enclave(global_eid);

	printf("Info: SampleEnclave successfully returned.\n");

	printf("Enter a character before exit ...\n");
	getchar();
	return 0;
}