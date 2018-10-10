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
namespace UI
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
        public static async Task SendFundAsync(string to, long fund)
        {
            await web3.TransactionManager.SendTransactionAsync(accounts[0], to, new HexBigInteger(UnitConversion.Convert.ToWei(fund)));
        }
        public static async Task<string> DeployContractAsync()
        {
            File.Delete("Auction.abi");
            File.Delete("Auction.bin");
            Process.Start(".\\solc.exe", " --abi --bin -o .\\ .\\Auction.sol").WaitForExit();
            var contractABI = File.ReadAllText("Auction.abi");
            var contractBIN = File.ReadAllText("Auction.bin");
            TransactionReceipt receipt = await web3.Eth.DeployContract.SendRequestAndWaitForReceiptAsync(contractABI, contractBIN, accounts[0], new HexBigInteger(3000000), new HexBigInteger(1), new HexBigInteger(0), null);
            auctionContract = web3.Eth.GetContract(contractABI, receipt.ContractAddress);
            return receipt.ContractAddress;
        }
        public static async Task<BigInteger> StartAuction(string enclaveAddress, byte[] enclavePublicKey, BigInteger t1, BigInteger t2, BigInteger t3, BigInteger t4, int _d)
        {
            initialDeposit = UnitConversion.Convert.ToWei(_d, UnitConversion.EthUnit.Ether);
            var receipt = await auctionContract.GetFunction("StartAuction").SendTransactionAndWaitForReceiptAsync(accounts[0], new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(initialDeposit), null, enclaveAddress, enclavePublicKey, t1, t2, t3, t4, initialDeposit);
            return receipt.BlockNumber.Value;
        }
        public static async Task SubmitBidAsync(string from, byte[] bidCT, byte[] bidPK)
        {
            await auctionContract.GetFunction("SubmitBid").SendTransactionAndWaitForReceiptAsync(from, new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(initialDeposit), null, bidCT, bidPK);
        }
        public static async Task<byte[]> RetrieveSealedBidsAsync(string skip)
        {
            int count = auctionContract.GetFunction("GetLength").CallAsync<int>().Result;
            byte[] contractAddress = BigInteger.Parse(auctionContract.Address.Substring(2), System.Globalization.NumberStyles.AllowHexSpecifier).ToByteArray().Reverse().ToArray();
            List<byte> lstcipher = new List<byte>();
            byte[] bid;
            for (int i = 0; i < count; i++)
            {
                bid = await auctionContract.GetFunction("bids").CallAsync<byte[]>(i);
                if (i % 2 == 0)
                {
                    string address ="0x"+ BitConverter.ToString(bid).Replace("-", "").ToLower();
                    if(address == skip)
                    {
                        lstcipher.RemoveRange(i - 2, 2);
                        continue;
                    }
                }
                lstcipher.AddRange(bid);
            }
            return lstcipher.ToArray();
        }
        public static async Task SendRawTransaction(byte[] rawTransaction)
        {
            string tx = BitConverter.ToString(rawTransaction).Replace("-", "");
            await web3.Eth.Transactions.SendRawTransaction.SendRequestAsync(tx);
        }
        public static async Task<AccountInfo> WhoIsTheWinner()
        {
            AccountInfo af = new UI.AccountInfo();
            af.Address= await auctionContract.GetFunction("WinnerAddress").CallAsync<string>();
            af.Balance= await auctionContract.GetFunction("WinnerBid").CallAsync<uint>();
            return af;
        }
    }
}
