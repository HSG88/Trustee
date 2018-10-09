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
    public partial class AuctionForm : Form
    {
        public AuctionForm()
        {
            InitializeComponent();
        }
        public int Bidding { get; set; }
        public int Winner { get; set; }
        public int Dispute { get; set; }
        public int Refund { get; set; }
        public int Deposit { get; set; }

        private void btnSave_Click(object sender, EventArgs e)
        {
            Bidding = int.Parse(txtBidding.Text);
            Winner = int.Parse(txtWinner.Text);
            Dispute = int.Parse(txtDispute.Text);
            Refund = int.Parse(txtRefund.Text);
            Deposit = int.Parse(txtDeposit.Text);
            this.DialogResult = DialogResult.OK;
        }
    }
}
