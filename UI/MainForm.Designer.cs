namespace UI
{
    partial class MainForm
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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.prgRefund = new System.Windows.Forms.ProgressBar();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.prgDispute = new System.Windows.Forms.ProgressBar();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.prgWinner = new System.Windows.Forms.ProgressBar();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnSubmit = new System.Windows.Forms.Button();
            this.txtBid = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.actionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuDeploy = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuInitializeSGX = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuStartAuction = new System.Windows.Forms.ToolStripMenuItem();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.indexDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.bidDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.addressDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.publicKeyDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.sealedBidDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.bidderBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lstLog = new System.Windows.Forms.ListBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.prgBidding = new System.Windows.Forms.ProgressBar();
            this.button1 = new System.Windows.Forms.Button();
            this.txtWinAddress = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtWinBid = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bidderBindingSource)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.OutsetDouble;
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.groupBox1, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.groupBox2, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.groupBox4, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 24);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 88F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 427F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 285F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1180, 667);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tableLayoutPanel2);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(6, 6);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(1168, 82);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Auction Intervals";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Inset;
            this.tableLayoutPanel2.ColumnCount = 4;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel2.Controls.Add(this.groupBox7, 3, 0);
            this.tableLayoutPanel2.Controls.Add(this.groupBox6, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.groupBox5, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.tableLayoutPanel3, 0, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 16);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.Size = new System.Drawing.Size(1162, 63);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.prgRefund);
            this.groupBox7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox7.Location = new System.Drawing.Point(875, 5);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(282, 53);
            this.groupBox7.TabIndex = 7;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Refund";
            // 
            // prgRefund
            // 
            this.prgRefund.Location = new System.Drawing.Point(2, 19);
            this.prgRefund.Name = "prgRefund";
            this.prgRefund.Size = new System.Drawing.Size(270, 28);
            this.prgRefund.Step = 1;
            this.prgRefund.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.prgRefund.TabIndex = 1;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.prgDispute);
            this.groupBox6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox6.Location = new System.Drawing.Point(585, 5);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(282, 53);
            this.groupBox6.TabIndex = 6;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Dispute";
            // 
            // prgDispute
            // 
            this.prgDispute.Location = new System.Drawing.Point(2, 19);
            this.prgDispute.Name = "prgDispute";
            this.prgDispute.Size = new System.Drawing.Size(270, 28);
            this.prgDispute.Step = 1;
            this.prgDispute.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.prgDispute.TabIndex = 1;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.prgWinner);
            this.groupBox5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox5.Location = new System.Drawing.Point(295, 5);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(282, 53);
            this.groupBox5.TabIndex = 5;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Set Winner";
            // 
            // prgWinner
            // 
            this.prgWinner.Location = new System.Drawing.Point(6, 19);
            this.prgWinner.Name = "prgWinner";
            this.prgWinner.Size = new System.Drawing.Size(270, 28);
            this.prgWinner.Step = 1;
            this.prgWinner.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.prgWinner.TabIndex = 1;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 1;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 333F));
            this.tableLayoutPanel3.Controls.Add(this.groupBox3, 0, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(5, 5);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(282, 53);
            this.tableLayoutPanel3.TabIndex = 4;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.button1);
            this.groupBox4.Controls.Add(this.txtWinAddress);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.txtWinBid);
            this.groupBox4.Controls.Add(this.label2);
            this.groupBox4.Controls.Add(this.btnSubmit);
            this.groupBox4.Controls.Add(this.txtBid);
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.dataGridView1);
            this.groupBox4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox4.Location = new System.Drawing.Point(6, 97);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(1168, 421);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Bidders";
            // 
            // btnSubmit
            // 
            this.btnSubmit.Location = new System.Drawing.Point(230, 11);
            this.btnSubmit.Name = "btnSubmit";
            this.btnSubmit.Size = new System.Drawing.Size(112, 23);
            this.btnSubmit.TabIndex = 3;
            this.btnSubmit.Text = "Submit";
            this.btnSubmit.UseVisualStyleBackColor = true;
            this.btnSubmit.Click += new System.EventHandler(this.btnSubmit_Click);
            // 
            // txtBid
            // 
            this.txtBid.Location = new System.Drawing.Point(34, 13);
            this.txtBid.Name = "txtBid";
            this.txtBid.Size = new System.Drawing.Size(177, 20);
            this.txtBid.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(22, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Bid";
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.AutoGenerateColumns = false;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.indexDataGridViewTextBoxColumn,
            this.bidDataGridViewTextBoxColumn,
            this.addressDataGridViewTextBoxColumn,
            this.publicKeyDataGridViewTextBoxColumn,
            this.sealedBidDataGridViewTextBoxColumn});
            this.dataGridView1.DataSource = this.bidderBindingSource;
            this.dataGridView1.Location = new System.Drawing.Point(3, 40);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView1.Size = new System.Drawing.Size(1157, 337);
            this.dataGridView1.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.actionsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1180, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // actionsToolStripMenuItem
            // 
            this.actionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuDeploy,
            this.mnuInitializeSGX,
            this.mnuStartAuction});
            this.actionsToolStripMenuItem.Name = "actionsToolStripMenuItem";
            this.actionsToolStripMenuItem.Size = new System.Drawing.Size(59, 20);
            this.actionsToolStripMenuItem.Text = "Actions";
            // 
            // mnuDeploy
            // 
            this.mnuDeploy.Name = "mnuDeploy";
            this.mnuDeploy.Size = new System.Drawing.Size(174, 22);
            this.mnuDeploy.Text = "1- Deploy Contract";
            this.mnuDeploy.Click += new System.EventHandler(this.mnuDeploy_Click);
            // 
            // mnuInitializeSGX
            // 
            this.mnuInitializeSGX.Name = "mnuInitializeSGX";
            this.mnuInitializeSGX.Size = new System.Drawing.Size(174, 22);
            this.mnuInitializeSGX.Text = "2- Initialize SGX";
            this.mnuInitializeSGX.Click += new System.EventHandler(this.mnuInitializeSGX_Click);
            // 
            // mnuStartAuction
            // 
            this.mnuStartAuction.Name = "mnuStartAuction";
            this.mnuStartAuction.Size = new System.Drawing.Size(174, 22);
            this.mnuStartAuction.Text = "3- Start Auction";
            this.mnuStartAuction.Click += new System.EventHandler(this.mnuStartAuction_Click);
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            // 
            // timer2
            // 
            this.timer2.Interval = 1000;
            // 
            // indexDataGridViewTextBoxColumn
            // 
            this.indexDataGridViewTextBoxColumn.DataPropertyName = "Index";
            this.indexDataGridViewTextBoxColumn.HeaderText = "Index";
            this.indexDataGridViewTextBoxColumn.Name = "indexDataGridViewTextBoxColumn";
            this.indexDataGridViewTextBoxColumn.ReadOnly = true;
            this.indexDataGridViewTextBoxColumn.Width = 60;
            // 
            // bidDataGridViewTextBoxColumn
            // 
            this.bidDataGridViewTextBoxColumn.DataPropertyName = "Bid";
            this.bidDataGridViewTextBoxColumn.FillWeight = 350.365F;
            this.bidDataGridViewTextBoxColumn.HeaderText = "Bid";
            this.bidDataGridViewTextBoxColumn.Name = "bidDataGridViewTextBoxColumn";
            this.bidDataGridViewTextBoxColumn.ReadOnly = true;
            this.bidDataGridViewTextBoxColumn.Width = 120;
            // 
            // addressDataGridViewTextBoxColumn
            // 
            this.addressDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.addressDataGridViewTextBoxColumn.DataPropertyName = "Address";
            this.addressDataGridViewTextBoxColumn.FillWeight = 16.54501F;
            this.addressDataGridViewTextBoxColumn.HeaderText = "Address";
            this.addressDataGridViewTextBoxColumn.Name = "addressDataGridViewTextBoxColumn";
            this.addressDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // publicKeyDataGridViewTextBoxColumn
            // 
            this.publicKeyDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.publicKeyDataGridViewTextBoxColumn.DataPropertyName = "PublicKey";
            this.publicKeyDataGridViewTextBoxColumn.FillWeight = 16.54501F;
            this.publicKeyDataGridViewTextBoxColumn.HeaderText = "PublicKey";
            this.publicKeyDataGridViewTextBoxColumn.Name = "publicKeyDataGridViewTextBoxColumn";
            this.publicKeyDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // sealedBidDataGridViewTextBoxColumn
            // 
            this.sealedBidDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.sealedBidDataGridViewTextBoxColumn.DataPropertyName = "SealedBid";
            this.sealedBidDataGridViewTextBoxColumn.FillWeight = 16.54501F;
            this.sealedBidDataGridViewTextBoxColumn.HeaderText = "SealedBid";
            this.sealedBidDataGridViewTextBoxColumn.Name = "sealedBidDataGridViewTextBoxColumn";
            this.sealedBidDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // bidderBindingSource
            // 
            this.bidderBindingSource.DataSource = typeof(ManagedAuction.Bidder);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.lstLog);
            this.groupBox1.Location = new System.Drawing.Point(6, 527);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1165, 128);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Log";
            // 
            // lstLog
            // 
            this.lstLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstLog.FormattingEnabled = true;
            this.lstLog.Location = new System.Drawing.Point(3, 16);
            this.lstLog.Name = "lstLog";
            this.lstLog.Size = new System.Drawing.Size(1159, 109);
            this.lstLog.TabIndex = 0;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.prgBidding);
            this.groupBox3.Location = new System.Drawing.Point(3, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(279, 47);
            this.groupBox3.TabIndex = 6;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Set Winner";
            // 
            // prgBidding
            // 
            this.prgBidding.Dock = System.Windows.Forms.DockStyle.Fill;
            this.prgBidding.Location = new System.Drawing.Point(3, 16);
            this.prgBidding.Name = "prgBidding";
            this.prgBidding.Size = new System.Drawing.Size(273, 28);
            this.prgBidding.Step = 1;
            this.prgBidding.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.prgBidding.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.Enabled = false;
            this.button1.Location = new System.Drawing.Point(686, 385);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(112, 23);
            this.button1.TabIndex = 15;
            this.button1.Text = "Who is the Winner?";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // txtWinAddress
            // 
            this.txtWinAddress.Location = new System.Drawing.Point(345, 387);
            this.txtWinAddress.Name = "txtWinAddress";
            this.txtWinAddress.Size = new System.Drawing.Size(324, 20);
            this.txtWinAddress.TabIndex = 14;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(280, 390);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(45, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "Address";
            // 
            // txtWinBid
            // 
            this.txtWinBid.Location = new System.Drawing.Point(71, 387);
            this.txtWinBid.Name = "txtWinBid";
            this.txtWinBid.Size = new System.Drawing.Size(187, 20);
            this.txtWinBid.TabIndex = 12;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 390);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "Winner Bid";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1180, 691);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Trustee";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bidderBindingSource)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnSubmit;
        private System.Windows.Forms.TextBox txtBid;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem actionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mnuDeploy;
        private System.Windows.Forms.ToolStripMenuItem mnuInitializeSGX;
        private System.Windows.Forms.ToolStripMenuItem mnuStartAuction;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.ProgressBar prgRefund;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.ProgressBar prgDispute;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.ProgressBar prgWinner;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.BindingSource bidderBindingSource;
        private System.Windows.Forms.DataGridViewTextBoxColumn indexDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn bidDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn addressDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn publicKeyDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn sealedBidDataGridViewTextBoxColumn;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ListBox lstLog;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ProgressBar prgBidding;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox txtWinAddress;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtWinBid;
        private System.Windows.Forms.Label label2;
    }
}

