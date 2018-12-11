using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App
{
    static class Enclave
    {
        private static byte[] _sealedSecret = new byte[2048], _sgxAddress = new byte[20], _dhPublicKey = new byte[32];
        public static byte[] PublicKey { get { return _dhPublicKey; } }
        private static ManagedEnclave sgx;
        public static void InitializeEnclave(out string EnclaveAddress, out string EnclavePublicKey)
        {
            sgx = new ManagedEnclave();            
            int sealedLength = sgx.SGX_GenerateKeys(ref _sealedSecret, ref _sgxAddress, ref _dhPublicKey);
            EnclaveAddress = "0x" + BitConverter.ToString(_sgxAddress).Replace("-", "");
            EnclavePublicKey = "0x" + BitConverter.ToString(_dhPublicKey).Replace("-", "");
            Array.Resize(ref _sealedSecret, sealedLength);
            File.WriteAllBytes("SealedSecrets", _sealedSecret);
        }
        public static void EncryptBid(uint bid, ref byte[] bidCT, ref byte[] bidPK)
        {
            sgx.SGX_EncryptBid(ref _dhPublicKey, bid, ref bidPK, ref bidCT);
        }
        public static byte[] GetSetWinnerRawTransaction(byte[] bids, byte[] contractAddress)
        {
            byte[] sealedSecret = File.ReadAllBytes("SealedSecrets");
            byte[] transaction = new byte[512];
            int len = sgx.SGX_GetAuctionWinner(ref sealedSecret, (uint)sealedSecret.Length, ref bids, (uint)bids.Length, ref contractAddress, ref transaction);
            Array.Resize(ref transaction, len);
            return transaction;
        }
    }
}
