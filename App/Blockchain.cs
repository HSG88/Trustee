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
namespace App
{
    class AccountInfo
    {
        public string Address { get; set; }
        public decimal Balance { get; set; }
    }
    static class Blockchain
    {
        public static byte[] ContractAddress { get { return BigInteger.Parse(auctionContract.Address.Substring(2), System.Globalization.NumberStyles.AllowHexSpecifier).ToByteArray().Reverse().ToArray(); } }
        public const int ActiveCount = 4;        
        private static string[] accounts;
        private static BigInteger initialDeposit;
        private static Web3 web3;
        private static Contract auctionContract;
        public static async Task Delay()
        {
            await Task.Delay(1000); //block time
        }
        public static async Task<AccountInfo> GetAccountInfo(int index)
        {
            if (accounts==null)
            {
                web3 = new Web3("http://127.0.0.1:8545");
                accounts = await web3.Personal.ListAccounts.SendRequestAsync();
            }
            if (index >= ActiveCount)
                throw new Exception("Larger number of accounts");
            AccountInfo a = new AccountInfo();
            a.Address = accounts[index];
            var x = await web3.Eth.GetBalance.SendRequestAsync(a.Address);
            a.Balance = UnitConversion.Convert.FromWei(x.Value, UnitConversion.EthUnit.Ether);
            return a;

        }
        public static async Task<decimal> GetBalanceAsync(string address)
        {
            var x = await web3.Eth.GetBalance.SendRequestAsync(address);
            return UnitConversion.Convert.FromWei(x.Value, UnitConversion.EthUnit.Ether);
        }        
        public static BigInteger GetBlockNumber()
        {
            return  web3.Eth.Blocks.GetBlockNumber.SendRequestAsync().Result;
        }
        public static void SendFundAsync(string to, long fund)
        {
            web3.TransactionManager.SendTransactionAsync(accounts[0], to, new HexBigInteger(UnitConversion.Convert.ToWei(fund))).Wait();
        }
        public static BigInteger DeployContract(out string address)
        {
            web3 = new Web3("http://127.0.0.1:8545");
            accounts = web3.Personal.ListAccounts.SendRequestAsync().Result;
            File.Delete("Auction.abi");
            File.Delete("Auction.bin");
            Process.Start(".\\solc.exe", " --abi --bin -o .\\ .\\Auction.sol").WaitForExit();
            var contractABI = File.ReadAllText("Auction.abi");
            var contractBIN = File.ReadAllText("Auction.bin");
            var receipt = web3.Eth.DeployContract.SendRequestAndWaitForReceiptAsync(contractABI, contractBIN, accounts[0], new HexBigInteger(3000000), new HexBigInteger(1), new HexBigInteger(0), null).Result;
            auctionContract = web3.Eth.GetContract(contractABI, receipt.ContractAddress);
            address = receipt.ContractAddress;
            return receipt.GasUsed.Value;
        }
        public static BigInteger StartAuction(string enclaveAddress, byte[] enclavePublicKey, BigInteger t1, BigInteger t2, BigInteger t3, int _d)
        {
            initialDeposit = UnitConversion.Convert.ToWei(_d, UnitConversion.EthUnit.Ether);
            var receipt = auctionContract.GetFunction("StartAuction").SendTransactionAndWaitForReceiptAsync(accounts[0], new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(initialDeposit), null, enclaveAddress, enclavePublicKey, t1, t2, t3, initialDeposit).Result;
            return receipt.GasUsed.Value;
        }
        public static BigInteger SubmitBid(int from, byte[] bidCT, byte[] bidPK)
        {
            return auctionContract.GetFunction("SubmitBid").SendTransactionAndWaitForReceiptAsync(accounts[from], new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(initialDeposit), null, bidCT, bidPK).Result.GasUsed.Value;
        }
        public static byte[] RetrieveSealedBids()
        {
            int count = auctionContract.GetFunction("GetLength").CallAsync<int>().Result;
            byte[] contractAddress = BigInteger.Parse(auctionContract.Address.Substring(2), System.Globalization.NumberStyles.AllowHexSpecifier).ToByteArray().Reverse().ToArray();
            List<byte> lstcipher = new List<byte>();
            byte[] bid;
            for (int i = 0; i < count; i++)
            {
                bid = auctionContract.GetFunction("bids").CallAsync<byte[]>(i).Result;
                lstcipher.AddRange(bid);
            }
            return lstcipher.ToArray();
        }
        public static void SendRawTransaction(byte[] rawTransaction)
        {
            string tx = BitConverter.ToString(rawTransaction).Replace("-", "");
            web3.Eth.Transactions.SendRawTransaction.SendRequestAsync(tx).Wait();
        }
        public static uint WhoIsTheWinner(out string address)
        {
            address = auctionContract.GetFunction("WinnerAddress").CallAsync<string>().Result;
            return auctionContract.GetFunction("WinnerBid").CallAsync<uint>().Result;
        }
        public static async Task<uint> Dispute(string from)
        {
            await auctionContract.GetFunction("Dispute").SendTransactionAndWaitForReceiptAsync(from, new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(0));
            await Delay();
            return await auctionContract.GetFunction("state").CallAsync<uint>();
        }
        public static BigInteger Refund(int from)
        {
            var receipt = auctionContract.GetFunction("Refund").SendTransactionAndWaitForReceiptAsync(accounts[from], new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(0)).Result;
            return receipt.GasUsed.Value;
        }
        public static BigInteger Reset()
        {
            return auctionContract.GetFunction("Reset").SendTransactionAndWaitForReceiptAsync(accounts[0], new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(0)).Result.GasUsed.Value;
        }
        public static uint GetContractState()
        {
            return auctionContract.GetFunction("state").CallAsync<uint>().Result;
        }
        public static void PublishDebug()
        {
            var b = auctionContract.GetFunction("ledger").CallAsync<BigInteger>(accounts[0]).Result;
            var x = web3.Eth.Blocks.GetBlockNumber.SendRequestAsync().Result.Value;
            var t1 = auctionContract.GetFunction("T1").CallAsync<BigInteger>().Result;
            var t2 = auctionContract.GetFunction("T2").CallAsync<BigInteger>().Result;
            var t3 = auctionContract.GetFunction("T3").CallAsync<BigInteger>().Result;
            var t4 = auctionContract.GetFunction("T4").CallAsync<BigInteger>().Result;
            var state = auctionContract.GetFunction("state").CallAsync<uint>().Result;

            Debug.WriteLine($"Balance={b}, X={x}, T1={t1}, T2={t2}, T3={t3}, T4={t4}, State= {state}");
        }
    }
}
