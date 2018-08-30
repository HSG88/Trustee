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
            Auctioneer.Initialize();            
            Console.WriteLine(Auctioneer.ContractAddress);
            Console.ReadLine();
            Auctioneer.DetermineWinner();
            Console.WriteLine(Bidders.WhoIsTheWinner());            
            Console.ReadLine();
        }
    }
}
