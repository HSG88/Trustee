using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UI
{
    public partial class BidderForm : Form
    {
        int index;
        public BidderForm(int i)
        {
            InitializeComponent();
            index = i;
            Shown += BidderForm_Shown;           
        }

        private async void BidderForm_Shown(object sender, EventArgs e)
        {
            var a = await Blockchain.GetAccountInfo(index);
            txtAddress.Text = a.Address;
            txtBalance.Text = a.Balance.ToString();
        }

        public async void SetState(State state)
        {
            switch(state)
            {
                case State.Init:
                    txtStatus.Text = "Waiting for auction";
                    break;
                case State.Bid:
                    txtStatus.Text = "You can bid now";
                    btnSubmit.Enabled = true;
                    break;
                case State.Reveal:
                    txtStatus.Text = "Winner reveal interval!";                    
                    break;
                case State.Dispute:
                    timer1.Start();
                    btnDispute.Enabled = true;
                    var winner = await Blockchain.WhoIsTheWinner();
                    if (winner.Address == txtAddress.Text)
                    {
                        txtStatus.Text = "Congratulations! you are the winner";
                        txtStatus.ForeColor = Color.Green;
                    }
                    else
                    if (txtBid.Text != ""&& winner.Balance< decimal.Parse(txtBid.Text))
                    {
                        txtStatus.Text = "Malicious auctioneer detected, Dispute now";                        
                    }
                    else
                    {
                        txtStatus.Text = "Sorry!, you lost. Highest Win is " + winner.Balance.ToString();
                        txtStatus.ForeColor = Color.Red;
                    }
                    break;
                case State.Withdraw:
                    btnDispute.Enabled = false;
                    btnWithdraw.Enabled = txtStatus.ForeColor == Color.Red;
                    break;
            }
        }

        private async void btnSubmit_Click(object sender, EventArgs e)
        {
            byte[] bidCT = new byte[32], bidPK = new byte[32];
            Enclave.EncryptBid(uint.Parse(txtBid.Text), ref bidCT, ref bidPK);
            await Blockchain.SubmitBidAsync(txtAddress.Text, bidCT, bidPK);
            await Blockchain.Delay();
            txtBalance.Text = (await Blockchain.GetBalanceAsync(txtAddress.Text)).ToString("F");
            btnSubmit.Enabled = false;
            txtStatus.Text = "You submitted bid";
        }

        private async void btnDispute_Click(object sender, EventArgs e)
        {
            btnDispute.Enabled = false;
            Blockchain.PublishDebug();
            bool success = await Blockchain.Dispute(txtAddress.Text) == 3;
            if (success)
                txtStatus.Text = "You won the malicious auctioneer deposit";
            else
                txtStatus.Text = "The auction winner is correct";
        }

        private async void btnWithdraw_Click(object sender, EventArgs e)
        {
            btnWithdraw.Enabled = false;
            await Blockchain.Withdraw(txtAddress.Text);
            await Blockchain.Delay();
            txtBalance.Text = (await Blockchain.GetBalanceAsync(txtAddress.Text)).ToString("F");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(Blockchain.GetContractState()==3)
            {
                txtStatus.Text = "The auction winner is invalid";
                timer1.Stop();
                txtStatus.ForeColor = Color.Red;
            }
        }
    }
}
