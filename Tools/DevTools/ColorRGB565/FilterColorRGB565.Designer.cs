namespace ColorRGB565
{
    partial class FilterColorRGB565
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            Label labelHeigth;
            Label labelWidth;
            Panel panelLocation;
            Label labelNameY;
            Label labelNameX;
            Label labelColorHtml;
            GroupBox groupBoxColor;
            Button btnColor;
            Label labelColorHex;
            labelY = new Label();
            labelX = new Label();
            groupBoxLessColor = new GroupBox();
            btnLessColor = new Button();
            comboBoxLessColor = new ComboBox();
            labelB = new Label();
            labelG = new Label();
            labelR = new Label();
            listViewColors = new ListView();
            columnHeaderColor = new ColumnHeader();
            columnHeaderCount = new ColumnHeader();
            columnHeaderRed = new ColumnHeader();
            columnHeaderGreen = new ColumnHeader();
            columnHeaderBlue = new ColumnHeader();
            contextMenuStrip = new ContextMenuStrip(components);
            replaceToolStripMenuItem = new ToolStripMenuItem();
            btnAnalysis = new Button();
            textBoxColorHex = new TextBox();
            textBoxColorHtml = new TextBox();
            textBoxHeight = new TextBox();
            textBoxWidth = new TextBox();
            colorDialog = new ColorDialog();
            labelHeigth = new Label();
            labelWidth = new Label();
            panelLocation = new Panel();
            labelNameY = new Label();
            labelNameX = new Label();
            labelColorHtml = new Label();
            groupBoxColor = new GroupBox();
            btnColor = new Button();
            labelColorHex = new Label();
            panelLocation.SuspendLayout();
            groupBoxColor.SuspendLayout();
            groupBoxLessColor.SuspendLayout();
            contextMenuStrip.SuspendLayout();
            SuspendLayout();
            // 
            // labelHeigth
            // 
            labelHeigth.AutoSize = true;
            labelHeigth.Location = new Point(127, 6);
            labelHeigth.Name = "labelHeigth";
            labelHeigth.Size = new Size(59, 20);
            labelHeigth.TabIndex = 10;
            labelHeigth.Text = "Высота";
            // 
            // labelWidth
            // 
            labelWidth.AutoSize = true;
            labelWidth.Location = new Point(2, 6);
            labelWidth.Name = "labelWidth";
            labelWidth.Size = new Size(67, 20);
            labelWidth.TabIndex = 8;
            labelWidth.Text = "Ширина";
            // 
            // panelLocation
            // 
            panelLocation.BorderStyle = BorderStyle.Fixed3D;
            panelLocation.Controls.Add(labelY);
            panelLocation.Controls.Add(labelNameY);
            panelLocation.Controls.Add(labelX);
            panelLocation.Controls.Add(labelNameX);
            panelLocation.Dock = DockStyle.Bottom;
            panelLocation.Location = new Point(0, 374);
            panelLocation.Name = "panelLocation";
            panelLocation.Size = new Size(387, 23);
            panelLocation.TabIndex = 12;
            // 
            // labelY
            // 
            labelY.AutoSize = true;
            labelY.Location = new Point(75, 0);
            labelY.Name = "labelY";
            labelY.Size = new Size(33, 20);
            labelY.TabIndex = 3;
            labelY.Text = "YYY";
            // 
            // labelNameY
            // 
            labelNameY.AutoSize = true;
            labelNameY.Location = new Point(61, 0);
            labelNameY.Name = "labelNameY";
            labelNameY.Size = new Size(20, 20);
            labelNameY.TabIndex = 2;
            labelNameY.Text = "Y:";
            // 
            // labelX
            // 
            labelX.AutoSize = true;
            labelX.Location = new Point(19, 0);
            labelX.Name = "labelX";
            labelX.Size = new Size(36, 20);
            labelX.TabIndex = 1;
            labelX.Text = "XXX";
            // 
            // labelNameX
            // 
            labelNameX.AutoSize = true;
            labelNameX.Location = new Point(2, 0);
            labelNameX.Name = "labelNameX";
            labelNameX.Size = new Size(21, 20);
            labelNameX.TabIndex = 0;
            labelNameX.Text = "X:";
            // 
            // labelColorHtml
            // 
            labelColorHtml.AutoSize = true;
            labelColorHtml.Location = new Point(6, 29);
            labelColorHtml.Name = "labelColorHtml";
            labelColorHtml.Size = new Size(48, 20);
            labelColorHtml.TabIndex = 13;
            labelColorHtml.Text = "HTML";
            // 
            // groupBoxColor
            // 
            groupBoxColor.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            groupBoxColor.Controls.Add(groupBoxLessColor);
            groupBoxColor.Controls.Add(labelB);
            groupBoxColor.Controls.Add(labelG);
            groupBoxColor.Controls.Add(labelR);
            groupBoxColor.Controls.Add(listViewColors);
            groupBoxColor.Controls.Add(btnAnalysis);
            groupBoxColor.Controls.Add(btnColor);
            groupBoxColor.Controls.Add(textBoxColorHex);
            groupBoxColor.Controls.Add(labelColorHex);
            groupBoxColor.Controls.Add(textBoxColorHtml);
            groupBoxColor.Controls.Add(labelColorHtml);
            groupBoxColor.Location = new Point(3, 36);
            groupBoxColor.Name = "groupBoxColor";
            groupBoxColor.Size = new Size(379, 337);
            groupBoxColor.TabIndex = 15;
            groupBoxColor.TabStop = false;
            groupBoxColor.Text = "Цвет";
            // 
            // groupBoxLessColor
            // 
            groupBoxLessColor.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            groupBoxLessColor.Controls.Add(btnLessColor);
            groupBoxLessColor.Controls.Add(comboBoxLessColor);
            groupBoxLessColor.Location = new Point(189, 16);
            groupBoxLessColor.Name = "groupBoxLessColor";
            groupBoxLessColor.Size = new Size(184, 93);
            groupBoxLessColor.TabIndex = 23;
            groupBoxLessColor.TabStop = false;
            groupBoxLessColor.Text = "Уменьшение цвета";
            // 
            // btnLessColor
            // 
            btnLessColor.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            btnLessColor.Enabled = false;
            btnLessColor.Location = new Point(6, 58);
            btnLessColor.Name = "btnLessColor";
            btnLessColor.Size = new Size(172, 29);
            btnLessColor.TabIndex = 1;
            btnLessColor.Text = "Уменьшить";
            btnLessColor.UseVisualStyleBackColor = true;
            btnLessColor.Click += btnLessColor_Click;
            // 
            // comboBoxLessColor
            // 
            comboBoxLessColor.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            comboBoxLessColor.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBoxLessColor.FormattingEnabled = true;
            comboBoxLessColor.Items.AddRange(new object[] { "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%" });
            comboBoxLessColor.Location = new Point(6, 26);
            comboBoxLessColor.Name = "comboBoxLessColor";
            comboBoxLessColor.Size = new Size(172, 28);
            comboBoxLessColor.TabIndex = 0;
            // 
            // labelB
            // 
            labelB.AutoSize = true;
            labelB.Font = new Font("Segoe UI", 9F, FontStyle.Bold);
            labelB.ForeColor = Color.Blue;
            labelB.Location = new Point(165, 89);
            labelB.Name = "labelB";
            labelB.Size = new Size(18, 20);
            labelB.TabIndex = 22;
            labelB.Text = "0";
            labelB.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelG
            // 
            labelG.AutoSize = true;
            labelG.Font = new Font("Segoe UI", 9F, FontStyle.Bold);
            labelG.ForeColor = Color.Green;
            labelG.Location = new Point(124, 89);
            labelG.Name = "labelG";
            labelG.Size = new Size(18, 20);
            labelG.TabIndex = 21;
            labelG.Text = "0";
            labelG.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // labelR
            // 
            labelR.AutoSize = true;
            labelR.Font = new Font("Segoe UI", 9F, FontStyle.Bold);
            labelR.ForeColor = Color.Red;
            labelR.Location = new Point(87, 89);
            labelR.Name = "labelR";
            labelR.Size = new Size(18, 20);
            labelR.TabIndex = 20;
            labelR.Text = "0";
            labelR.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // listViewColors
            // 
            listViewColors.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            listViewColors.Columns.AddRange(new ColumnHeader[] { columnHeaderColor, columnHeaderCount, columnHeaderRed, columnHeaderGreen, columnHeaderBlue });
            listViewColors.ContextMenuStrip = contextMenuStrip;
            listViewColors.Enabled = false;
            listViewColors.FullRowSelect = true;
            listViewColors.LabelWrap = false;
            listViewColors.Location = new Point(12, 182);
            listViewColors.Name = "listViewColors";
            listViewColors.ShowGroups = false;
            listViewColors.Size = new Size(361, 149);
            listViewColors.Sorting = SortOrder.Ascending;
            listViewColors.TabIndex = 19;
            listViewColors.UseCompatibleStateImageBehavior = false;
            listViewColors.View = View.Details;
            listViewColors.ColumnClick += listViewColors_ColumnClick;
            listViewColors.DoubleClick += listViewColors_DoubleClick;
            // 
            // columnHeaderColor
            // 
            columnHeaderColor.Text = "Цвет";
            columnHeaderColor.Width = 128;
            // 
            // columnHeaderCount
            // 
            columnHeaderCount.Text = "Кол-во";
            columnHeaderCount.Width = 64;
            // 
            // columnHeaderRed
            // 
            columnHeaderRed.Text = "R";
            columnHeaderRed.Width = 48;
            // 
            // columnHeaderGreen
            // 
            columnHeaderGreen.Text = "G";
            columnHeaderGreen.Width = 48;
            // 
            // columnHeaderBlue
            // 
            columnHeaderBlue.Text = "B";
            columnHeaderBlue.Width = 48;
            // 
            // contextMenuStrip
            // 
            contextMenuStrip.ImageScalingSize = new Size(20, 20);
            contextMenuStrip.Items.AddRange(new ToolStripItem[] { replaceToolStripMenuItem });
            contextMenuStrip.Name = "contextMenuStrip";
            contextMenuStrip.Size = new Size(251, 28);
            // 
            // replaceToolStripMenuItem
            // 
            replaceToolStripMenuItem.Name = "replaceToolStripMenuItem";
            replaceToolStripMenuItem.Size = new Size(250, 24);
            replaceToolStripMenuItem.Text = "Заменить на HTML(цвет)";
            replaceToolStripMenuItem.Click += replaceToolStripMenuItem_Click;
            // 
            // btnAnalysis
            // 
            btnAnalysis.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            btnAnalysis.Enabled = false;
            btnAnalysis.Location = new Point(12, 147);
            btnAnalysis.Name = "btnAnalysis";
            btnAnalysis.Size = new Size(361, 29);
            btnAnalysis.TabIndex = 18;
            btnAnalysis.Text = "Анализ";
            btnAnalysis.UseVisualStyleBackColor = true;
            btnAnalysis.Click += btnAnalysis_Click;
            // 
            // btnColor
            // 
            btnColor.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            btnColor.Location = new Point(12, 112);
            btnColor.Name = "btnColor";
            btnColor.Size = new Size(361, 29);
            btnColor.TabIndex = 17;
            btnColor.Text = "Выбор цвета";
            btnColor.UseVisualStyleBackColor = true;
            btnColor.Click += btnColor_Click;
            // 
            // textBoxColorHex
            // 
            textBoxColorHex.Location = new Point(87, 59);
            textBoxColorHex.Name = "textBoxColorHex";
            textBoxColorHex.ReadOnly = true;
            textBoxColorHex.Size = new Size(96, 27);
            textBoxColorHex.TabIndex = 16;
            textBoxColorHex.WordWrap = false;
            // 
            // labelColorHex
            // 
            labelColorHex.AutoSize = true;
            labelColorHex.Location = new Point(6, 62);
            labelColorHex.Name = "labelColorHex";
            labelColorHex.Size = new Size(75, 20);
            labelColorHex.TabIndex = 15;
            labelColorHex.Text = "HEX (565)";
            // 
            // textBoxColorHtml
            // 
            textBoxColorHtml.Location = new Point(87, 26);
            textBoxColorHtml.Name = "textBoxColorHtml";
            textBoxColorHtml.ReadOnly = true;
            textBoxColorHtml.Size = new Size(96, 27);
            textBoxColorHtml.TabIndex = 14;
            textBoxColorHtml.WordWrap = false;
            // 
            // textBoxHeight
            // 
            textBoxHeight.Location = new Point(192, 3);
            textBoxHeight.Name = "textBoxHeight";
            textBoxHeight.ReadOnly = true;
            textBoxHeight.Size = new Size(42, 27);
            textBoxHeight.TabIndex = 11;
            textBoxHeight.Text = "0";
            textBoxHeight.WordWrap = false;
            // 
            // textBoxWidth
            // 
            textBoxWidth.Location = new Point(75, 3);
            textBoxWidth.Name = "textBoxWidth";
            textBoxWidth.ReadOnly = true;
            textBoxWidth.Size = new Size(47, 27);
            textBoxWidth.TabIndex = 9;
            textBoxWidth.Text = "0";
            textBoxWidth.WordWrap = false;
            // 
            // colorDialog
            // 
            colorDialog.AnyColor = true;
            colorDialog.FullOpen = true;
            // 
            // FilterColorRGB565
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(groupBoxColor);
            Controls.Add(panelLocation);
            Controls.Add(textBoxHeight);
            Controls.Add(labelHeigth);
            Controls.Add(textBoxWidth);
            Controls.Add(labelWidth);
            Name = "FilterColorRGB565";
            Size = new Size(387, 397);
            panelLocation.ResumeLayout(false);
            panelLocation.PerformLayout();
            groupBoxColor.ResumeLayout(false);
            groupBoxColor.PerformLayout();
            groupBoxLessColor.ResumeLayout(false);
            contextMenuStrip.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox textBoxHeight;
        private TextBox textBoxWidth;
        private Label labelX;
        private Label labelY;
        private TextBox textBoxColorHtml;
        private TextBox textBoxColorHex;
        private ColorDialog colorDialog;
        private Button btnAnalysis;
        private ListView listViewColors;
        private ColumnHeader columnHeaderColor;
        private ColumnHeader columnHeaderRed;
        private ColumnHeader columnHeaderGreen;
        private ColumnHeader columnHeaderBlue;
        private ColumnHeader columnHeaderCount;
        private ContextMenuStrip contextMenuStrip;
        private ToolStripMenuItem replaceToolStripMenuItem;
        private Label labelR4;
        private Label labelR3;
        private Label labelR2;
        private Label labelR1;
        private Label labelR;
        private Label labelG;
        private Label labelB;
        private GroupBox groupBoxLessColor;
        private Button btnLessColor;
        private ComboBox comboBoxLessColor;
    }
}
