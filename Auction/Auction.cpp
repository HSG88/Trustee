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

void HexToBinary(uint8_t* input, uint8_t* output, size_t size)
{
	uint8_t byte1, byte2;
	for (int i = 0; i < size; i++)
	{
		byte1 = *input++;
		byte2 = *input++;
		if (byte1 >= '0' && byte1 <= '9') byte1 -= '0';
		else if (byte1 >= 'A' && byte1 <= 'F') byte1 = byte1- 'A' + 10;
		else if (byte1 >= 'a' && byte1 <= 'f') byte1 = byte1 - 'a' + 10;
		if (byte2 >= '0' && byte2 <= '9') byte2 -= '0';
		else if (byte2 >= 'A' && byte2 <= 'F') byte2 = byte2 - 'A' + 10;
		else if (byte2 >= 'a' && byte2 <= 'f') byte2 = byte2 - 'a' + 10;
		output[i] = (byte1 << 4) | byte2;	
	}
}

void BinaryToHex(uint8_t* input, uint8_t* output, size_t size)
{
	uint8_t byte1, byte2;
	for (int i = 0; i < size; i+=2)
	{
		byte1 = *input >> 4;
		byte2 = *input & 0xf;
		if (byte1 >= 0 && byte1 <= 9) byte1 += '0';
		else if (byte1 >= 10 && byte1 <= 15) byte1 += 'A' + 10;
		if (byte2 >= 0 && byte2 <= 9) byte2 += '0';
		else if (byte2 >= 10 && byte2 <= 15) byte2 += 'A' + 10;
		output[i] = byte1;
		output[i + 1] = byte2;
	}
}

void Dump(char* title, uint8_t *input, size_t size)
{
	printf("%s: ", title);
	for (int i = 0; i < size; i++)
		printf("%02X", input[i]);
	printf("\n");
}

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

void StartSGX()
{
	HANDLE hFile = CreateFile("sealedData", GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	size_t sealedLen = 1024;
	DWORD tmpLen;
	sgx_sealed_data_t* sealed = (sgx_sealed_data_t*)malloc(sealedLen);
	uint8_t sgxAddress[20] = { 0 }, dhPublicKey[32];
	EnclaveStart(global_eid,sealed, sealedLen, &sealedLen, sgxAddress, dhPublicKey);
	WriteFile(hFile, (uint8_t*)&sealedLen, sizeof(size_t), &tmpLen, NULL);
	WriteFile(hFile, (uint8_t*)sealed, sealedLen, &tmpLen, NULL);
	WriteFile(hFile, sgxAddress, sizeof(sgxAddress), &tmpLen, NULL);
	WriteFile(hFile, dhPublicKey, sizeof(dhPublicKey), &tmpLen, NULL);
	CloseHandle(hFile);
	Dump("SGX Address: ", sgxAddress, sizeof(sgxAddress));
	Dump("SGX ECDH Public Key: ", dhPublicKey, sizeof(dhPublicKey));
}

void GetAuctionWinner()
{
	//read sealed Data
	HANDLE hFile = CreateFile("sealedData", GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	size_t sealedLen;
	DWORD tmpLen;
	ReadFile(hFile, (uint8_t*)&sealedLen, sizeof(size_t), &tmpLen, NULL);
	sgx_sealed_data_t* sealed = (sgx_sealed_data_t*)malloc(sealedLen);
	ReadFile(hFile, (uint8_t*)sealed, sealedLen, &tmpLen, NULL);
	CloseHandle(hFile);
	//read contract address and bids ciphertext
	hFile = CreateFile("bids", GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	uint8_t contractAddress[20], *cipher;
	uint32_t cipherLen;
	ReadFile(hFile, contractAddress, sizeof(contractAddress), &tmpLen, NULL);
	ReadFile(hFile, (uint8_t*)&cipherLen, sizeof(cipherLen), &tmpLen, NULL);
	cipher = (uint8_t*)malloc(cipherLen);
	ReadFile(hFile, cipher, cipherLen, &tmpLen, NULL);
	CloseHandle(hFile);
	//submit data to SGX and get raw transaction
	size_t transactionLen = 512;
	uint8_t* transaction = (uint8_t*)malloc(transactionLen);
	EnclaveGetAuctionWinner(global_eid, sealed, sealedLen, cipher, cipherLen, contractAddress, transaction, transactionLen, &transactionLen);
	hFile = CreateFile("transaction", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, transaction, transactionLen, &tmpLen, NULL);
	CloseHandle(hFile);
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
	
	
	StartSGX();
	/* Destroy the enclave */
	sgx_destroy_enclave(global_eid);

	printf("Info: SampleEnclave successfully returned.\n");

	printf("Enter a character before exit ...\n");
	getchar(); getchar();
	return 0;
}