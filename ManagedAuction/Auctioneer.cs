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
    public class Bidder
    {
        public int Index { get; set; }
        public string Address { get; set; }
        public uint Bid { get; set; }
        public string PublicKey { get; set; }
        public string SealedBid { get; set; }
    }
    public static class Auctioneer
    {

        private static byte[] _sgxAddress = new byte[20], _dhPublicKey = new byte[32];
        private static string[] accounts;
        private static BigInteger t1, t2, t3, t4, d;
        private static Web3 web3;
        private static ManagedEnclave sgx;
        private static int biddersCount;
        private static string auctioneerAddress, sgxAddress, dhPublicKey, contractBIN;
        public static string ContractAddress { get; private set; }
        public static string ContractABI { get; private set; }
        public static Function refund, reset, dispute, startAuction, setWinner, submitBid, SealedBids, bids, GetLength, winnerBid, winnerAddress, hash;
        public static Action<string> Log { get; set; }
        public static void DeployContract()
        {
            web3 = new Web3("http://127.0.0.1:8545");
            accounts = web3.Personal.ListAccounts.SendRequestAsync().Result;
            auctioneerAddress = accounts[0];
            File.Delete("Auction.abi");
            File.Delete("Auction.bin");
            Process.Start(".\\solc.exe", " --abi --bin -o .\\ .\\Auction.sol").WaitForExit();
            ContractABI = File.ReadAllText("Auction.abi");
            contractBIN = File.ReadAllText("Auction.bin");
            TransactionReceipt receipt = web3.Eth.DeployContract.SendRequestAndWaitForReceiptAsync(ContractABI, contractBIN, auctioneerAddress, new HexBigInteger(3000000), new HexBigInteger(1), new HexBigInteger(0), null).Result;
            Contract auctionContract = web3.Eth.GetContract(ContractABI, receipt.ContractAddress);
            Log($"Deployed contract at: {receipt.ContractAddress}");
            Log($"Gas cost: {receipt.GasUsed.Value}");

            ContractAddress = receipt.ContractAddress;
            dispute = auctionContract.GetFunction(nameof(Dispute));
            refund = auctionContract.GetFunction(nameof(Refund));
            reset = auctionContract.GetFunction(nameof(Reset));
            startAuction = auctionContract.GetFunction(nameof(StartAuction));
            submitBid = auctionContract.GetFunction(nameof(SubmitBid));
            setWinner = auctionContract.GetFunction(nameof(SetWinner));
            GetLength = auctionContract.GetFunction(nameof(GetLength));
            bids = auctionContract.GetFunction(nameof(bids));
            winnerBid = auctionContract.GetFunction("WinnerBid");
            winnerAddress = auctionContract.GetFunction("WinnerAddress");
            hash = auctionContract.GetFunction("Hash");
        }
        public static BigInteger GetBlockNumber()
        {
            return web3.Eth.Blocks.GetBlockNumber.SendRequestAsync().Result.Value;
        }
        public static void InitializeSGX()
        {
            sgx = new ManagedEnclave();
            byte[] _sealedSecret = new byte[2048];
            int sealedLength = sgx.SGX_GenerateKeys(ref _sealedSecret, ref _sgxAddress, ref _dhPublicKey);
            sgxAddress = "0x" + BitConverter.ToString(_sgxAddress).Replace("-", "");
            dhPublicKey = "0x" + BitConverter.ToString(_dhPublicKey).Replace("-", "");
            Array.Resize(ref _sealedSecret, sealedLength);
            File.WriteAllBytes("SealedSecrets", _sealedSecret);

            Log($"SGX Address: {sgxAddress}");
            Log($"SGX PublicKey: {dhPublicKey}");
            var w = UnitConversion.Convert.ToWei(5, UnitConversion.EthUnit.Ether);
            web3.TransactionManager.SendTransactionAsync(auctioneerAddress, sgxAddress, new HexBigInteger(w)).Wait(); //fund SGX Account so it can post transactions
            Log($"Auctioneer funded SGX Address with: 5 ethers");
        }
        public static BigInteger StartAuction(int _t1, int _t2, int _t3, int _t4, int _d)
        {
            t1 = new BigInteger(20);
            t2 = new BigInteger(10);
            t3 = new BigInteger(10);
            t4 = new BigInteger(40);
            d = UnitConversion.Convert.ToWei(_d, UnitConversion.EthUnit.Ether);
            var receipt = startAuction.SendTransactionAndWaitForReceiptAsync(auctioneerAddress, new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(d), null, sgxAddress, _dhPublicKey, t1, t2, t3, t4, d).Result;
            Log($"StartAuction Gas Cost: {receipt.GasUsed.Value}");
            return receipt.BlockNumber.Value;
        }
        public static string[] BiddersAccounts
        {
            get
            {
                return web3.Personal.ListAccounts.SendRequestAsync().Result;
            }
        }
        public static Bidder SubmitBid(uint bid)
        {
            biddersCount++;
            byte[] bidPK = new byte[32], bidCT = new byte[32];
            sgx.SGX_EncryptBid(ref _dhPublicKey, bid, ref bidPK, ref bidCT);
            Bidder x = new Bidder() { Index = biddersCount, Address = accounts[biddersCount], SealedBid = BitConverter.ToString(bidCT).Replace("-", ""), PublicKey = BitConverter.ToString(bidPK).Replace("-", ""), Bid = bid };
            var receipt = submitBid.SendTransactionAndWaitForReceiptAsync(accounts[biddersCount], new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(d), null, bidCT, bidPK).Result;
            Log($"SubmitBid Gas Cost: {receipt.GasUsed.Value}");
            return x;
        }
        public static void SetWinner()
        {
            int count = GetLength.CallAsync<int>().Result;
            byte[] contractAddress = BigInteger.Parse(ContractAddress.Substring(2), System.Globalization.NumberStyles.AllowHexSpecifier).ToByteArray().Reverse().ToArray();
            List<byte> lstcipher = new List<byte>();
            byte[] bid;
            Log("Retriving " + count / 3 + " sealed-bids...");
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
            var r = web3.Eth.Transactions.SendRawTransaction.SendRequestAsync(tx).Result;
            Log($"SetWinner transaction hash: {r}");

        }
        public static void RefundAllExcept(string address)
        {

            for (int i = 0; i < biddersCount; i++)
            {
                if (StringComparer.OrdinalIgnoreCase.Compare(address, accounts[i]) == 0)
                    continue;
                refund.SendTransactionAsync(accounts[i], new HexBigInteger(5000000), new HexBigInteger(1), new HexBigInteger(0), null);
                Log("Refunding: " + accounts[i]);
            }
        }
        public static Bidder WhoIsTheWinner()
        {
            Bidder x = new ManagedAuction.Bidder();
            x.Address = winnerAddress.CallAsync<string>().Result;
            x.Bid = winnerBid.CallAsync<uint>().Result;
            return x;
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

    }
}
