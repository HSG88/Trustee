
# define ENCLAVE_FILENAME "Enclave.signed.dll"
extern "C"
{
	__declspec(dllexport) bool CreateEnclave();
	__declspec(dllexport) void DestroyEnclave();
	__declspec(dllexport) int GenerateKeys(unsigned char sealed[1024], unsigned char sgxAddress[20], unsigned char dhPublicKey[32]);
	__declspec(dllexport) int GetAuctionWinner(unsigned char* sealed, unsigned int sealedLen, unsigned char* cipher, unsigned int cipherLen, unsigned char contractAddress[20], unsigned char transaction[512]);
};
