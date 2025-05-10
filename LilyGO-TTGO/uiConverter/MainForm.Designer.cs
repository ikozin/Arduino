
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
            components = new System.ComponentModel.Container();
            System.Windows.Forms.Label labelPositionX;
            System.Windows.Forms.Label labelPositionY;
            System.Windows.Forms.Label labelWidth;
            System.Windows.Forms.Label labelHeight;
            System.Windows.Forms.Label labelBackColor;
            System.Windows.Forms.Label labelForeColor;
            System.Windows.Forms.Panel panelMain;
            System.Windows.Forms.Button btnLoad;
            System.Windows.Forms.Panel panelView;
            btnSaveWH = new System.Windows.Forms.Button();
            btnSave = new System.Windows.Forms.Button();
            panelInfo = new System.Windows.Forms.Panel();
            textBoxForeColor = new System.Windows.Forms.TextBox();
            textBoxBackColor = new System.Windows.Forms.TextBox();
            textBoxHeight = new System.Windows.Forms.TextBox();
            textBoxWidth = new System.Windows.Forms.TextBox();
            numericPosY = new System.Windows.Forms.NumericUpDown();
            numericPosX = new System.Windows.Forms.NumericUpDown();
            checkBoxSwap = new System.Windows.Forms.CheckBox();
            pictureBox = new System.Windows.Forms.PictureBox();
            panelViewTool = new System.Windows.Forms.Panel();
            comboBoxScale = new System.Windows.Forms.ComboBox();
            comboBoxSizeMode = new System.Windows.Forms.ComboBox();
            openFileDlg = new System.Windows.Forms.OpenFileDialog();
            toolTip = new System.Windows.Forms.ToolTip(components);
            folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            btnHexClip = new System.Windows.Forms.Button();
            labelPositionX = new System.Windows.Forms.Label();
            labelPositionY = new System.Windows.Forms.Label();
            labelWidth = new System.Windows.Forms.Label();
            labelHeight = new System.Windows.Forms.Label();
            labelBackColor = new System.Windows.Forms.Label();
            labelForeColor = new System.Windows.Forms.Label();
            panelMain = new System.Windows.Forms.Panel();
            btnLoad = new System.Windows.Forms.Button();
            panelView = new System.Windows.Forms.Panel();
            panelMain.SuspendLayout();
            panelInfo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numericPosY).BeginInit();
            ((System.ComponentModel.ISupportInitialize)numericPosX).BeginInit();
            panelView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)pictureBox).BeginInit();
            panelViewTool.SuspendLayout();
            SuspendLayout();
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
            panelMain.Controls.Add(btnHexClip);
            panelMain.Controls.Add(btnSaveWH);
            panelMain.Controls.Add(btnSave);
            panelMain.Controls.Add(btnLoad);
            panelMain.Controls.Add(panelInfo);
            panelMain.Dock = System.Windows.Forms.DockStyle.Left;
            panelMain.Location = new System.Drawing.Point(0, 0);
            panelMain.Name = "panelMain";
            panelMain.Size = new System.Drawing.Size(227, 481);
            panelMain.TabIndex = 0;
            // 
            // btnSaveWH
            // 
            btnSaveWH.Location = new System.Drawing.Point(12, 82);
            btnSaveWH.Name = "btnSaveWH";
            btnSaveWH.Size = new System.Drawing.Size(209, 29);
            btnSaveWH.TabIndex = 3;
            btnSaveWH.Text = "Save (Width+Height)...";
            btnSaveWH.UseVisualStyleBackColor = true;
            btnSaveWH.Click += btnSaveWH_Click;
            // 
            // btnSave
            // 
            btnSave.Location = new System.Drawing.Point(12, 47);
            btnSave.Name = "btnSave";
            btnSave.Size = new System.Drawing.Size(209, 29);
            btnSave.TabIndex = 0;
            btnSave.Text = "Save ...";
            btnSave.UseVisualStyleBackColor = true;
            btnSave.Click += btnSave_Click;
            // 
            // btnLoad
            // 
            btnLoad.Location = new System.Drawing.Point(12, 12);
            btnLoad.Name = "btnLoad";
            btnLoad.Size = new System.Drawing.Size(209, 29);
            btnLoad.TabIndex = 2;
            btnLoad.Text = "Load ...";
            btnLoad.UseVisualStyleBackColor = true;
            btnLoad.Click += btnLoad_Click;
            // 
            // panelInfo
            // 
            panelInfo.Anchor = System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right;
            panelInfo.Controls.Add(textBoxForeColor);
            panelInfo.Controls.Add(labelForeColor);
            panelInfo.Controls.Add(textBoxBackColor);
            panelInfo.Controls.Add(labelBackColor);
            panelInfo.Controls.Add(textBoxHeight);
            panelInfo.Controls.Add(labelHeight);
            panelInfo.Controls.Add(textBoxWidth);
            panelInfo.Controls.Add(labelWidth);
            panelInfo.Controls.Add(numericPosY);
            panelInfo.Controls.Add(labelPositionY);
            panelInfo.Controls.Add(numericPosX);
            panelInfo.Controls.Add(labelPositionX);
            panelInfo.Controls.Add(checkBoxSwap);
            panelInfo.Enabled = false;
            panelInfo.Location = new System.Drawing.Point(0, 213);
            panelInfo.Name = "panelInfo";
            panelInfo.Size = new System.Drawing.Size(227, 268);
            panelInfo.TabIndex = 0;
            // 
            // textBoxForeColor
            // 
            textBoxForeColor.Location = new System.Drawing.Point(95, 219);
            textBoxForeColor.Name = "textBoxForeColor";
            textBoxForeColor.Size = new System.Drawing.Size(104, 27);
            textBoxForeColor.TabIndex = 33;
            textBoxForeColor.Text = "FFFFFFFF";
            toolTip.SetToolTip(textBoxForeColor, "Double click to select a color");
            textBoxForeColor.MouseDoubleClick += textBoxColor_MouseDoubleClick;
            // 
            // textBoxBackColor
            // 
            textBoxBackColor.Location = new System.Drawing.Point(95, 182);
            textBoxBackColor.Name = "textBoxBackColor";
            textBoxBackColor.Size = new System.Drawing.Size(104, 27);
            textBoxBackColor.TabIndex = 31;
            toolTip.SetToolTip(textBoxBackColor, "Double click to select a color");
            textBoxBackColor.MouseDoubleClick += textBoxColor_MouseDoubleClick;
            // 
            // textBoxHeight
            // 
            textBoxHeight.Location = new System.Drawing.Point(138, 142);
            textBoxHeight.Name = "textBoxHeight";
            textBoxHeight.ReadOnly = true;
            textBoxHeight.Size = new System.Drawing.Size(61, 27);
            textBoxHeight.TabIndex = 26;
            // 
            // textBoxWidth
            // 
            textBoxWidth.Location = new System.Drawing.Point(138, 107);
            textBoxWidth.Name = "textBoxWidth";
            textBoxWidth.ReadOnly = true;
            textBoxWidth.Size = new System.Drawing.Size(61, 27);
            textBoxWidth.TabIndex = 24;
            // 
            // numericPosY
            // 
            numericPosY.Location = new System.Drawing.Point(95, 71);
            numericPosY.Maximum = new decimal(new int[] { 240, 0, 0, 0 });
            numericPosY.Name = "numericPosY";
            numericPosY.Size = new System.Drawing.Size(104, 27);
            numericPosY.TabIndex = 4;
            // 
            // numericPosX
            // 
            numericPosX.Location = new System.Drawing.Point(93, 37);
            numericPosX.Maximum = new decimal(new int[] { 240, 0, 0, 0 });
            numericPosX.Name = "numericPosX";
            numericPosX.Size = new System.Drawing.Size(106, 27);
            numericPosX.TabIndex = 2;
            // 
            // checkBoxSwap
            // 
            checkBoxSwap.Checked = true;
            checkBoxSwap.CheckState = System.Windows.Forms.CheckState.Checked;
            checkBoxSwap.Location = new System.Drawing.Point(12, 12);
            checkBoxSwap.Name = "checkBoxSwap";
            checkBoxSwap.Size = new System.Drawing.Size(106, 24);
            checkBoxSwap.TabIndex = 0;
            checkBoxSwap.Text = "Swap Bytes";
            checkBoxSwap.UseVisualStyleBackColor = true;
            // 
            // panelView
            // 
            panelView.Controls.Add(pictureBox);
            panelView.Controls.Add(panelViewTool);
            panelView.Dock = System.Windows.Forms.DockStyle.Fill;
            panelView.Location = new System.Drawing.Point(227, 0);
            panelView.Name = "panelView";
            panelView.Size = new System.Drawing.Size(568, 481);
            panelView.TabIndex = 2;
            // 
            // pictureBox
            // 
            pictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            pictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            pictureBox.Location = new System.Drawing.Point(0, 41);
            pictureBox.Name = "pictureBox";
            pictureBox.Size = new System.Drawing.Size(568, 440);
            pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            pictureBox.TabIndex = 1;
            pictureBox.TabStop = false;
            pictureBox.MouseClick += pictureBox_MouseClick;
            // 
            // panelViewTool
            // 
            panelViewTool.Controls.Add(comboBoxScale);
            panelViewTool.Controls.Add(comboBoxSizeMode);
            panelViewTool.Dock = System.Windows.Forms.DockStyle.Top;
            panelViewTool.Location = new System.Drawing.Point(0, 0);
            panelViewTool.Name = "panelViewTool";
            panelViewTool.Size = new System.Drawing.Size(568, 41);
            panelViewTool.TabIndex = 2;
            // 
            // comboBoxScale
            // 
            comboBoxScale.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            comboBoxScale.FormattingEnabled = true;
            comboBoxScale.Items.AddRange(new object[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" });
            comboBoxScale.Location = new System.Drawing.Point(194, 6);
            comboBoxScale.Name = "comboBoxScale";
            comboBoxScale.Size = new System.Drawing.Size(151, 28);
            comboBoxScale.TabIndex = 1;
            comboBoxScale.SelectionChangeCommitted += comboBoxScale_SelectionChangeCommitted;
            // 
            // comboBoxSizeMode
            // 
            comboBoxSizeMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            comboBoxSizeMode.FormattingEnabled = true;
            comboBoxSizeMode.Location = new System.Drawing.Point(6, 6);
            comboBoxSizeMode.Name = "comboBoxSizeMode";
            comboBoxSizeMode.Size = new System.Drawing.Size(151, 28);
            comboBoxSizeMode.TabIndex = 0;
            comboBoxSizeMode.SelectionChangeCommitted += comboBoxSizeMode_SelectionChangeCommitted;
            // 
            // openFileDlg
            // 
            openFileDlg.Filter = "All files|*.*";
            // 
            // btnHexClip
            // 
            btnHexClip.Location = new System.Drawing.Point(12, 117);
            btnHexClip.Name = "btnHexClip";
            btnHexClip.Size = new System.Drawing.Size(209, 29);
            btnHexClip.TabIndex = 4;
            btnHexClip.Text = "HEX to Clipboard";
            btnHexClip.UseVisualStyleBackColor = true;
            btnHexClip.Click += btnHexClip_Click;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            ClientSize = new System.Drawing.Size(795, 481);
            Controls.Add(panelView);
            Controls.Add(panelMain);
            Name = "MainForm";
            Text = "LilyGO-TTGO T-Display [135 x 240]";
            panelMain.ResumeLayout(false);
            panelInfo.ResumeLayout(false);
            panelInfo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numericPosY).EndInit();
            ((System.ComponentModel.ISupportInitialize)numericPosX).EndInit();
            panelView.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)pictureBox).EndInit();
            panelViewTool.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private System.Windows.Forms.Panel panelMain;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Button btnSave;
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
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
        private System.Windows.Forms.Panel panelViewTool;
        private System.Windows.Forms.ComboBox comboBoxSizeMode;
        private System.Windows.Forms.Button btnSaveWH;
        private System.Windows.Forms.ComboBox comboBoxScale;
        private System.Windows.Forms.Button btnHexClip;
    }
}

