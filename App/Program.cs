using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace App
{
    class Program
    {
        static void Main(string[] args)
        {
            //Deploy the smart contract
            string ContractAddress;
            var cost = Blockchain.DeployContract(out ContractAddress);
            Console.WriteLine("DeployContract cost: " + cost);

            //Initialize the enclave
            string pk, address;
            Enclave.InitializeEnclave(out address, out pk);

            //Fund Trustee account
            Blockchain.SendFundAsync(address, 5);

            //start the auction in test mode => no intervals
            cost = Blockchain.StartAuction(address, Enclave.PublicKey, 0, 0, 0, 10);
            Console.WriteLine($"StartAuction cost: {cost}");


            //Do 50x bidding
            Random random = new Random();
            uint bid;
            byte[] bidCT = new byte[32], bidPK = new byte[32];
            for(int i=1; i<=50;i++)
            {
                bid = (uint)random.Next(100, 10000);
                Enclave.EncryptBid(bid, ref bidCT, ref bidPK);
                cost = Blockchain.SubmitBid(i, bidCT, bidPK);
                Console.WriteLine($"{i-1}:{bid} with cost: {cost}");               
            }

            //SetWinner
            byte[] bids = Blockchain.RetrieveSealedBids();
            byte[] tx = Enclave.GetSetWinnerRawTransaction(bids, Blockchain.ContractAddress);
            Blockchain.SendRawTransaction(tx);
            Console.WriteLine("SetWinner");

            //WhoIsTheWinner
            uint winningBid = Blockchain.WhoIsTheWinner(out string winnerAddress);
            Console.WriteLine($"Winning bid = {winningBid} @{winnerAddress}");

            //Refund
            for (int i = 0; i <= 50; i++)
                try
                {
                    Console.WriteLine($"Refunding {i} : {Blockchain.Refund(i)}");
                }
                catch { }

            //Reset
            Console.WriteLine($"Reset: {Blockchain.Reset()}");
            Console.ReadLine();


        }
    }
}
