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
    public static class Auctioneer
    {
        private static byte[] _sgxAddress = new byte[20], _dhPublicKey = new byte[32];
        private static BigInteger t1, t2, t3, t4, d;
        private static Web3 web3;
        private static ManagedEnclave sgx;
        private static string auctioneerAddress, sgxAddress, dhPublicKey, contractBIN;
        public static string ContractAddress { get; private set; }
        public static string ContractABI { get; private set; }
        public static Function refund, reset, dispute, startAuction, setWinner, SealedBids, bids, GetLength;
        public static void Initialize(string provider = "HTTP://127.0.0.1:8545")
        {
            t1 = new BigInteger(20);
            t2 = new BigInteger(10);
            t3 = new BigInteger(10);
            t4 = new BigInteger(40);
            d = UnitConversion.Convert.ToWei(1, UnitConversion.EthUnit.Ether);
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
        public static void StartAuction()
        {
            var receipt = startAuction.SendTransactionAndWaitForReceiptAsync(auctioneerAddress, new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(d),null, sgxAddress, _dhPublicKey, t1, t2, t3, t4, d).Result;
            Console.WriteLine($"Gas Cost: {receipt.GasUsed.Value}");
        }
        public static void Dispute()
        {
            var receipt = dispute.SendTransactionAndWaitForReceiptAsync(auctioneerAddress, new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(0), null).Result;
            Console.WriteLine($"Gas Cost: {receipt.GasUsed.Value}");
        }
        public static void Refund()
        {
            var receipt = refund.SendTransactionAndWaitForReceiptAsync(auctioneerAddress, new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(0), null).Result;
            Console.WriteLine($"Gas Cost: {receipt.GasUsed.Value}");
        }
        public static void Reset()
        {
            var receipt = reset.SendTransactionAndWaitForReceiptAsync(auctioneerAddress, new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(0), null).Result;
            Console.WriteLine($"Gas Cost: {receipt.GasUsed.Value}");
        }
        public static void SetWinner()
        {
            int count = GetLength.CallAsync<int>().Result;
            byte[] contractAddress = BigInteger.Parse(ContractAddress.Substring(2), System.Globalization.NumberStyles.AllowHexSpecifier).ToByteArray().Reverse().ToArray();
            List<byte> lstcipher = new List<byte>();
            byte[] bid;
            for (int i = 0; i < count; i++)
            {
                bid = bids.CallAsync<byte[]>(i).Result;
                lstcipher.AddRange(bid);
            }
            byte[] sealedBids = lstcipher.ToArray();
            byte[] sealedSecret = File.ReadAllBytes("SealedSecrets");
            byte[] transaction = new byte[512];
            int len = sgx.SGX_GetAuctionWinner(ref sealedSecret, (uint)sealedSecret.Length, ref sealedBids, (uint)sealedBids.Length, ref contractAddress, ref transaction);
            Array.Resize(ref transaction, len);
            string tx = BitConverter.ToString(transaction).Replace("-", "");
            var r= web3.Eth.Transactions.SendRawTransaction.SendRequestAsync(tx).Result;            
        }
        #region Private Helper Methods
        private static void DeployContract()
        {            
            web3.TransactionManager.SendTransactionAsync(auctioneerAddress, sgxAddress, new HexBigInteger(d*5)).Wait(); //fund SGX Account so it can post transactions
            TransactionReceipt receipt = web3.Eth.DeployContract.SendRequestAndWaitForReceiptAsync(ContractABI, contractBIN, auctioneerAddress, new HexBigInteger(3000000), new HexBigInteger(1), new HexBigInteger(0), null).Result;
            Console.WriteLine($"Gas Cost: {receipt.GasUsed.Value}");
            Contract auctionContract = web3.Eth.GetContract(ContractABI, receipt.ContractAddress);
            ContractAddress = receipt.ContractAddress;
            dispute = auctionContract.GetFunction(nameof(Dispute));
            refund = auctionContract.GetFunction(nameof(Refund));
            reset = auctionContract.GetFunction(nameof(Reset));
            startAuction = auctionContract.GetFunction(nameof(StartAuction));
            setWinner = auctionContract.GetFunction(nameof(SetWinner));
            GetLength = auctionContract.GetFunction(nameof(GetLength));
            bids = auctionContract.GetFunction(nameof(bids));         
        }
        private static void CompileContract()
        {
            File.Delete("Auction.abi");
            File.Delete("Auction.bin");
            Process.Start(".\\solc.exe", " --abi --bin -o .\\ .\\Auction.sol").WaitForExit();            
            ContractABI = File.ReadAllText("Auction.abi");
            contractBIN = File.ReadAllText("Auction.bin");
        }
        private static void InitSGX()
        {
            sgx = new ManagedEnclave();
            byte[] _sealedSecret = new byte[2048];
            int sealedLength = sgx.SGX_GenerateKeys(ref _sealedSecret, ref _sgxAddress, ref _dhPublicKey);
            sgxAddress = "0x" + BitConverter.ToString(_sgxAddress).Replace("-", "");
            dhPublicKey = "0x" + BitConverter.ToString(_dhPublicKey).Replace("-", "");
            Array.Resize(ref _sealedSecret, sealedLength);
            File.WriteAllBytes("SealedSecrets", _sealedSecret);
        }
        #endregion
    }
}
