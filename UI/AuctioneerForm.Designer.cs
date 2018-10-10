namespace UI
{
    partial class AuctioneerForm
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
            this.components = new System.ComponentModel.Container();
            this.txtAuctioneerBalance = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtAuctioneerAddress = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtContractAddress = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnDeployContract = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtEnclavePublicKey = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtEnclaveAddress = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txtEnclaveBalance = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.btnInitializeEnclave = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.prgWithdraw = new System.Windows.Forms.ProgressBar();
            this.prgDispute = new System.Windows.Forms.ProgressBar();
            this.prgWinner = new System.Windows.Forms.ProgressBar();
            this.prgBidding = new System.Windows.Forms.ProgressBar();
            this.txtWithdraw = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.txtDispute = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtBidding = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtWinner = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.btnStartAuction = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnSetWinner = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.txtSkip = new System.Windows.Forms.TextBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtAuctioneerBalance
            // 
            this.txtAuctioneerBalance.BackColor = System.Drawing.Color.White;
            this.txtAuctioneerBalance.ForeColor = System.Drawing.Color.Lime;
            this.txtAuctioneerBalance.Location = new System.Drawing.Point(112, 44);
            this.txtAuctioneerBalance.Name = "txtAuctioneerBalance";
            this.txtAuctioneerBalance.ReadOnly = true;
            this.txtAuctioneerBalance.Size = new System.Drawing.Size(342, 20);
            this.txtAuctioneerBalance.TabIndex = 19;
            this.txtAuctioneerBalance.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 47);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 13);
            this.label4.TabIndex = 18;
            this.label4.Text = "Balance";
            // 
            // txtAuctioneerAddress
            // 
            this.txtAuctioneerAddress.BackColor = System.Drawing.Color.White;
            this.txtAuctioneerAddress.ForeColor = System.Drawing.Color.Blue;
            this.txtAuctioneerAddress.Location = new System.Drawing.Point(111, 18);
            this.txtAuctioneerAddress.Name = "txtAuctioneerAddress";
            this.txtAuctioneerAddress.ReadOnly = true;
            this.txtAuctioneerAddress.Size = new System.Drawing.Size(342, 20);
            this.txtAuctioneerAddress.TabIndex = 15;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(99, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "Auctioneer Address";
            // 
            // txtContractAddress
            // 
            this.txtContractAddress.BackColor = System.Drawing.Color.White;
            this.txtContractAddress.ForeColor = System.Drawing.Color.Blue;
            this.txtContractAddress.Location = new System.Drawing.Point(111, 70);
            this.txtContractAddress.Name = "txtContractAddress";
            this.txtContractAddress.ReadOnly = true;
            this.txtContractAddress.Size = new System.Drawing.Size(342, 20);
            this.txtContractAddress.TabIndex = 21;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 73);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(88, 13);
            this.label2.TabIndex = 20;
            this.label2.Text = "Contract Address";
            // 
            // btnDeployContract
            // 
            this.btnDeployContract.Location = new System.Drawing.Point(189, 96);
            this.btnDeployContract.Name = "btnDeployContract";
            this.btnDeployContract.Size = new System.Drawing.Size(167, 24);
            this.btnDeployContract.TabIndex = 22;
            this.btnDeployContract.Text = "1- Deploy Contract";
            this.btnDeployContract.UseVisualStyleBackColor = true;
            this.btnDeployContract.Click += new System.EventHandler(this.btnDeployContract_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtContractAddress);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtAuctioneerAddress);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.txtAuctioneerBalance);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.btnDeployContract);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(476, 131);
            this.groupBox1.TabIndex = 30;
            this.groupBox1.TabStop = false;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.txtEnclavePublicKey);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.txtEnclaveAddress);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.txtEnclaveBalance);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.btnInitializeEnclave);
            this.groupBox2.Location = new System.Drawing.Point(13, 149);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(476, 131);
            this.groupBox2.TabIndex = 31;
            this.groupBox2.TabStop = false;
            // 
            // txtEnclavePublicKey
            // 
            this.txtEnclavePublicKey.BackColor = System.Drawing.Color.White;
            this.txtEnclavePublicKey.ForeColor = System.Drawing.Color.Blue;
            this.txtEnclavePublicKey.Location = new System.Drawing.Point(111, 70);
            this.txtEnclavePublicKey.Name = "txtEnclavePublicKey";
            this.txtEnclavePublicKey.ReadOnly = true;
            this.txtEnclavePublicKey.Size = new System.Drawing.Size(342, 20);
            this.txtEnclavePublicKey.TabIndex = 21;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 21);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 13);
            this.label3.TabIndex = 14;
            this.label3.Text = "Enclave Address";
            // 
            // txtEnclaveAddress
            // 
            this.txtEnclaveAddress.BackColor = System.Drawing.Color.White;
            this.txtEnclaveAddress.ForeColor = System.Drawing.Color.Blue;
            this.txtEnclaveAddress.Location = new System.Drawing.Point(111, 18);
            this.txtEnclaveAddress.Name = "txtEnclaveAddress";
            this.txtEnclaveAddress.ReadOnly = true;
            this.txtEnclaveAddress.Size = new System.Drawing.Size(342, 20);
            this.txtEnclaveAddress.TabIndex = 15;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 47);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(46, 13);
            this.label5.TabIndex = 18;
            this.label5.Text = "Balance";
            // 
            // txtEnclaveBalance
            // 
            this.txtEnclaveBalance.BackColor = System.Drawing.Color.White;
            this.txtEnclaveBalance.ForeColor = System.Drawing.Color.Lime;
            this.txtEnclaveBalance.Location = new System.Drawing.Point(111, 44);
            this.txtEnclaveBalance.Name = "txtEnclaveBalance";
            this.txtEnclaveBalance.ReadOnly = true;
            this.txtEnclaveBalance.Size = new System.Drawing.Size(342, 20);
            this.txtEnclaveBalance.TabIndex = 19;
            this.txtEnclaveBalance.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 73);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(99, 13);
            this.label6.TabIndex = 20;
            this.label6.Text = "Enclave Public Key";
            // 
            // btnInitializeEnclave
            // 
            this.btnInitializeEnclave.Enabled = false;
            this.btnInitializeEnclave.Location = new System.Drawing.Point(189, 96);
            this.btnInitializeEnclave.Name = "btnInitializeEnclave";
            this.btnInitializeEnclave.Size = new System.Drawing.Size(167, 24);
            this.btnInitializeEnclave.TabIndex = 22;
            this.btnInitializeEnclave.Text = "2- Initialize Enclave";
            this.btnInitializeEnclave.UseVisualStyleBackColor = true;
            this.btnInitializeEnclave.Click += new System.EventHandler(this.btnInitializeEnclave_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnSetWinner);
            this.groupBox3.Controls.Add(this.prgWithdraw);
            this.groupBox3.Controls.Add(this.prgDispute);
            this.groupBox3.Controls.Add(this.prgWinner);
            this.groupBox3.Controls.Add(this.prgBidding);
            this.groupBox3.Controls.Add(this.txtWithdraw);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.txtDispute);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.txtBidding);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.txtWinner);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.btnStartAuction);
            this.groupBox3.Location = new System.Drawing.Point(12, 286);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(476, 154);
            this.groupBox3.TabIndex = 32;
            this.groupBox3.TabStop = false;
            // 
            // prgWithdraw
            // 
            this.prgWithdraw.Location = new System.Drawing.Point(262, 96);
            this.prgWithdraw.Name = "prgWithdraw";
            this.prgWithdraw.Size = new System.Drawing.Size(191, 17);
            this.prgWithdraw.TabIndex = 28;
            // 
            // prgDispute
            // 
            this.prgDispute.Location = new System.Drawing.Point(262, 73);
            this.prgDispute.Name = "prgDispute";
            this.prgDispute.Size = new System.Drawing.Size(191, 17);
            this.prgDispute.TabIndex = 27;
            // 
            // prgWinner
            // 
            this.prgWinner.Location = new System.Drawing.Point(262, 47);
            this.prgWinner.Name = "prgWinner";
            this.prgWinner.Size = new System.Drawing.Size(191, 17);
            this.prgWinner.TabIndex = 26;
            // 
            // prgBidding
            // 
            this.prgBidding.Location = new System.Drawing.Point(262, 21);
            this.prgBidding.Name = "prgBidding";
            this.prgBidding.Size = new System.Drawing.Size(191, 17);
            this.prgBidding.TabIndex = 25;
            // 
            // txtWithdraw
            // 
            this.txtWithdraw.BackColor = System.Drawing.Color.Yellow;
            this.txtWithdraw.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.txtWithdraw.Location = new System.Drawing.Point(112, 96);
            this.txtWithdraw.Name = "txtWithdraw";
            this.txtWithdraw.ReadOnly = true;
            this.txtWithdraw.Size = new System.Drawing.Size(132, 20);
            this.txtWithdraw.TabIndex = 24;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(7, 99);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(90, 13);
            this.label10.TabIndex = 23;
            this.label10.Text = "Withdraw Interval";
            // 
            // txtDispute
            // 
            this.txtDispute.BackColor = System.Drawing.Color.Yellow;
            this.txtDispute.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.txtDispute.Location = new System.Drawing.Point(111, 70);
            this.txtDispute.Name = "txtDispute";
            this.txtDispute.ReadOnly = true;
            this.txtDispute.Size = new System.Drawing.Size(132, 20);
            this.txtDispute.TabIndex = 21;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 21);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(80, 13);
            this.label7.TabIndex = 14;
            this.label7.Text = "Bidding Interval";
            // 
            // txtBidding
            // 
            this.txtBidding.BackColor = System.Drawing.Color.Yellow;
            this.txtBidding.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.txtBidding.Location = new System.Drawing.Point(111, 18);
            this.txtBidding.Name = "txtBidding";
            this.txtBidding.ReadOnly = true;
            this.txtBidding.Size = new System.Drawing.Size(132, 20);
            this.txtBidding.TabIndex = 15;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 47);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(98, 13);
            this.label8.TabIndex = 18;
            this.label8.Text = "Set Winner Interval";
            // 
            // txtWinner
            // 
            this.txtWinner.BackColor = System.Drawing.Color.Yellow;
            this.txtWinner.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.txtWinner.Location = new System.Drawing.Point(111, 44);
            this.txtWinner.Name = "txtWinner";
            this.txtWinner.ReadOnly = true;
            this.txtWinner.Size = new System.Drawing.Size(132, 20);
            this.txtWinner.TabIndex = 19;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 73);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(81, 13);
            this.label9.TabIndex = 20;
            this.label9.Text = "Dispute Interval";
            // 
            // btnStartAuction
            // 
            this.btnStartAuction.Enabled = false;
            this.btnStartAuction.Location = new System.Drawing.Point(112, 124);
            this.btnStartAuction.Name = "btnStartAuction";
            this.btnStartAuction.Size = new System.Drawing.Size(132, 24);
            this.btnStartAuction.TabIndex = 22;
            this.btnStartAuction.Text = "3- Start Auction";
            this.btnStartAuction.UseVisualStyleBackColor = true;
            this.btnStartAuction.Click += new System.EventHandler(this.btnStartAuction_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label11);
            this.groupBox4.Controls.Add(this.txtSkip);
            this.groupBox4.Controls.Add(this.checkBox1);
            this.groupBox4.Location = new System.Drawing.Point(12, 446);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(476, 100);
            this.groupBox4.TabIndex = 33;
            this.groupBox4.TabStop = false;
            // 
            // btnSetWinner
            // 
            this.btnSetWinner.Enabled = false;
            this.btnSetWinner.Location = new System.Drawing.Point(286, 124);
            this.btnSetWinner.Name = "btnSetWinner";
            this.btnSetWinner.Size = new System.Drawing.Size(132, 24);
            this.btnSetWinner.TabIndex = 29;
            this.btnSetWinner.Text = "4- Set Winner";
            this.btnSetWinner.UseVisualStyleBackColor = true;
            this.btnSetWinner.Click += new System.EventHandler(this.btnSetWinner_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(7, 46);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(100, 13);
            this.label11.TabIndex = 16;
            this.label11.Text = "Skip bidder address";
            // 
            // txtSkip
            // 
            this.txtSkip.BackColor = System.Drawing.SystemColors.Control;
            this.txtSkip.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.txtSkip.Location = new System.Drawing.Point(112, 43);
            this.txtSkip.Name = "txtSkip";
            this.txtSkip.Size = new System.Drawing.Size(342, 20);
            this.txtSkip.TabIndex = 17;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Enabled = false;
            this.checkBox1.Location = new System.Drawing.Point(10, 20);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(148, 17);
            this.checkBox1.TabIndex = 0;
            this.checkBox1.Text = "I\'m a malicious Auctioneer";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            // 
            // AuctioneerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(501, 551);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "AuctioneerForm";
            this.Text = "Auctioneer";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox txtAuctioneerBalance;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtAuctioneerAddress;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtContractAddress;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnDeployContract;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtEnclavePublicKey;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtEnclaveAddress;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtEnclaveBalance;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btnInitializeEnclave;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ProgressBar prgWithdraw;
        private System.Windows.Forms.ProgressBar prgDispute;
        private System.Windows.Forms.ProgressBar prgWinner;
        private System.Windows.Forms.ProgressBar prgBidding;
        private System.Windows.Forms.TextBox txtWithdraw;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtDispute;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtBidding;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtWinner;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnStartAuction;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnSetWinner;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox txtSkip;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Timer timer1;
    }
}