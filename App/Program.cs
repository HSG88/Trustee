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
            Auctioneer.Log = Console.WriteLine;
            Auctioneer.DeployContract();
            Auctioneer.InitializeSGX();
            Auctioneer.StartAuction(20, 10, 10, 10, 1);
            Auctioneer.SubmitBid(599);
            Auctioneer.SubmitBid(700);
            Auctioneer.SubmitBid(900);
            Auctioneer.SubmitBid(200);
            Auctioneer.SubmitBid(300);
            Auctioneer.SubmitBid(400);
            Auctioneer.SetWinner();
        }
    }
}
