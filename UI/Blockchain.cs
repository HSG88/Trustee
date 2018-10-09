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
    static class Blockchain
    {
        public static byte[] ContractAddress { get { return BigInteger.Parse(auctionContract.Address.Substring(2), System.Globalization.NumberStyles.AllowHexSpecifier).ToByteArray().Reverse().ToArray(); } }
        private const int ActiveCount = 4;        
        private static string[] accounts;
        private static BigInteger initialDeposit;
        private static Web3 web3;
        private static Contract auctionContract;
        private static int biddersCount;
        public static Function refund, reset, dispute, startAuction, setWinner, submitBid, bids, GetLength, winnerBid, winnerAddress, hash;
        public static void InitializeAuctioneerAndBidders(string[] _accounts, decimal[] _balances)
        {
            web3 = new Web3("http://127.0.0.1:8545");
            accounts = web3.Personal.ListAccounts.SendRequestAsync().Result;
            _accounts = accounts;
            for(int i=0;i<ActiveCount;i++)
            {
                _accounts[i] = accounts[i];
                _balances[i] = GetBalance(accounts[i]);
            }
        }
        public static decimal GetBalance(string address)
        {
            return UnitConversion.Convert.FromWei(web3.Eth.GetBalance.SendRequestAsync(address).Result.Value, UnitConversion.EthUnit.Ether);
        }
        public static void SendFund(string to, long fund)
        {
            web3.TransactionManager.SendTransactionAsync(accounts[0], to, new HexBigInteger(UnitConversion.Convert.ToWei(fund))).RunSynchronously();
        }
        public static string DeployContract()
        {
            File.Delete("Auction.abi");
            File.Delete("Auction.bin");
            Process.Start(".\\solc.exe", " --abi --bin -o .\\ .\\Auction.sol").WaitForExit();
            var contractABI = File.ReadAllText("Auction.abi");
            var contractBIN = File.ReadAllText("Auction.bin");
            TransactionReceipt receipt = web3.Eth.DeployContract.SendRequestAndWaitForReceiptAsync(contractABI, contractBIN, auctioneerAddress, new HexBigInteger(3000000), new HexBigInteger(1), new HexBigInteger(0), null).Result;
            auctionContract = web3.Eth.GetContract(contractABI, receipt.ContractAddress);
            dispute = auctionContract.GetFunction("Dispute");
            refund = auctionContract.GetFunction("Refund");
            reset = auctionContract.GetFunction("Reset");
            startAuction = auctionContract.GetFunction("StartAuction");
            submitBid = auctionContract.GetFunction("SubmitBid");
            setWinner = auctionContract.GetFunction("SetWinner");
            GetLength = auctionContract.GetFunction("GetLength");
            bids = auctionContract.GetFunction("bids");
            winnerBid = auctionContract.GetFunction("WinnerBid");
            winnerAddress = auctionContract.GetFunction("WinnerAddress");
            hash = auctionContract.GetFunction("Hash");
            return receipt.ContractAddress;
        }
        public static BigInteger StartAuction(string enclaveAddress, string enclavePublicKey, BigInteger _t1, BigInteger _t2, BigInteger _t3, BigInteger _t4, int _d)
        {
            initialDeposit = UnitConversion.Convert.ToWei(_d, UnitConversion.EthUnit.Ether);
            var receipt = startAuction.SendTransactionAndWaitForReceiptAsync(accounts[0], new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(initialDeposit), null, enclaveAddress, enclavePublicKey, t1, t2, t3, t4, initialDeposit).Result;
            return receipt.BlockNumber.Value;
        }
        public static void SubmitBid(string from, byte[] bidCT, byte[] bidPK)
        {
            var receipt = submitBid.SendTransactionAndWaitForReceiptAsync(from, new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(initialDeposit), null, bidCT, bidPK).Result;
        }
        public static byte[] RetrieveSealedBids(string skip)
        {
            int count = auctionContract.GetFunction("GetLength").CallAsync<int>().Result;
            byte[] contractAddress = BigInteger.Parse(auctionContract.Address.Substring(2), System.Globalization.NumberStyles.AllowHexSpecifier).ToByteArray().Reverse().ToArray();
            List<byte> lstcipher = new List<byte>();
            byte[] bid;
            for (int i = 0; i < count; i++)
            {
                bid = auctionContract.GetFunction("bids").CallAsync<byte[]>(i).Result;
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
        public static void SendRawTransaction(byte[] rawTransaction)
        {
            string tx = BitConverter.ToString(rawTransaction).Replace("-", "");
            var r = web3.Eth.Transactions.SendRawTransaction.SendRequestAsync(tx).Result;
        }
    }
}
