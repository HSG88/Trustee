namespace UI
{
    partial class AuctionForm
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
            this.txtBidding = new System.Windows.Forms.TextBox();
            this.txtWinner = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtDispute = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtRefund = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtDeposit = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.btnSave = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Bidding";
            // 
            // txtBidding
            // 
            this.txtBidding.Location = new System.Drawing.Point(91, 12);
            this.txtBidding.Name = "txtBidding";
            this.txtBidding.Size = new System.Drawing.Size(173, 20);
            this.txtBidding.TabIndex = 1;
            // 
            // txtWinner
            // 
            this.txtWinner.Location = new System.Drawing.Point(91, 38);
            this.txtWinner.Name = "txtWinner";
            this.txtWinner.Size = new System.Drawing.Size(173, 20);
            this.txtWinner.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 41);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Set Winner";
            // 
            // txtDispute
            // 
            this.txtDispute.Location = new System.Drawing.Point(91, 64);
            this.txtDispute.Name = "txtDispute";
            this.txtDispute.Size = new System.Drawing.Size(173, 20);
            this.txtDispute.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 67);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(43, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Dispute";
            // 
            // txtRefund
            // 
            this.txtRefund.Location = new System.Drawing.Point(91, 90);
            this.txtRefund.Name = "txtRefund";
            this.txtRefund.Size = new System.Drawing.Size(173, 20);
            this.txtRefund.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 93);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(42, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Refund";
            // 
            // txtDeposit
            // 
            this.txtDeposit.Location = new System.Drawing.Point(91, 116);
            this.txtDeposit.Name = "txtDeposit";
            this.txtDeposit.Size = new System.Drawing.Size(173, 20);
            this.txtDeposit.TabIndex = 9;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 119);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(70, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Initial Deposit";
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(189, 142);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 10;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // AuctionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(279, 173);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.txtDeposit);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txtRefund);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtDispute);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtWinner);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtBidding);
            this.Controls.Add(this.label1);
            this.Name = "AuctionForm";
            this.Text = "AuctionForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtBidding;
        private System.Windows.Forms.TextBox txtWinner;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtDispute;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtRefund;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtDeposit;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btnSave;
    }
}