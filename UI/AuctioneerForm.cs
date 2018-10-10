using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UI
{
    public enum State { Init, Bid, Reveal, Dispute, Withdraw}
    public partial class AuctioneerForm : Form
    {
        BigInteger T0, T1, T2, T3, T4;
        State state;
        BidderForm[] bidders;
        public event Action<State> StateChanged;
        public AuctioneerForm()
        {
            InitializeComponent();
            this.Shown += AuctioneerForm_Shown;
            timer1.Tick += UpdateProgress;        
        }

        private async void UpdateProgress(object sender, EventArgs e)
        {
            var x = Blockchain.GetBlockNumber();
            if(T0< x && x <= T1)
            {
                if (state != State.Bid)
                {
                    state = State.Bid;
                    StateChanged(state);
                }
                var a =x -T0;
                var b = T1 - T0;
                prgBidding.Value = (int)(a * 100 / b);
            }
            if (T1 < x && x <= T2)
            {
                if (state != State.Reveal)
                {
                    state = State.Reveal;
                    StateChanged(state);
                    prgBidding.Value = 100;
                    btnSetWinner.Enabled = true;
                    txtSkip.ReadOnly = false;
                }                
                var a = x - T1;
                var b = T2 - T1;
                prgWinner.Value = (int)(a * 100 / b);
            }
            if(T2 < x && x <= T3)
            {
                if (state != State.Dispute)
                {
                    timer1.Stop();
                    state = State.Dispute;
                    StateChanged(state);
                    prgWinner.Value = 100;
                    timer1.Start();
                }                
                var a = x - T2;
                var b = T3 - T2;
                prgDispute.Value = (int)(a * 100 / b);
            }
            if (T3 < x && x <= T4)
            {
                if (state != State.Withdraw)
                {
                    timer1.Stop();
                    await Blockchain.Withdraw(txtAuctioneerAddress.Text);
                    await Blockchain.Delay();
                    txtAuctioneerBalance.Text = (await Blockchain.GetBalanceAsync(txtAuctioneerAddress.Text)).ToString("F");
                    state = State.Withdraw;
                    StateChanged(state);
                    prgDispute.Value = 100;
                    timer1.Start();
                }
                var a = x - T3;
                var b = T4 - T3;
                prgWithdraw.Value = (int)(a * 100 / b);
            }
            if(x>T4)
            {
                prgWithdraw.Value = 100;
                timer1.Stop();
                await Blockchain.Finalize();
                await Blockchain.Delay();
                txtAuctioneerBalance.Text = (await Blockchain.GetBalanceAsync(txtAuctioneerAddress.Text)).ToString("F");
            }
        }

        private async void btnSetWinner_Click(object sender, EventArgs e)
        {
            btnSetWinner.Enabled = false;
            txtSkip.ReadOnly = true;
            byte[] bids = await Blockchain.RetrieveSealedBidsAsync(txtSkip.Text);
            byte[] tx = Enclave.GetSetWinnerRawTransaction(bids, Blockchain.ContractAddress);
            await Blockchain.SendRawTransaction(tx);
            await Blockchain.Delay();
        }

        private async void AuctioneerForm_Shown(object sender, EventArgs e)
        {
            var a = await Blockchain.GetAccountInfo(0);
            txtAuctioneerAddress.Text = a.Address;
            txtAuctioneerBalance.Text = a.Balance.ToString("F");
        }

        private async void btnDeployContract_Click(object sender, EventArgs e)
        {            
            btnDeployContract.Enabled = false;
            txtContractAddress.Text = await Blockchain.DeployContractAsync();
            bidders = new BidderForm[Blockchain.ActiveCount];
            for(int i=1; i<Blockchain.ActiveCount; i++)
            {
                bidders[i] = new BidderForm(i);
                this.StateChanged += bidders[i].SetState;
                bidders[i].Show();
            }
            this.StateChanged(State.Init);
            await Blockchain.Delay();
            txtAuctioneerBalance.Text = (await Blockchain.GetBalanceAsync(txtAuctioneerAddress.Text)).ToString("F");
            btnInitializeEnclave.Enabled = true;
        }

        private async void btnInitializeEnclave_Click(object sender, EventArgs e)
        {
            btnInitializeEnclave.Enabled = false;
            string pk, address;
            Enclave.InitializeEnclave(out address, out pk);
            txtEnclaveAddress.Text = address;
            txtEnclavePublicKey.Text = pk;
            await Blockchain.SendFundAsync(address, 5);
            await Blockchain.Delay();
            txtEnclaveBalance.Text = (await Blockchain.GetBalanceAsync(address)).ToString("F");
            txtAuctioneerBalance.Text = (await Blockchain.GetBalanceAsync(txtAuctioneerAddress.Text)).ToString("F");
            btnStartAuction.Enabled = true;
            txtBidding.ReadOnly = txtWinner.ReadOnly = txtDispute.ReadOnly = txtWithdraw.ReadOnly = false;
        }

        private async void btnStartAuction_Click(object sender, EventArgs e)
        {
            btnStartAuction.Enabled = false;
            txtBidding.ReadOnly = txtWinner.ReadOnly = txtDispute.ReadOnly = txtWithdraw.ReadOnly = true;
            T1 = BigInteger.Parse(txtBidding.Text);
            T2 = BigInteger.Parse(txtWinner.Text);
            T3 = BigInteger.Parse(txtDispute.Text);
            T4 = BigInteger.Parse(txtWithdraw.Text);
            T0 =await Blockchain.StartAuction(txtEnclaveAddress.Text, Enclave.PublicKey, T1, T2, T3, T4 ,10);
            T1 += T0;
            T2 += T1;
            T3 += T2;
            T4 += T3;
            timer1.Start();            
        }
    }
}
