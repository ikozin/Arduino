
namespace YandexWeather
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
            System.Windows.Forms.GroupBox groupBoxPng;
            System.Windows.Forms.Button btnPng;
            System.Windows.Forms.GroupBox groupBoxApi;
            System.Windows.Forms.Button btnApiLoad;
            System.Windows.Forms.GroupBox groupBoxSvg;
            System.Windows.Forms.Button btnSvg;
            this.comboBoxPngUrl = new System.Windows.Forms.ComboBox();
            this.comboBoxApiKey = new System.Windows.Forms.ComboBox();
            this.comboBoxApiUrl = new System.Windows.Forms.ComboBox();
            this.labelBackColor = new System.Windows.Forms.Label();
            this.labelSize = new System.Windows.Forms.Label();
            this.numericUpDownSvgSize = new System.Windows.Forms.NumericUpDown();
            this.textBoxSvgColor = new System.Windows.Forms.TextBox();
            this.comboBoxSvgUrl = new System.Windows.Forms.ComboBox();
            this.textBoxLog = new System.Windows.Forms.TextBox();
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            groupBoxPng = new System.Windows.Forms.GroupBox();
            btnPng = new System.Windows.Forms.Button();
            groupBoxApi = new System.Windows.Forms.GroupBox();
            btnApiLoad = new System.Windows.Forms.Button();
            groupBoxSvg = new System.Windows.Forms.GroupBox();
            btnSvg = new System.Windows.Forms.Button();
            groupBoxPng.SuspendLayout();
            groupBoxApi.SuspendLayout();
            groupBoxSvg.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSvgSize)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxPng
            // 
            groupBoxPng.Controls.Add(btnPng);
            groupBoxPng.Controls.Add(this.comboBoxPngUrl);
            groupBoxPng.Dock = System.Windows.Forms.DockStyle.Top;
            groupBoxPng.Location = new System.Drawing.Point(0, 0);
            groupBoxPng.Name = "groupBoxPng";
            groupBoxPng.Size = new System.Drawing.Size(800, 68);
            groupBoxPng.TabIndex = 0;
            groupBoxPng.TabStop = false;
            groupBoxPng.Text = "PNG download";
            // 
            // btnPng
            // 
            btnPng.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            btnPng.Location = new System.Drawing.Point(700, 26);
            btnPng.Name = "btnPng";
            btnPng.Size = new System.Drawing.Size(94, 29);
            btnPng.TabIndex = 1;
            btnPng.Text = "Load";
            btnPng.UseVisualStyleBackColor = true;
            btnPng.Click += new System.EventHandler(this.btnPng_Click);
            // 
            // comboBoxPngUrl
            // 
            this.comboBoxPngUrl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxPngUrl.FormattingEnabled = true;
            this.comboBoxPngUrl.Items.AddRange(new object[] {
            "https://yastatic.net/weather/i/icons/blueye/48/*.png",
            "https://yastatic.net/weather/i/icons/blueye/64/*.png",
            "",
            "https://yastatic.net/weather/i/icons/funky/png/black/48/*.png",
            "https://yastatic.net/weather/i/icons/funky/png/dark/48/*.png",
            "https://yastatic.net/weather/i/icons/funky/png/flat/48/*.png",
            "https://yastatic.net/weather/i/icons/funky/png/light/48/*.png",
            "",
            "https://yastatic.net/weather/i/icons/funky/png/black/64/*.png",
            "https://yastatic.net/weather/i/icons/funky/png/dark/64/*.png",
            "https://yastatic.net/weather/i/icons/funky/png/flat/64/*.png",
            "https://yastatic.net/weather/i/icons/funky/png/light/64/*.png"});
            this.comboBoxPngUrl.Location = new System.Drawing.Point(6, 26);
            this.comboBoxPngUrl.Name = "comboBoxPngUrl";
            this.comboBoxPngUrl.Size = new System.Drawing.Size(683, 28);
            this.comboBoxPngUrl.TabIndex = 0;
            // 
            // groupBoxApi
            // 
            groupBoxApi.Controls.Add(btnApiLoad);
            groupBoxApi.Controls.Add(this.comboBoxApiKey);
            groupBoxApi.Controls.Add(this.comboBoxApiUrl);
            groupBoxApi.Dock = System.Windows.Forms.DockStyle.Top;
            groupBoxApi.Location = new System.Drawing.Point(0, 174);
            groupBoxApi.Name = "groupBoxApi";
            groupBoxApi.Size = new System.Drawing.Size(800, 94);
            groupBoxApi.TabIndex = 2;
            groupBoxApi.TabStop = false;
            groupBoxApi.Text = "API";
            // 
            // btnApiLoad
            // 
            btnApiLoad.Location = new System.Drawing.Point(700, 26);
            btnApiLoad.Name = "btnApiLoad";
            btnApiLoad.Size = new System.Drawing.Size(94, 62);
            btnApiLoad.TabIndex = 2;
            btnApiLoad.Text = "Load";
            btnApiLoad.UseVisualStyleBackColor = true;
            btnApiLoad.Click += new System.EventHandler(this.btnApiLoad_Click);
            // 
            // comboBoxApiKey
            // 
            this.comboBoxApiKey.FormattingEnabled = true;
            this.comboBoxApiKey.Items.AddRange(new object[] {
            "ce09edeb-132e-40d6-a0ae-1c1026b2466e"});
            this.comboBoxApiKey.Location = new System.Drawing.Point(6, 60);
            this.comboBoxApiKey.Name = "comboBoxApiKey";
            this.comboBoxApiKey.Size = new System.Drawing.Size(683, 28);
            this.comboBoxApiKey.TabIndex = 1;
            // 
            // comboBoxApiUrl
            // 
            this.comboBoxApiUrl.FormattingEnabled = true;
            this.comboBoxApiUrl.Items.AddRange(new object[] {
            "https://api.weather.yandex.ru/v2/forecast?lat=55.783483&lon=37.473015&limit=2&hou" +
                "rs=false",
            "https://api.weather.yandex.ru/v1/forecast?lat=55.783483&lon=37.473015&limit=2"});
            this.comboBoxApiUrl.Location = new System.Drawing.Point(6, 26);
            this.comboBoxApiUrl.Name = "comboBoxApiUrl";
            this.comboBoxApiUrl.Size = new System.Drawing.Size(683, 28);
            this.comboBoxApiUrl.TabIndex = 0;
            // 
            // groupBoxSvg
            // 
            groupBoxSvg.Controls.Add(this.labelBackColor);
            groupBoxSvg.Controls.Add(this.labelSize);
            groupBoxSvg.Controls.Add(this.numericUpDownSvgSize);
            groupBoxSvg.Controls.Add(this.textBoxSvgColor);
            groupBoxSvg.Controls.Add(btnSvg);
            groupBoxSvg.Controls.Add(this.comboBoxSvgUrl);
            groupBoxSvg.Dock = System.Windows.Forms.DockStyle.Top;
            groupBoxSvg.Location = new System.Drawing.Point(0, 68);
            groupBoxSvg.Name = "groupBoxSvg";
            groupBoxSvg.Size = new System.Drawing.Size(800, 106);
            groupBoxSvg.TabIndex = 3;
            groupBoxSvg.TabStop = false;
            groupBoxSvg.Text = "SVG download";
            // 
            // labelBackColor
            // 
            this.labelBackColor.AutoSize = true;
            this.labelBackColor.Location = new System.Drawing.Point(12, 63);
            this.labelBackColor.Name = "labelBackColor";
            this.labelBackColor.Size = new System.Drawing.Size(82, 20);
            this.labelBackColor.TabIndex = 5;
            this.labelBackColor.Text = "Цвет фона";
            // 
            // labelSize
            // 
            this.labelSize.AutoSize = true;
            this.labelSize.Location = new System.Drawing.Point(239, 62);
            this.labelSize.Name = "labelSize";
            this.labelSize.Size = new System.Drawing.Size(60, 20);
            this.labelSize.TabIndex = 4;
            this.labelSize.Text = "Размер";
            // 
            // numericUpDownSvgSize
            // 
            this.numericUpDownSvgSize.Location = new System.Drawing.Point(305, 60);
            this.numericUpDownSvgSize.Maximum = new decimal(new int[] {
            240,
            0,
            0,
            0});
            this.numericUpDownSvgSize.Name = "numericUpDownSvgSize";
            this.numericUpDownSvgSize.Size = new System.Drawing.Size(121, 27);
            this.numericUpDownSvgSize.TabIndex = 3;
            this.numericUpDownSvgSize.Value = new decimal(new int[] {
            64,
            0,
            0,
            0});
            // 
            // textBoxSvgColor
            // 
            this.textBoxSvgColor.Location = new System.Drawing.Point(100, 59);
            this.textBoxSvgColor.Name = "textBoxSvgColor";
            this.textBoxSvgColor.Size = new System.Drawing.Size(125, 27);
            this.textBoxSvgColor.TabIndex = 2;
            this.textBoxSvgColor.Text = "#4D8DEE";
            this.textBoxSvgColor.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.textBoxSvgColor_MouseDoubleClick);
            // 
            // btnSvg
            // 
            btnSvg.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            btnSvg.Location = new System.Drawing.Point(700, 26);
            btnSvg.Name = "btnSvg";
            btnSvg.Size = new System.Drawing.Size(94, 29);
            btnSvg.TabIndex = 1;
            btnSvg.Text = "Load";
            btnSvg.UseVisualStyleBackColor = true;
            btnSvg.Click += new System.EventHandler(this.btnSvg_Click);
            // 
            // comboBoxSvgUrl
            // 
            this.comboBoxSvgUrl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBoxSvgUrl.FormattingEnabled = true;
            this.comboBoxSvgUrl.Items.AddRange(new object[] {
            "https://yastatic.net/weather/i/icons/svg/*.svg",
            "",
            "https://yastatic.net/weather/i/icons/funky/black/*.svg",
            "https://yastatic.net/weather/i/icons/funky/light/*.svg",
            "https://yastatic.net/weather/i/icons/funky/dark/*.svg",
            "",
            "https://yastatic.net/weather/i/icons/blueye/black/svg/*.svg",
            "https://yastatic.net/weather/i/icons/blueye/color/svg/*.svg"});
            this.comboBoxSvgUrl.Location = new System.Drawing.Point(6, 26);
            this.comboBoxSvgUrl.Name = "comboBoxSvgUrl";
            this.comboBoxSvgUrl.Size = new System.Drawing.Size(682, 28);
            this.comboBoxSvgUrl.TabIndex = 0;
            // 
            // textBoxLog
            // 
            this.textBoxLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBoxLog.Location = new System.Drawing.Point(0, 268);
            this.textBoxLog.Multiline = true;
            this.textBoxLog.Name = "textBoxLog";
            this.textBoxLog.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxLog.Size = new System.Drawing.Size(800, 391);
            this.textBoxLog.TabIndex = 1;
            this.textBoxLog.WordWrap = false;
            // 
            // colorDialog
            // 
            this.colorDialog.AnyColor = true;
            this.colorDialog.FullOpen = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 659);
            this.Controls.Add(this.textBoxLog);
            this.Controls.Add(groupBoxApi);
            this.Controls.Add(groupBoxSvg);
            this.Controls.Add(groupBoxPng);
            this.Name = "MainForm";
            this.Text = "Yandex Weather";
            groupBoxPng.ResumeLayout(false);
            groupBoxApi.ResumeLayout(false);
            groupBoxSvg.ResumeLayout(false);
            groupBoxSvg.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSvgSize)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxPngUrl;
        private System.Windows.Forms.TextBox textBoxLog;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
        private System.Windows.Forms.ComboBox comboBoxApiKey;
        private System.Windows.Forms.ComboBox comboBoxApiUrl;
        private System.Windows.Forms.ComboBox comboBoxSvgUrl;
        private System.Windows.Forms.NumericUpDown numericUpDownSvgSize;
        private System.Windows.Forms.TextBox textBoxSvgColor;
        private System.Windows.Forms.ColorDialog colorDialog;
        private System.Windows.Forms.Label labelSize;
        private System.Windows.Forms.Label labelBackColor;
    }
}

