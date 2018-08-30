#using <System.dll>
using namespace System;
extern "C"
{
	__declspec(dllimport) bool CreateEnclave();
	__declspec(dllimport) void DestroyEnclave();
	__declspec(dllimport) int GenerateKeys(unsigned char sealed[2048], unsigned char sgxAddress[20], unsigned char dhPublicKey[32]);
	__declspec(dllimport) int GetAuctionWinner(unsigned char* sealed, unsigned int sealedLen, unsigned char* cipher, unsigned int cipherLen, unsigned char contractAddress[20], unsigned char transaction[512]);
};
public ref class ManagedEnclave
{
	
public:
	ManagedEnclave(bool% success) {
		success = CreateEnclave();
	}
	~ManagedEnclave()
	{
		DestroyEnclave();
	}
	int SGX_GenerateKeys(array<unsigned char>^% sealed, array<unsigned char>^% sgxAddress, array<unsigned char>^% dhPublicKey )
	{
		pin_ptr<unsigned char> pSealed = &sealed[0];
		pin_ptr<unsigned char> pAddress = &sgxAddress[0];
		pin_ptr<unsigned char> pDHPublicKey = &dhPublicKey[0];
		return GenerateKeys(pSealed, pAddress, pDHPublicKey);
	}
	int SGX_GetAuctionWinner(array<unsigned char>^% sealed, unsigned int sealedLen, array<unsigned char>^% cipher, unsigned int cipherLen, array<unsigned char>^% contractAddress, array<unsigned char>^% transaction)
	{
		pin_ptr<unsigned char> pSealed = &sealed[0];
		pin_ptr<unsigned char> pCipher = &cipher[0];
		pin_ptr<unsigned char> pAddress = &contractAddress[0];
		pin_ptr<unsigned char> pTransaction = &transaction[0];
		return GetAuctionWinner(pSealed, sealedLen, pCipher, cipherLen, pAddress, pTransaction);
	}
};