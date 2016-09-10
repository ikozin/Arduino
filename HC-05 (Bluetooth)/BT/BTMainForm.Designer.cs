namespace BT
{
    partial class BtMainForm
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
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem5;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem6;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem7;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem8;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem9;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem10;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem11;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem12;
            System.Windows.Forms.ToolStripMenuItem toolStripMenuItem13;
            this.btnRefreshComList = new System.Windows.Forms.Button();
            this.btnConnect = new System.Windows.Forms.Button();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.comboBoxBaudRate = new System.Windows.Forms.ComboBox();
            this.comboBoxComList = new System.Windows.Forms.ComboBox();
            this.contextMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pasteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sepToolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.clearToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.btnSend = new System.Windows.Forms.Button();
            this.textBoxSend = new System.Windows.Forms.TextBox();
            this.contextMenuStripSend = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItem14 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem15 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem16 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem17 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem18 = new System.Windows.Forms.ToolStripMenuItem();
            this.textBoxData = new System.Windows.Forms.TextBox();
            this.checkBoxNewLine = new System.Windows.Forms.CheckBox();
            this.btnHelp = new System.Windows.Forms.Button();
            toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem5 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem6 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem7 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem8 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem9 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem10 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem11 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem12 = new System.Windows.Forms.ToolStripMenuItem();
            toolStripMenuItem13 = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip.SuspendLayout();
            this.contextMenuStripSend.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStripMenuItem1
            // 
            toolStripMenuItem1.Name = "toolStripMenuItem1";
            toolStripMenuItem1.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem1.Text = "AT";
            toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem2
            // 
            toolStripMenuItem2.Name = "toolStripMenuItem2";
            toolStripMenuItem2.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem2.Text = "AT+VERSION?";
            toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem3
            // 
            toolStripMenuItem3.Name = "toolStripMenuItem3";
            toolStripMenuItem3.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem3.Text = "AT+ADDR?";
            toolStripMenuItem3.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem4
            // 
            toolStripMenuItem4.Name = "toolStripMenuItem4";
            toolStripMenuItem4.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem4.Text = "AT+NAME?";
            toolStripMenuItem4.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem5
            // 
            toolStripMenuItem5.Name = "toolStripMenuItem5";
            toolStripMenuItem5.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem5.Text = "AT+ROLE?";
            toolStripMenuItem5.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem6
            // 
            toolStripMenuItem6.Name = "toolStripMenuItem6";
            toolStripMenuItem6.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem6.Text = "AT+CLASS?";
            toolStripMenuItem6.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem7
            // 
            toolStripMenuItem7.Name = "toolStripMenuItem7";
            toolStripMenuItem7.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem7.Text = "AT+IAC?";
            toolStripMenuItem7.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem8
            // 
            toolStripMenuItem8.Name = "toolStripMenuItem8";
            toolStripMenuItem8.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem8.Text = "AT+INQM?";
            toolStripMenuItem8.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem9
            // 
            toolStripMenuItem9.Name = "toolStripMenuItem9";
            toolStripMenuItem9.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem9.Text = "AT+PSWD?";
            toolStripMenuItem9.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem10
            // 
            toolStripMenuItem10.Name = "toolStripMenuItem10";
            toolStripMenuItem10.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem10.Text = "AT+UART?";
            toolStripMenuItem10.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem11
            // 
            toolStripMenuItem11.Name = "toolStripMenuItem11";
            toolStripMenuItem11.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem11.Text = "AT+CMODE?";
            toolStripMenuItem11.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem12
            // 
            toolStripMenuItem12.Name = "toolStripMenuItem12";
            toolStripMenuItem12.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem12.Text = "AT+BIND?";
            toolStripMenuItem12.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem13
            // 
            toolStripMenuItem13.Name = "toolStripMenuItem13";
            toolStripMenuItem13.Size = new System.Drawing.Size(149, 22);
            toolStripMenuItem13.Text = "AT+MPIO?";
            toolStripMenuItem13.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // btnRefreshComList
            // 
            this.btnRefreshComList.Location = new System.Drawing.Point(12, 12);
            this.btnRefreshComList.Name = "btnRefreshComList";
            this.btnRefreshComList.Size = new System.Drawing.Size(100, 23);
            this.btnRefreshComList.TabIndex = 0;
            this.btnRefreshComList.Text = "Обновить";
            this.btnRefreshComList.UseVisualStyleBackColor = true;
            this.btnRefreshComList.Click += new System.EventHandler(this.btnRefreshComList_Click);
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(290, 12);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(100, 23);
            this.btnConnect.TabIndex = 3;
            this.btnConnect.Text = "Подключиться";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // serialPort
            // 
            this.serialPort.ParityReplace = ((byte)(0));
            this.serialPort.ErrorReceived += new System.IO.Ports.SerialErrorReceivedEventHandler(this.serialPort_ErrorReceived);
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // comboBoxBaudRate
            // 
            this.comboBoxBaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxBaudRate.FormattingEnabled = true;
            this.comboBoxBaudRate.Items.AddRange(new object[] {
            "300",
            "1200",
            "2400",
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200",
            "460800 ",
            "921600 ",
            "1382400"});
            this.comboBoxBaudRate.Location = new System.Drawing.Point(204, 12);
            this.comboBoxBaudRate.Name = "comboBoxBaudRate";
            this.comboBoxBaudRate.Size = new System.Drawing.Size(80, 21);
            this.comboBoxBaudRate.TabIndex = 2;
            // 
            // comboBoxComList
            // 
            this.comboBoxComList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxComList.FormattingEnabled = true;
            this.comboBoxComList.Location = new System.Drawing.Point(118, 12);
            this.comboBoxComList.Name = "comboBoxComList";
            this.comboBoxComList.Size = new System.Drawing.Size(80, 21);
            this.comboBoxComList.TabIndex = 1;
            // 
            // contextMenuStrip
            // 
            this.contextMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem,
            this.cutToolStripMenuItem,
            this.pasteToolStripMenuItem,
            this.selectAllToolStripMenuItem,
            this.sepToolStripMenuItem1,
            this.clearToolStripMenuItem});
            this.contextMenuStrip.Name = "contextMenuStrip";
            this.contextMenuStrip.Size = new System.Drawing.Size(165, 120);
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.copyToolStripMenuItem.Text = "Copy";
            this.copyToolStripMenuItem.Click += new System.EventHandler(this.copyToolStripMenuItem_Click);
            // 
            // cutToolStripMenuItem
            // 
            this.cutToolStripMenuItem.Name = "cutToolStripMenuItem";
            this.cutToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.cutToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.cutToolStripMenuItem.Text = "Cut";
            this.cutToolStripMenuItem.Click += new System.EventHandler(this.cutToolStripMenuItem_Click);
            // 
            // pasteToolStripMenuItem
            // 
            this.pasteToolStripMenuItem.Name = "pasteToolStripMenuItem";
            this.pasteToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.pasteToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.pasteToolStripMenuItem.Text = "Paste";
            this.pasteToolStripMenuItem.Click += new System.EventHandler(this.pasteToolStripMenuItem_Click);
            // 
            // selectAllToolStripMenuItem
            // 
            this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
            this.selectAllToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.selectAllToolStripMenuItem.Text = "Select All";
            this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.selectAllToolStripMenuItem_Click);
            // 
            // sepToolStripMenuItem1
            // 
            this.sepToolStripMenuItem1.Name = "sepToolStripMenuItem1";
            this.sepToolStripMenuItem1.Size = new System.Drawing.Size(161, 6);
            // 
            // clearToolStripMenuItem
            // 
            this.clearToolStripMenuItem.Name = "clearToolStripMenuItem";
            this.clearToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.clearToolStripMenuItem.Text = "Clear";
            this.clearToolStripMenuItem.Click += new System.EventHandler(this.clearToolStripMenuItem_Click);
            // 
            // btnSend
            // 
            this.btnSend.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSend.Location = new System.Drawing.Point(437, 296);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(75, 23);
            this.btnSend.TabIndex = 8;
            this.btnSend.Text = "Отправить";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // textBoxSend
            // 
            this.textBoxSend.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxSend.ContextMenuStrip = this.contextMenuStripSend;
            this.textBoxSend.Location = new System.Drawing.Point(12, 298);
            this.textBoxSend.Name = "textBoxSend";
            this.textBoxSend.Size = new System.Drawing.Size(345, 20);
            this.textBoxSend.TabIndex = 6;
            // 
            // contextMenuStripSend
            // 
            this.contextMenuStripSend.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            toolStripMenuItem1,
            toolStripMenuItem2,
            toolStripMenuItem3,
            toolStripMenuItem4,
            toolStripMenuItem5,
            toolStripMenuItem6,
            toolStripMenuItem7,
            toolStripMenuItem8,
            toolStripMenuItem9,
            toolStripMenuItem10,
            toolStripMenuItem11,
            toolStripMenuItem12,
            toolStripMenuItem13,
            this.toolStripMenuItem14,
            this.toolStripMenuItem15,
            this.toolStripMenuItem16,
            this.toolStripMenuItem17,
            this.toolStripMenuItem18});
            this.contextMenuStripSend.Name = "contextMenuStripSend";
            this.contextMenuStripSend.Size = new System.Drawing.Size(150, 400);
            // 
            // toolStripMenuItem14
            // 
            this.toolStripMenuItem14.Name = "toolStripMenuItem14";
            this.toolStripMenuItem14.Size = new System.Drawing.Size(149, 22);
            this.toolStripMenuItem14.Text = "AT+IPSCAN?";
            this.toolStripMenuItem14.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem15
            // 
            this.toolStripMenuItem15.Name = "toolStripMenuItem15";
            this.toolStripMenuItem15.Size = new System.Drawing.Size(149, 22);
            this.toolStripMenuItem15.Text = "AT+SENM?";
            this.toolStripMenuItem15.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem16
            // 
            this.toolStripMenuItem16.Name = "toolStripMenuItem16";
            this.toolStripMenuItem16.Size = new System.Drawing.Size(149, 22);
            this.toolStripMenuItem16.Text = "AT+ADCN?";
            this.toolStripMenuItem16.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem17
            // 
            this.toolStripMenuItem17.Name = "toolStripMenuItem17";
            this.toolStripMenuItem17.Size = new System.Drawing.Size(149, 22);
            this.toolStripMenuItem17.Text = "AT+MRAD?";
            this.toolStripMenuItem17.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // toolStripMenuItem18
            // 
            this.toolStripMenuItem18.Name = "toolStripMenuItem18";
            this.toolStripMenuItem18.Size = new System.Drawing.Size(149, 22);
            this.toolStripMenuItem18.Text = "AT+STATE?";
            this.toolStripMenuItem18.Click += new System.EventHandler(this.toolStripMenuItem_Click);
            // 
            // textBoxData
            // 
            this.textBoxData.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxData.ContextMenuStrip = this.contextMenuStrip;
            this.textBoxData.Location = new System.Drawing.Point(12, 41);
            this.textBoxData.Multiline = true;
            this.textBoxData.Name = "textBoxData";
            this.textBoxData.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxData.Size = new System.Drawing.Size(498, 248);
            this.textBoxData.TabIndex = 5;
            this.textBoxData.WordWrap = false;
            // 
            // checkBoxNewLine
            // 
            this.checkBoxNewLine.AutoSize = true;
            this.checkBoxNewLine.Checked = true;
            this.checkBoxNewLine.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxNewLine.Location = new System.Drawing.Point(363, 300);
            this.checkBoxNewLine.Name = "checkBoxNewLine";
            this.checkBoxNewLine.Size = new System.Drawing.Size(68, 17);
            this.checkBoxNewLine.TabIndex = 7;
            this.checkBoxNewLine.Text = "NewLine";
            this.checkBoxNewLine.UseVisualStyleBackColor = true;
            // 
            // btnHelp
            // 
            this.btnHelp.Location = new System.Drawing.Point(396, 12);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(114, 23);
            this.btnHelp.TabIndex = 4;
            this.btnHelp.Text = "Помощь";
            this.btnHelp.UseVisualStyleBackColor = true;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // BtMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(529, 329);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.checkBoxNewLine);
            this.Controls.Add(this.textBoxData);
            this.Controls.Add(this.textBoxSend);
            this.Controls.Add(this.btnSend);
            this.Controls.Add(this.comboBoxComList);
            this.Controls.Add(this.comboBoxBaudRate);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.btnRefreshComList);
            this.MinimumSize = new System.Drawing.Size(545, 300);
            this.Name = "BtMainForm";
            this.Text = "BlueTooth";
            this.contextMenuStrip.ResumeLayout(false);
            this.contextMenuStripSend.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnConnect;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.ComboBox comboBoxBaudRate;
        private System.Windows.Forms.Button btnRefreshComList;
        private System.Windows.Forms.ComboBox comboBoxComList;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.TextBox textBoxSend;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pasteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator sepToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem clearToolStripMenuItem;
        private System.Windows.Forms.TextBox textBoxData;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripSend;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem14;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem15;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem16;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem17;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem18;
        private System.Windows.Forms.CheckBox checkBoxNewLine;
        private System.Windows.Forms.Button btnHelp;
    }
}

