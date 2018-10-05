using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ManagedAuction;
namespace App
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Deploying Auction");
            Auctioneer.Initialize();            
            Console.WriteLine(Auctioneer.ContractAddress);
            Console.WriteLine("Starting Auction");
            Auctioneer.StartAuction();
            Console.ReadLine();
            Console.WriteLine("Setwinner");
            Auctioneer.SetWinner();
            Console.WriteLine("Dispute");
            Auctioneer.Dispute();
            Console.WriteLine("Refund");
            Auctioneer.Refund();
            Console.WriteLine("Reseting");
            Auctioneer.Reset();
        }
    }
}
