
namespace ImageConvertor
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
            System.Windows.Forms.Panel panelAction;
            System.Windows.Forms.Label labelBackColor;
            System.Windows.Forms.Label labelPosY;
            System.Windows.Forms.Label labelPosX;
            System.Windows.Forms.Label labelWidth;
            System.Windows.Forms.Label labelHeight;
            System.Windows.Forms.Button btnSelectColor;
            System.Windows.Forms.Label labelForeColor;
            this.textBoxBackColor = new System.Windows.Forms.TextBox();
            this.numericPosY = new System.Windows.Forms.NumericUpDown();
            this.numericPosX = new System.Windows.Forms.NumericUpDown();
            this.checkBoxSwap = new System.Windows.Forms.CheckBox();
            this.btnSave565 = new System.Windows.Forms.Button();
            this.btnScan = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnLoad = new System.Windows.Forms.Button();
            this.textBoxHeight = new System.Windows.Forms.TextBox();
            this.textBoxWidth = new System.Windows.Forms.TextBox();
            this.panelTool = new System.Windows.Forms.Panel();
            this.numericToB = new System.Windows.Forms.NumericUpDown();
            this.numericToG = new System.Windows.Forms.NumericUpDown();
            this.numericToR = new System.Windows.Forms.NumericUpDown();
            this.numericToA = new System.Windows.Forms.NumericUpDown();
            this.btnChangeColor = new System.Windows.Forms.Button();
            this.textBoxColorFrom = new System.Windows.Forms.TextBox();
            this.listViewColor = new System.Windows.Forms.ListView();
            this.columnHeaderColor = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderCounter = new System.Windows.Forms.ColumnHeader();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.openFileDlg = new System.Windows.Forms.OpenFileDialog();
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            this.textBoxForeColor = new System.Windows.Forms.TextBox();
            panelAction = new System.Windows.Forms.Panel();
            labelBackColor = new System.Windows.Forms.Label();
            labelPosY = new System.Windows.Forms.Label();
            labelPosX = new System.Windows.Forms.Label();
            labelWidth = new System.Windows.Forms.Label();
            labelHeight = new System.Windows.Forms.Label();
            btnSelectColor = new System.Windows.Forms.Button();
            labelForeColor = new System.Windows.Forms.Label();
            panelAction.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericPosY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericPosX)).BeginInit();
            this.panelTool.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericToB)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericToG)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericToR)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericToA)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // panelAction
            // 
            panelAction.Controls.Add(labelForeColor);
            panelAction.Controls.Add(this.textBoxForeColor);
            panelAction.Controls.Add(labelBackColor);
            panelAction.Controls.Add(this.textBoxBackColor);
            panelAction.Controls.Add(labelPosY);
            panelAction.Controls.Add(labelPosX);
            panelAction.Controls.Add(this.numericPosY);
            panelAction.Controls.Add(this.numericPosX);
            panelAction.Controls.Add(this.checkBoxSwap);
            panelAction.Controls.Add(this.btnSave565);
            panelAction.Controls.Add(this.btnScan);
            panelAction.Controls.Add(this.btnSave);
            panelAction.Controls.Add(this.btnLoad);
            panelAction.Controls.Add(this.textBoxHeight);
            panelAction.Controls.Add(this.textBoxWidth);
            panelAction.Controls.Add(labelWidth);
            panelAction.Controls.Add(labelHeight);
            panelAction.Dock = System.Windows.Forms.DockStyle.Left;
            panelAction.Location = new System.Drawing.Point(0, 0);
            panelAction.Name = "panelAction";
            panelAction.Size = new System.Drawing.Size(180, 476);
            panelAction.TabIndex = 0;
            // 
            // labelBackColor
            // 
            labelBackColor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            labelBackColor.AutoSize = true;
            labelBackColor.Location = new System.Drawing.Point(10, 316);
            labelBackColor.Name = "labelBackColor";
            labelBackColor.Size = new System.Drawing.Size(76, 20);
            labelBackColor.TabIndex = 15;
            labelBackColor.Text = "BackColor";
            // 
            // textBoxBackColor
            // 
            this.textBoxBackColor.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxBackColor.Location = new System.Drawing.Point(92, 313);
            this.textBoxBackColor.Name = "textBoxBackColor";
            this.textBoxBackColor.ReadOnly = true;
            this.textBoxBackColor.Size = new System.Drawing.Size(78, 27);
            this.textBoxBackColor.TabIndex = 14;
            // 
            // labelPosY
            // 
            labelPosY.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            labelPosY.AutoSize = true;
            labelPosY.Location = new System.Drawing.Point(10, 191);
            labelPosY.Name = "labelPosY";
            labelPosY.Size = new System.Drawing.Size(73, 20);
            labelPosY.TabIndex = 13;
            labelPosY.Text = "Position Y";
            // 
            // labelPosX
            // 
            labelPosX.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            labelPosX.AutoSize = true;
            labelPosX.Location = new System.Drawing.Point(10, 160);
            labelPosX.Name = "labelPosX";
            labelPosX.Size = new System.Drawing.Size(74, 20);
            labelPosX.TabIndex = 12;
            labelPosX.Text = "Position X";
            // 
            // numericPosY
            // 
            this.numericPosY.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.numericPosY.Location = new System.Drawing.Point(92, 191);
            this.numericPosY.Maximum = new decimal(new int[] {
            135,
            0,
            0,
            0});
            this.numericPosY.Name = "numericPosY";
            this.numericPosY.Size = new System.Drawing.Size(78, 27);
            this.numericPosY.TabIndex = 11;
            // 
            // numericPosX
            // 
            this.numericPosX.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.numericPosX.Location = new System.Drawing.Point(92, 158);
            this.numericPosX.Maximum = new decimal(new int[] {
            240,
            0,
            0,
            0});
            this.numericPosX.Name = "numericPosX";
            this.numericPosX.Size = new System.Drawing.Size(78, 27);
            this.numericPosX.TabIndex = 10;
            // 
            // checkBoxSwap
            // 
            this.checkBoxSwap.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.checkBoxSwap.Checked = true;
            this.checkBoxSwap.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxSwap.Location = new System.Drawing.Point(10, 128);
            this.checkBoxSwap.Name = "checkBoxSwap";
            this.checkBoxSwap.Size = new System.Drawing.Size(160, 24);
            this.checkBoxSwap.TabIndex = 5;
            this.checkBoxSwap.Text = "Swap Bytes";
            this.checkBoxSwap.UseVisualStyleBackColor = true;
            // 
            // btnSave565
            // 
            this.btnSave565.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSave565.Location = new System.Drawing.Point(10, 391);
            this.btnSave565.Name = "btnSave565";
            this.btnSave565.Size = new System.Drawing.Size(160, 73);
            this.btnSave565.TabIndex = 4;
            this.btnSave565.Text = "Save to RGB565";
            this.btnSave565.UseVisualStyleBackColor = true;
            this.btnSave565.Click += new System.EventHandler(this.btnSave565_Click);
            // 
            // btnScan
            // 
            this.btnScan.Location = new System.Drawing.Point(10, 47);
            this.btnScan.Name = "btnScan";
            this.btnScan.Size = new System.Drawing.Size(160, 29);
            this.btnScan.TabIndex = 3;
            this.btnScan.Text = "Scan";
            this.btnScan.UseVisualStyleBackColor = true;
            this.btnScan.Click += new System.EventHandler(this.btnScan_Click);
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(10, 82);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(160, 29);
            this.btnSave.TabIndex = 1;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnLoad
            // 
            this.btnLoad.Location = new System.Drawing.Point(10, 12);
            this.btnLoad.Name = "btnLoad";
            this.btnLoad.Size = new System.Drawing.Size(160, 29);
            this.btnLoad.TabIndex = 0;
            this.btnLoad.Text = "Load";
            this.btnLoad.UseVisualStyleBackColor = true;
            this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
            // 
            // textBoxHeight
            // 
            this.textBoxHeight.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxHeight.Location = new System.Drawing.Point(92, 269);
            this.textBoxHeight.Name = "textBoxHeight";
            this.textBoxHeight.ReadOnly = true;
            this.textBoxHeight.Size = new System.Drawing.Size(78, 27);
            this.textBoxHeight.TabIndex = 6;
            // 
            // textBoxWidth
            // 
            this.textBoxWidth.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxWidth.Location = new System.Drawing.Point(92, 230);
            this.textBoxWidth.Name = "textBoxWidth";
            this.textBoxWidth.ReadOnly = true;
            this.textBoxWidth.Size = new System.Drawing.Size(78, 27);
            this.textBoxWidth.TabIndex = 5;
            // 
            // labelWidth
            // 
            labelWidth.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            labelWidth.AutoSize = true;
            labelWidth.Location = new System.Drawing.Point(10, 233);
            labelWidth.Name = "labelWidth";
            labelWidth.Size = new System.Drawing.Size(49, 20);
            labelWidth.TabIndex = 8;
            labelWidth.Text = "Width";
            // 
            // labelHeight
            // 
            labelHeight.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            labelHeight.AutoSize = true;
            labelHeight.Location = new System.Drawing.Point(10, 272);
            labelHeight.Name = "labelHeight";
            labelHeight.Size = new System.Drawing.Size(54, 20);
            labelHeight.TabIndex = 9;
            labelHeight.Text = "Height";
            // 
            // btnSelectColor
            // 
            btnSelectColor.Location = new System.Drawing.Point(407, 48);
            btnSelectColor.Name = "btnSelectColor";
            btnSelectColor.Size = new System.Drawing.Size(25, 24);
            btnSelectColor.TabIndex = 19;
            btnSelectColor.Text = "...";
            btnSelectColor.UseVisualStyleBackColor = true;
            btnSelectColor.Click += new System.EventHandler(this.btnSelectColor_Click);
            // 
            // panelTool
            // 
            this.panelTool.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelTool.Controls.Add(btnSelectColor);
            this.panelTool.Controls.Add(this.numericToB);
            this.panelTool.Controls.Add(this.numericToG);
            this.panelTool.Controls.Add(this.numericToR);
            this.panelTool.Controls.Add(this.numericToA);
            this.panelTool.Controls.Add(this.btnChangeColor);
            this.panelTool.Controls.Add(this.textBoxColorFrom);
            this.panelTool.Controls.Add(this.listViewColor);
            this.panelTool.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelTool.Enabled = false;
            this.panelTool.Location = new System.Drawing.Point(180, 287);
            this.panelTool.Name = "panelTool";
            this.panelTool.Size = new System.Drawing.Size(686, 189);
            this.panelTool.TabIndex = 8;
            // 
            // numericToB
            // 
            this.numericToB.Hexadecimal = true;
            this.numericToB.Location = new System.Drawing.Point(355, 47);
            this.numericToB.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericToB.Name = "numericToB";
            this.numericToB.Size = new System.Drawing.Size(46, 27);
            this.numericToB.TabIndex = 18;
            // 
            // numericToG
            // 
            this.numericToG.Hexadecimal = true;
            this.numericToG.Location = new System.Drawing.Point(303, 47);
            this.numericToG.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericToG.Name = "numericToG";
            this.numericToG.Size = new System.Drawing.Size(46, 27);
            this.numericToG.TabIndex = 17;
            // 
            // numericToR
            // 
            this.numericToR.Hexadecimal = true;
            this.numericToR.Location = new System.Drawing.Point(251, 47);
            this.numericToR.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericToR.Name = "numericToR";
            this.numericToR.Size = new System.Drawing.Size(46, 27);
            this.numericToR.TabIndex = 16;
            // 
            // numericToA
            // 
            this.numericToA.Hexadecimal = true;
            this.numericToA.Location = new System.Drawing.Point(199, 47);
            this.numericToA.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numericToA.Name = "numericToA";
            this.numericToA.Size = new System.Drawing.Size(46, 27);
            this.numericToA.TabIndex = 15;
            // 
            // btnChangeColor
            // 
            this.btnChangeColor.Location = new System.Drawing.Point(199, 89);
            this.btnChangeColor.Name = "btnChangeColor";
            this.btnChangeColor.Size = new System.Drawing.Size(233, 29);
            this.btnChangeColor.TabIndex = 14;
            this.btnChangeColor.Text = "Change";
            this.btnChangeColor.UseVisualStyleBackColor = true;
            this.btnChangeColor.Click += new System.EventHandler(this.btnChangeColor_Click);
            // 
            // textBoxColorFrom
            // 
            this.textBoxColorFrom.Location = new System.Drawing.Point(199, 11);
            this.textBoxColorFrom.Name = "textBoxColorFrom";
            this.textBoxColorFrom.ReadOnly = true;
            this.textBoxColorFrom.Size = new System.Drawing.Size(233, 27);
            this.textBoxColorFrom.TabIndex = 12;
            // 
            // listViewColor
            // 
            this.listViewColor.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderColor,
            this.columnHeaderCounter});
            this.listViewColor.FullRowSelect = true;
            this.listViewColor.GridLines = true;
            this.listViewColor.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listViewColor.HideSelection = false;
            this.listViewColor.LabelWrap = false;
            this.listViewColor.Location = new System.Drawing.Point(-1, -1);
            this.listViewColor.MultiSelect = false;
            this.listViewColor.Name = "listViewColor";
            this.listViewColor.Size = new System.Drawing.Size(194, 189);
            this.listViewColor.TabIndex = 11;
            this.listViewColor.UseCompatibleStateImageBehavior = false;
            this.listViewColor.View = System.Windows.Forms.View.Details;
            this.listViewColor.SelectedIndexChanged += new System.EventHandler(this.listViewColor_SelectedIndexChanged);
            // 
            // columnHeaderColor
            // 
            this.columnHeaderColor.Name = "columnHeaderColor";
            this.columnHeaderColor.Text = "Color";
            this.columnHeaderColor.Width = 100;
            // 
            // columnHeaderCounter
            // 
            this.columnHeaderCounter.Name = "columnHeaderCounter";
            this.columnHeaderCounter.Text = "Counter";
            this.columnHeaderCounter.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // pictureBox
            // 
            this.pictureBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox.Location = new System.Drawing.Point(180, 0);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(686, 287);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox.TabIndex = 1;
            this.pictureBox.TabStop = false;
            // 
            // openFileDlg
            // 
            this.openFileDlg.FileName = "openFileDialog1";
            this.openFileDlg.Filter = "All files|*.*;";
            // 
            // colorDialog
            // 
            this.colorDialog.AnyColor = true;
            this.colorDialog.FullOpen = true;
            // 
            // textBoxForeColor
            // 
            this.textBoxForeColor.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxForeColor.Location = new System.Drawing.Point(92, 354);
            this.textBoxForeColor.Name = "textBoxForeColor";
            this.textBoxForeColor.Size = new System.Drawing.Size(78, 27);
            this.textBoxForeColor.TabIndex = 16;
            this.textBoxForeColor.Text = "FFFFFFFF";
            // 
            // labelForeColor
            // 
            labelForeColor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            labelForeColor.AutoSize = true;
            labelForeColor.Location = new System.Drawing.Point(10, 354);
            labelForeColor.Name = "labelForeColor";
            labelForeColor.Size = new System.Drawing.Size(74, 20);
            labelForeColor.TabIndex = 17;
            labelForeColor.Text = "ForeColor";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(866, 476);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.panelTool);
            this.Controls.Add(panelAction);
            this.Name = "MainForm";
            this.Text = "Image Convertor";
            panelAction.ResumeLayout(false);
            panelAction.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericPosY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericPosX)).EndInit();
            this.panelTool.ResumeLayout(false);
            this.panelTool.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericToB)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericToG)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericToR)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericToA)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelAction;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnLoad;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.OpenFileDialog openFileDlg;
        private System.Windows.Forms.Button btnScan;
        private System.Windows.Forms.TextBox textBoxHeight;
        private System.Windows.Forms.TextBox textBoxWidth;
        private System.Windows.Forms.Panel panelTool;
        private System.Windows.Forms.Button btnChangeColor;
        private System.Windows.Forms.TextBox textBoxColorFrom;
        private System.Windows.Forms.ListView listViewColor;
        private System.Windows.Forms.ColumnHeader columnHeaderColor;
        private System.Windows.Forms.ColumnHeader columnHeaderCounter;
        private System.Windows.Forms.NumericUpDown numericToB;
        private System.Windows.Forms.NumericUpDown numericToG;
        private System.Windows.Forms.NumericUpDown numericToR;
        private System.Windows.Forms.NumericUpDown numericToA;
        private System.Windows.Forms.ColorDialog colorDialog;
        private System.Windows.Forms.Button btnSave565;
        private System.Windows.Forms.CheckBox checkBoxSwap;
        private System.Windows.Forms.NumericUpDown numericPosY;
        private System.Windows.Forms.NumericUpDown numericPosX;
        private System.Windows.Forms.TextBox textBoxBackColor;
        private System.Windows.Forms.TextBox textBoxForeColor;
    }
}

