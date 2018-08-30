using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Nethereum.Web3;
using Nethereum;
using System.IO;
using System.Diagnostics;
using Nethereum.Hex.HexTypes;
using Nethereum.RPC.Eth.DTOs;
using Nethereum.Util;
using System.Numerics;
using Nethereum.Contracts;
using Nethereum.ABI.FunctionEncoding.Attributes;

namespace ManagedAuction
{
    [FunctionOutput]
    class Bid
    {
        [Parameter("bytes32", "bidCipher", 1)]
        public byte[] Cipher { get; set; }
        [Parameter("bytes32", "ecdhPublicKey", 2)]
        public byte[] ECDHPublicKey { get; set; }
    }
    public static class Auctioneer
    {
        private static BigInteger bidingInterval, sgxInterval, initialDeposit;
        private static Web3 web3;
        private static ManagedEnclave sgx;
        private static string auctioneerAddress, sgxAddress, dhPublicKey, contractBIN;
        public static string ContractAddress { get; private set; }
        public static string ContractABI { get; private set; }
        public static Function setWinner, bidders, index, getIndexLength;
        public static void Initialize(string provider = "HTTP://127.0.0.1:8545")
        {
            bidingInterval = new BigInteger(20);
            sgxInterval = new BigInteger(10);
            initialDeposit = UnitConversion.Convert.ToWei(5, UnitConversion.EthUnit.Ether);
            web3 = new Web3(provider);
            auctioneerAddress = web3.Personal.ListAccounts.SendRequestAsync().Result[0];

            InitSGX();
            CompileContract();
            DeployContract();
        }
        public static string[] BiddersAccounts { get
            {
                return web3.Personal.ListAccounts.SendRequestAsync().Result;
            } }
        public static void DetermineWinner()
        {
            int biddersCounts = getIndexLength.CallAsync<int>().Result;
            byte[] contractAddress = BigInteger.Parse(ContractAddress.Substring(2),System.Globalization.NumberStyles.AllowHexSpecifier).ToByteArray().Reverse().ToArray();
            List<byte> lstcipher = new List<byte>();
            Bid bid;
            for(int i =0; i< biddersCounts; i++)
            {
                bid = bidders.CallDeserializingToObjectAsync<Bid>(index.CallAsync<string>(i).Result).Result;
                lstcipher.AddRange(bid.Cipher);
                lstcipher.AddRange(bid.ECDHPublicKey);
            }
            byte[] cipher = lstcipher.ToArray();
            byte[] hash = new Nethereum.Util.Sha3Keccack().CalculateHash(cipher);
            byte[] sealedSecret = File.ReadAllBytes("SealedSecrets");
            byte[] transaction = new byte[512];
            int len = sgx.SGX_GetAuctionWinner(ref sealedSecret, (uint)sealedSecret.Length, ref cipher, (uint)cipher.Length, ref contractAddress, ref transaction);
            Array.Resize(ref transaction, len);
            string tx = BitConverter.ToString(transaction).Replace("-", "");
            var r= web3.Eth.Transactions.SendRawTransaction.SendRequestAsync(tx).Result;
        }
        #region Private Helper Methods
        private static void DeployContract()
        {            
            web3.TransactionManager.SendTransactionAsync(auctioneerAddress, sgxAddress, new HexBigInteger(initialDeposit)).Wait(); //fund SGX Account so it can post transactions
            TransactionReceipt receipt = web3.Eth.DeployContract.SendRequestAndWaitForReceiptAsync(ContractABI, contractBIN, auctioneerAddress, new HexBigInteger(3000000), new HexBigInteger(1), new HexBigInteger(0), null, bidingInterval, sgxInterval, initialDeposit).Result;
            Contract auctionContract = web3.Eth.GetContract(ContractABI, receipt.ContractAddress);
            ContractAddress = receipt.ContractAddress;
            setWinner = auctionContract.GetFunction(nameof(setWinner));
            bidders = auctionContract.GetFunction(nameof(bidders));
            index = auctionContract.GetFunction(nameof(index));
            getIndexLength = auctionContract.GetFunction(nameof(getIndexLength));
        }
        private static void CompileContract()
        {
            string contractCode = File.ReadAllText("Auction.sol");
            contractCode= contractCode.Replace("ADDRESSPLACEHOLDER", $"{sgxAddress}");
            contractCode= contractCode.Replace("DHPLACEHOLDER", $"{dhPublicKey}");
            File.WriteAllText("Temp.sol", contractCode);
            File.Delete("Auction.abi");
            File.Delete("Auction.bin");
            Process.Start(".\\solc.exe", " --abi --bin -o .\\ .\\Temp.sol").WaitForExit();            
            ContractABI = File.ReadAllText("Auction.abi");
            contractBIN = File.ReadAllText("Auction.bin");
        }
        private static void InitSGX()
        {
            bool success = false;
            sgx = new ManagedEnclave(ref success);
            if (!success)
                throw new Exception("Failed at initializing the SGX enclave");
            byte[] _sealedSecret = new byte[2048], _sgxAddress = new byte[20], _dhPublicKey = new byte[32];
            int sealedLength = sgx.SGX_GenerateKeys(ref _sealedSecret, ref _sgxAddress, ref _dhPublicKey);
            sgxAddress = "0x" + BitConverter.ToString(_sgxAddress).Replace("-", "");
            dhPublicKey = "0x" + BitConverter.ToString(_dhPublicKey).Replace("-", "");
            Array.Resize(ref _sealedSecret, sealedLength);
            File.WriteAllBytes("SealedSecrets", _sealedSecret);
        }
        #endregion
    }
}
