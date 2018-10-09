using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ManagedAuction;
using System.Numerics;

namespace UI
{
    public partial class MainForm : Form
    {
        BigInteger start, bidding, winner, dispute, refund;

        private void mnuInitializeSGX_Click(object sender, EventArgs e)
        {
            Auctioneer.InitializeSGX();
            mnuInitializeSGX.Enabled = false;
        }

        private void btnSubmit_Click(object sender, EventArgs e)
        {
            uint bid = uint.Parse(txtBid.Text);
            Bidder x = Auctioneer.SubmitBid(bid);
            bidderBindingSource.Add(x);
            txtBid.Text = "";
        }

        public MainForm()
        {
            InitializeComponent();
            timer.Tick += UpdateProgress;
            timer1.Tick += Timer1_Tick;
            timer2.Tick += Timer2_Tick;
        }

        private void Timer2_Tick(object sender, EventArgs e)
        {
            var x = Auctioneer.GetBlockNumber();
            if (x < refund)
                prgRefund.Value = (int)((float)(x - dispute) / (float)(refund - dispute) * 100.0);
            else
            {
                prgRefund.Value = 100;
                timer2.Stop();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var x = Auctioneer.WhoIsTheWinner();
            txtWinBid.Text = x.Bid.ToString();
            txtWinAddress.Text = x.Address;
        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
            var x = Auctioneer.GetBlockNumber();
            if (x < winner)
                prgWinner.Value = (int)((float)(x - bidding) / (float)(winner - bidding) * 100.0);
            else
            {
                button1.Enabled = true;
                prgWinner.Value = 100;
                if (x < dispute)
                    prgDispute.Value = (int)((float)(x - winner) / (float)(dispute - winner) * 100.0);
                else
                {
                    prgDispute.Value = 100;
                    timer1.Stop();
                    Auctioneer.RefundAllExcept(txtWinAddress.Text);
                    timer2.Start();                    
                }
            }
        }

        private void mnuDeploy_Click(object sender, EventArgs e)
        {
            Auctioneer.Log = x =>
            {
                lstLog.Items.Add(x);
                lstLog.SelectedIndex = lstLog.Items.Count - 1;
            };
            Auctioneer.DeployContract();
            mnuDeploy.Enabled = false;
        }
        private void mnuStartAuction_Click(object sender, EventArgs e)
        {
            AuctionForm af = new UI.AuctionForm();
            var res = af.ShowDialog();
            start= Auctioneer.StartAuction(af.Bidding, af.Winner, af.Dispute, af.Refund, af.Deposit);
            bidding = start + af.Bidding;
            winner = bidding + af.Winner;
            dispute = winner + af.Dispute;
            refund = dispute + af.Refund;
            af.Close();
            timer.Start();
            mnuStartAuction.Enabled = false;
        }
        private void UpdateProgress(object sender, EventArgs e)
        {
            var x = Auctioneer.GetBlockNumber();

            if (x < bidding)
                prgBidding.Value = (int)((float)(x-start) / (float)(bidding - start) * 100.0);
            else
            {
                btnSubmit.Enabled = false;
                txtBid.Enabled = false;
                prgBidding.Value = 100;
                Auctioneer.SetWinner();
                timer.Stop();
                timer1.Start();                
            }
        }
    }
}
