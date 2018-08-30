using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Nethereum;
using Nethereum.Web3;
using Nethereum.Contracts;
using System.Numerics;
using Nethereum.Hex.HexTypes;
using Nethereum.RPC.Eth.DTOs;
using Elliptic;
using System.Security.Cryptography;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Crypto.Modes;
using Org.BouncyCastle.Crypto.Engines;

namespace ManagedAuction
{
    public static class Bidders
    {
        private static Web3 web3;
        private static Function submitBid, SGXDHPUBLICKEY, initialDeposit, winnerIndex, winnerBid, index;
        public static void Initialize(string contractABI, string contractAddress, string provider = "HTTP://127.0.0.1:8545")
        {
            web3 = new Web3(provider);
            Contract auctionContract = web3.Eth.GetContract(contractABI, contractAddress);
            submitBid = auctionContract.GetFunction(nameof(submitBid));
            SGXDHPUBLICKEY = auctionContract.GetFunction(nameof(SGXDHPUBLICKEY));
            initialDeposit = auctionContract.GetFunction(nameof(initialDeposit));
            winnerBid = auctionContract.GetFunction(nameof(winnerBid));
            winnerIndex = auctionContract.GetFunction(nameof(winnerIndex));
            index = auctionContract.GetFunction(nameof(index));
        }

        public static string WhoIsTheWinner()
        {
            Initialize(Auctioneer.ContractABI, Auctioneer.ContractAddress);
            ushort _winnerIndex = winnerIndex.CallAsync<ushort>().Result;
            uint _winnerBid = winnerBid.CallAsync<uint>().Result;
            string _winnerAddress = index.CallAsync<string>(_winnerIndex).Result;
            return $"Winner's address: {_winnerAddress}\nBid: {_winnerBid}";
        }

        public static void SubmitBid(uint bid, int accountIndex)
        {
            string bidderAccount = Auctioneer.BiddersAccounts[accountIndex];
            HexBigInteger deposit = new HexBigInteger(initialDeposit.CallAsync<BigInteger>().Result);
            byte[] cipher, bidderPublicKey;
            EncryptBid(bid, out cipher, out bidderPublicKey);
            submitBid.SendTransactionAsync(bidderAccount, new HexBigInteger(3000000), deposit, cipher,bidderPublicKey).Wait();
        }
        #region Helper Functions
        private static void EncryptBid(uint bid, out byte[] cipher, out byte[] bidderPublicKey)
        {
            byte[] sgxECDH = SGXDHPUBLICKEY.CallAsync<byte[]>().Result;            
            byte[] prvKey = Curve25519.CreateRandomPrivateKey();
            bidderPublicKey = Curve25519.GetPublicKey(prvKey);
            byte[] symmetricKey = Curve25519.GetSharedSecret(prvKey, sgxECDH);
            Array.Resize(ref symmetricKey, 16);
            byte[] iv = new byte[12];
            RNGCryptoServiceProvider.Create().GetBytes(iv);
            AeadParameters parameters = new AeadParameters(new KeyParameter(symmetricKey), 128, iv);
            GcmBlockCipher aes = new GcmBlockCipher(new AesEngine());
            aes.Init(true, parameters);
            byte[] output = new byte[32];
            int x = aes.ProcessBytes(BitConverter.GetBytes(bid), 0, sizeof(uint), output, 0);
            aes.DoFinal(output, 0);
            byte[] mac = aes.GetMac();
            cipher = new byte[32];
            bidderPublicKey = new byte[32];
        }
        #endregion
    }
}
