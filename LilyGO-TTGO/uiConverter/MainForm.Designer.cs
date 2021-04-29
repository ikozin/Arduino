
namespace uiConverter
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.Label labelPositionX;
            System.Windows.Forms.Label labelPositionY;
            System.Windows.Forms.Label labelWidth;
            System.Windows.Forms.Label labelHeight;
            System.Windows.Forms.Label labelBackColor;
            System.Windows.Forms.Label labelForeColor;
            System.Windows.Forms.Panel panelMain;
            System.Windows.Forms.Button btnBatch;
            System.Windows.Forms.Button btnSaveRaw;
            System.Windows.Forms.Button btnLoad;
            this.panelInfo = new System.Windows.Forms.Panel();
            this.textBoxForeColor = new System.Windows.Forms.TextBox();
            this.textBoxBackColor = new System.Windows.Forms.TextBox();
            this.textBoxHeight = new System.Windows.Forms.TextBox();
            this.textBoxWidth = new System.Windows.Forms.TextBox();
            this.numericPosY = new System.Windows.Forms.NumericUpDown();
            this.numericPosX = new System.Windows.Forms.NumericUpDown();
            this.checkBoxSwap = new System.Windows.Forms.CheckBox();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.openFileDlg = new System.Windows.Forms.OpenFileDialog();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            labelPositionX = new System.Windows.Forms.Label();
            labelPositionY = new System.Windows.Forms.Label();
            labelWidth = new System.Windows.Forms.Label();
            labelHeight = new System.Windows.Forms.Label();
            labelBackColor = new System.Windows.Forms.Label();
            labelForeColor = new System.Windows.Forms.Label();
            panelMain = new System.Windows.Forms.Panel();
            btnBatch = new System.Windows.Forms.Button();
            btnSaveRaw = new System.Windows.Forms.Button();
            btnLoad = new System.Windows.Forms.Button();
            panelMain.SuspendLayout();
            this.panelInfo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericPosY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericPosX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // labelPositionX
            // 
            labelPositionX.AutoSize = true;
            labelPositionX.Location = new System.Drawing.Point(12, 39);
            labelPositionX.Name = "labelPositionX";
            labelPositionX.Size = new System.Drawing.Size(74, 20);
            labelPositionX.TabIndex = 1;
            labelPositionX.Text = "Position X";
            // 
            // labelPositionY
            // 
            labelPositionY.AutoSize = true;
            labelPositionY.Location = new System.Drawing.Point(12, 73);
            labelPositionY.Name = "labelPositionY";
            labelPositionY.Size = new System.Drawing.Size(73, 20);
            labelPositionY.TabIndex = 3;
            labelPositionY.Text = "Position Y";
            // 
            // labelWidth
            // 
            labelWidth.AutoSize = true;
            labelWidth.Location = new System.Drawing.Point(12, 110);
            labelWidth.Name = "labelWidth";
            labelWidth.Size = new System.Drawing.Size(119, 20);
            labelWidth.TabIndex = 23;
            labelWidth.Text = "Width (Max 240)";
            // 
            // labelHeight
            // 
            labelHeight.AutoSize = true;
            labelHeight.Location = new System.Drawing.Point(12, 145);
            labelHeight.Name = "labelHeight";
            labelHeight.Size = new System.Drawing.Size(124, 20);
            labelHeight.TabIndex = 25;
            labelHeight.Text = "Height (Max 135)";
            // 
            // labelBackColor
            // 
            labelBackColor.AutoSize = true;
            labelBackColor.Location = new System.Drawing.Point(12, 185);
            labelBackColor.Name = "labelBackColor";
            labelBackColor.Size = new System.Drawing.Size(76, 20);
            labelBackColor.TabIndex = 30;
            labelBackColor.Text = "BackColor";
            // 
            // labelForeColor
            // 
            labelForeColor.AutoSize = true;
            labelForeColor.Location = new System.Drawing.Point(12, 222);
            labelForeColor.Name = "labelForeColor";
            labelForeColor.Size = new System.Drawing.Size(74, 20);
            labelForeColor.TabIndex = 32;
            labelForeColor.Text = "ForeColor";
            // 
            // panelMain
            // 
            panelMain.Controls.Add(btnBatch);
            panelMain.Controls.Add(btnSaveRaw);
            panelMain.Controls.Add(btnLoad);
            panelMain.Controls.Add(this.panelInfo);
            panelMain.Dock = System.Windows.Forms.DockStyle.Left;
            panelMain.Location = new System.Drawing.Point(0, 0);
            panelMain.Name = "panelMain";
            panelMain.Size = new System.Drawing.Size(210, 385);
            panelMain.TabIndex = 0;
            // 
            // btnBatch
            // 
            btnBatch.Location = new System.Drawing.Point(12, 82);
            btnBatch.Name = "btnBatch";
            btnBatch.Size = new System.Drawing.Size(187, 29);
            btnBatch.TabIndex = 3;
            btnBatch.Text = "Batch (swap:true)";
            btnBatch.UseVisualStyleBackColor = true;
            btnBatch.Click += new System.EventHandler(this.btnBatch_Click);
            // 
            // btnSaveRaw
            // 
            btnSaveRaw.Location = new System.Drawing.Point(12, 47);
            btnSaveRaw.Name = "btnSaveRaw";
            btnSaveRaw.Size = new System.Drawing.Size(187, 29);
            btnSaveRaw.TabIndex = 0;
            btnSaveRaw.Text = "Save RAW";
            btnSaveRaw.UseVisualStyleBackColor = true;
            btnSaveRaw.Click += new System.EventHandler(this.btnSaveRaw_Click);
            // 
            // btnLoad
            // 
            btnLoad.Location = new System.Drawing.Point(12, 12);
            btnLoad.Name = "btnLoad";
            btnLoad.Size = new System.Drawing.Size(187, 29);
            btnLoad.TabIndex = 2;
            btnLoad.Text = "Load";
            btnLoad.UseVisualStyleBackColor = true;
            btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
            // 
            // panelInfo
            // 
            this.panelInfo.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelInfo.Controls.Add(this.textBoxForeColor);
            this.panelInfo.Controls.Add(labelForeColor);
            this.panelInfo.Controls.Add(this.textBoxBackColor);
            this.panelInfo.Controls.Add(labelBackColor);
            this.panelInfo.Controls.Add(this.textBoxHeight);
            this.panelInfo.Controls.Add(labelHeight);
            this.panelInfo.Controls.Add(this.textBoxWidth);
            this.panelInfo.Controls.Add(labelWidth);
            this.panelInfo.Controls.Add(this.numericPosY);
            this.panelInfo.Controls.Add(labelPositionY);
            this.panelInfo.Controls.Add(this.numericPosX);
            this.panelInfo.Controls.Add(labelPositionX);
            this.panelInfo.Controls.Add(this.checkBoxSwap);
            this.panelInfo.Enabled = false;
            this.panelInfo.Location = new System.Drawing.Point(0, 121);
            this.panelInfo.Name = "panelInfo";
            this.panelInfo.Size = new System.Drawing.Size(210, 264);
            this.panelInfo.TabIndex = 0;
            // 
            // textBoxForeColor
            // 
            this.textBoxForeColor.Location = new System.Drawing.Point(95, 219);
            this.textBoxForeColor.Name = "textBoxForeColor";
            this.textBoxForeColor.Size = new System.Drawing.Size(104, 27);
            this.textBoxForeColor.TabIndex = 33;
            this.textBoxForeColor.Text = "FFFFFFFF";
            this.toolTip.SetToolTip(this.textBoxForeColor, "Double click to select a color");
            this.textBoxForeColor.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.textBoxColor_MouseDoubleClick);
            // 
            // textBoxBackColor
            // 
            this.textBoxBackColor.Location = new System.Drawing.Point(95, 182);
            this.textBoxBackColor.Name = "textBoxBackColor";
            this.textBoxBackColor.Size = new System.Drawing.Size(104, 27);
            this.textBoxBackColor.TabIndex = 31;
            this.toolTip.SetToolTip(this.textBoxBackColor, "Double click to select a color");
            this.textBoxBackColor.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.textBoxColor_MouseDoubleClick);
            // 
            // textBoxHeight
            // 
            this.textBoxHeight.Location = new System.Drawing.Point(138, 142);
            this.textBoxHeight.Name = "textBoxHeight";
            this.textBoxHeight.ReadOnly = true;
            this.textBoxHeight.Size = new System.Drawing.Size(61, 27);
            this.textBoxHeight.TabIndex = 26;
            // 
            // textBoxWidth
            // 
            this.textBoxWidth.Location = new System.Drawing.Point(138, 107);
            this.textBoxWidth.Name = "textBoxWidth";
            this.textBoxWidth.ReadOnly = true;
            this.textBoxWidth.Size = new System.Drawing.Size(61, 27);
            this.textBoxWidth.TabIndex = 24;
            // 
            // numericPosY
            // 
            this.numericPosY.Location = new System.Drawing.Point(95, 71);
            this.numericPosY.Name = "numericPosY";
            this.numericPosY.Size = new System.Drawing.Size(104, 27);
            this.numericPosY.TabIndex = 4;
            // 
            // numericPosX
            // 
            this.numericPosX.Location = new System.Drawing.Point(93, 37);
            this.numericPosX.Name = "numericPosX";
            this.numericPosX.Size = new System.Drawing.Size(106, 27);
            this.numericPosX.TabIndex = 2;
            // 
            // checkBoxSwap
            // 
            this.checkBoxSwap.Checked = true;
            this.checkBoxSwap.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxSwap.Location = new System.Drawing.Point(12, 12);
            this.checkBoxSwap.Name = "checkBoxSwap";
            this.checkBoxSwap.Size = new System.Drawing.Size(106, 24);
            this.checkBoxSwap.TabIndex = 0;
            this.checkBoxSwap.Text = "Swap Bytes";
            this.checkBoxSwap.UseVisualStyleBackColor = true;
            // 
            // pictureBox
            // 
            this.pictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox.Location = new System.Drawing.Point(210, 0);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(395, 385);
            this.pictureBox.TabIndex = 1;
            this.pictureBox.TabStop = false;
            this.pictureBox.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseClick);
            // 
            // openFileDlg
            // 
            this.openFileDlg.Filter = "All files|*.*";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(605, 385);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(panelMain);
            this.Name = "MainForm";
            this.Text = "LilyGO-TTGO T-Display [135 x 240]";
            panelMain.ResumeLayout(false);
            this.panelInfo.ResumeLayout(false);
            this.panelInfo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericPosY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericPosX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelMain;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Button btnSaveRaw;
        private System.Windows.Forms.Button btnLoad;
        private System.Windows.Forms.Panel panelInfo;
        private System.Windows.Forms.CheckBox checkBoxSwap;
        private System.Windows.Forms.NumericUpDown numericPosY;
        private System.Windows.Forms.NumericUpDown numericPosX;
        private System.Windows.Forms.TextBox textBoxBackColor;
        private System.Windows.Forms.TextBox textBoxHeight;
        private System.Windows.Forms.TextBox textBoxWidth;
        private System.Windows.Forms.TextBox textBoxForeColor;
        private System.Windows.Forms.OpenFileDialog openFileDlg;
        private System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.Button btnBatch;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
    }
}

