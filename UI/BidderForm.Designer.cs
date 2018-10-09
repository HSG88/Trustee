namespace UI
{
    partial class BidderForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.txtAddress = new System.Windows.Forms.TextBox();
            this.txtBid = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnSubmit = new System.Windows.Forms.Button();
            this.btnWithdraw = new System.Windows.Forms.Button();
            this.txtBalance = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtStatus = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnDispute = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Address";
            // 
            // txtAddress
            // 
            this.txtAddress.Location = new System.Drawing.Point(69, 9);
            this.txtAddress.Name = "txtAddress";
            this.txtAddress.Size = new System.Drawing.Size(312, 20);
            this.txtAddress.TabIndex = 1;
            // 
            // txtBid
            // 
            this.txtBid.Location = new System.Drawing.Point(69, 61);
            this.txtBid.Name = "txtBid";
            this.txtBid.Size = new System.Drawing.Size(310, 20);
            this.txtBid.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 64);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(22, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Bid";
            // 
            // btnSubmit
            // 
            this.btnSubmit.Location = new System.Drawing.Point(69, 92);
            this.btnSubmit.Name = "btnSubmit";
            this.btnSubmit.Size = new System.Drawing.Size(100, 24);
            this.btnSubmit.TabIndex = 4;
            this.btnSubmit.Text = "Submit Bid";
            this.btnSubmit.UseVisualStyleBackColor = true;
            // 
            // btnWithdraw
            // 
            this.btnWithdraw.Location = new System.Drawing.Point(281, 92);
            this.btnWithdraw.Name = "btnWithdraw";
            this.btnWithdraw.Size = new System.Drawing.Size(100, 24);
            this.btnWithdraw.TabIndex = 5;
            this.btnWithdraw.Text = "Withdraw Funds";
            this.btnWithdraw.UseVisualStyleBackColor = true;
            // 
            // txtBalance
            // 
            this.txtBalance.BackColor = System.Drawing.Color.LightGray;
            this.txtBalance.Enabled = false;
            this.txtBalance.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.txtBalance.Location = new System.Drawing.Point(259, 35);
            this.txtBalance.Name = "txtBalance";
            this.txtBalance.Size = new System.Drawing.Size(122, 20);
            this.txtBalance.TabIndex = 13;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(207, 38);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Balance";
            // 
            // txtStatus
            // 
            this.txtStatus.BackColor = System.Drawing.Color.LightGray;
            this.txtStatus.Enabled = false;
            this.txtStatus.ForeColor = System.Drawing.Color.Red;
            this.txtStatus.Location = new System.Drawing.Point(69, 35);
            this.txtStatus.Name = "txtStatus";
            this.txtStatus.ReadOnly = true;
            this.txtStatus.Size = new System.Drawing.Size(122, 20);
            this.txtStatus.TabIndex = 11;
            this.txtStatus.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 38);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(37, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Status";
            // 
            // btnDispute
            // 
            this.btnDispute.Location = new System.Drawing.Point(175, 92);
            this.btnDispute.Name = "btnDispute";
            this.btnDispute.Size = new System.Drawing.Size(100, 24);
            this.btnDispute.TabIndex = 14;
            this.btnDispute.Text = "Dispute";
            this.btnDispute.UseVisualStyleBackColor = true;
            // 
            // BidderForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(391, 128);
            this.Controls.Add(this.btnDispute);
            this.Controls.Add(this.txtBalance);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtStatus);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.btnWithdraw);
            this.Controls.Add(this.btnSubmit);
            this.Controls.Add(this.txtBid);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtAddress);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "BidderForm";
            this.Text = "Bidder";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtAddress;
        private System.Windows.Forms.TextBox txtBid;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnSubmit;
        private System.Windows.Forms.Button btnWithdraw;
        private System.Windows.Forms.TextBox txtBalance;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtStatus;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnDispute;
    }
}