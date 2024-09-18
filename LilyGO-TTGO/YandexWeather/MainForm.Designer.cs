
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
            comboBoxPngUrl = new System.Windows.Forms.ComboBox();
            comboBoxApiKey = new System.Windows.Forms.ComboBox();
            comboBoxApiUrl = new System.Windows.Forms.ComboBox();
            labelBackColor = new System.Windows.Forms.Label();
            labelSize = new System.Windows.Forms.Label();
            numericUpDownSvgSize = new System.Windows.Forms.NumericUpDown();
            textBoxSvgColor = new System.Windows.Forms.TextBox();
            comboBoxSvgUrl = new System.Windows.Forms.ComboBox();
            textBoxLog = new System.Windows.Forms.TextBox();
            folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            colorDialog = new System.Windows.Forms.ColorDialog();
            groupBoxPng = new System.Windows.Forms.GroupBox();
            btnPng = new System.Windows.Forms.Button();
            groupBoxApi = new System.Windows.Forms.GroupBox();
            btnApiLoad = new System.Windows.Forms.Button();
            groupBoxSvg = new System.Windows.Forms.GroupBox();
            btnSvg = new System.Windows.Forms.Button();
            groupBoxPng.SuspendLayout();
            groupBoxApi.SuspendLayout();
            groupBoxSvg.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDownSvgSize).BeginInit();
            SuspendLayout();
            // 
            // groupBoxPng
            // 
            groupBoxPng.Controls.Add(btnPng);
            groupBoxPng.Controls.Add(comboBoxPngUrl);
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
            btnPng.Anchor = System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right;
            btnPng.Location = new System.Drawing.Point(700, 26);
            btnPng.Name = "btnPng";
            btnPng.Size = new System.Drawing.Size(94, 29);
            btnPng.TabIndex = 1;
            btnPng.Text = "Load";
            btnPng.UseVisualStyleBackColor = true;
            btnPng.Click += btnPng_Click;
            // 
            // comboBoxPngUrl
            // 
            comboBoxPngUrl.Anchor = System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right;
            comboBoxPngUrl.FormattingEnabled = true;
            comboBoxPngUrl.Items.AddRange(new object[] { "https://yastatic.net/weather/i/icons/funky/png/light/64/*.png", "https://yastatic.net/weather/i/icons/funky/png/dark/64/*.png", "https://yastatic.net/weather/i/icons/funky/png/circle/64/*.png", "https://yastatic.net/weather/i/icons/funky/png/flat/64/*.png", "https://yastatic.net/weather/i/icons/funky/png/light/96/*.png", "https://yastatic.net/weather/i/icons/funky/png/dark/96/*.png", "https://yastatic.net/weather/i/icons/funky/png/circle/96/*.png", "https://yastatic.net/weather/i/icons/funky/png/flat/96/*.png" });
            comboBoxPngUrl.Location = new System.Drawing.Point(6, 26);
            comboBoxPngUrl.Name = "comboBoxPngUrl";
            comboBoxPngUrl.Size = new System.Drawing.Size(683, 28);
            comboBoxPngUrl.TabIndex = 0;
            // 
            // groupBoxApi
            // 
            groupBoxApi.Controls.Add(btnApiLoad);
            groupBoxApi.Controls.Add(comboBoxApiKey);
            groupBoxApi.Controls.Add(comboBoxApiUrl);
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
            btnApiLoad.Click += btnApiLoad_Click;
            // 
            // comboBoxApiKey
            // 
            comboBoxApiKey.FormattingEnabled = true;
            comboBoxApiKey.Items.AddRange(new object[] { "837f22c6-d139-4aa2-8579-e3712309b744" });
            comboBoxApiKey.Location = new System.Drawing.Point(6, 60);
            comboBoxApiKey.Name = "comboBoxApiKey";
            comboBoxApiKey.Size = new System.Drawing.Size(683, 28);
            comboBoxApiKey.TabIndex = 1;
            // 
            // comboBoxApiUrl
            // 
            comboBoxApiUrl.FormattingEnabled = true;
            comboBoxApiUrl.Items.AddRange(new object[] { "https://api.weather.yandex.ru/v2/forecast?lat=55.783230&lon=37.473060", "https://api.weather.yandex.ru/v2/forecast?lat=55.783230&lon=37.473060&lang=ru_RU&limit=1" });
            comboBoxApiUrl.Location = new System.Drawing.Point(6, 26);
            comboBoxApiUrl.Name = "comboBoxApiUrl";
            comboBoxApiUrl.Size = new System.Drawing.Size(683, 28);
            comboBoxApiUrl.TabIndex = 0;
            // 
            // groupBoxSvg
            // 
            groupBoxSvg.Controls.Add(labelBackColor);
            groupBoxSvg.Controls.Add(labelSize);
            groupBoxSvg.Controls.Add(numericUpDownSvgSize);
            groupBoxSvg.Controls.Add(textBoxSvgColor);
            groupBoxSvg.Controls.Add(btnSvg);
            groupBoxSvg.Controls.Add(comboBoxSvgUrl);
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
            labelBackColor.AutoSize = true;
            labelBackColor.Location = new System.Drawing.Point(12, 63);
            labelBackColor.Name = "labelBackColor";
            labelBackColor.Size = new System.Drawing.Size(82, 20);
            labelBackColor.TabIndex = 5;
            labelBackColor.Text = "Цвет фона";
            // 
            // labelSize
            // 
            labelSize.AutoSize = true;
            labelSize.Location = new System.Drawing.Point(239, 62);
            labelSize.Name = "labelSize";
            labelSize.Size = new System.Drawing.Size(60, 20);
            labelSize.TabIndex = 4;
            labelSize.Text = "Размер";
            // 
            // numericUpDownSvgSize
            // 
            numericUpDownSvgSize.Location = new System.Drawing.Point(305, 60);
            numericUpDownSvgSize.Maximum = new decimal(new int[] { 240, 0, 0, 0 });
            numericUpDownSvgSize.Name = "numericUpDownSvgSize";
            numericUpDownSvgSize.Size = new System.Drawing.Size(121, 27);
            numericUpDownSvgSize.TabIndex = 3;
            numericUpDownSvgSize.Value = new decimal(new int[] { 64, 0, 0, 0 });
            // 
            // textBoxSvgColor
            // 
            textBoxSvgColor.Location = new System.Drawing.Point(100, 59);
            textBoxSvgColor.Name = "textBoxSvgColor";
            textBoxSvgColor.Size = new System.Drawing.Size(125, 27);
            textBoxSvgColor.TabIndex = 2;
            textBoxSvgColor.Text = "#4D8DEE";
            textBoxSvgColor.MouseDoubleClick += textBoxSvgColor_MouseDoubleClick;
            // 
            // btnSvg
            // 
            btnSvg.Anchor = System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right;
            btnSvg.Location = new System.Drawing.Point(700, 26);
            btnSvg.Name = "btnSvg";
            btnSvg.Size = new System.Drawing.Size(94, 29);
            btnSvg.TabIndex = 1;
            btnSvg.Text = "Load";
            btnSvg.UseVisualStyleBackColor = true;
            btnSvg.Click += btnSvg_Click;
            // 
            // comboBoxSvgUrl
            // 
            comboBoxSvgUrl.Anchor = System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right;
            comboBoxSvgUrl.FormattingEnabled = true;
            comboBoxSvgUrl.Items.AddRange(new object[] { "https://yastatic.net/weather/i/icons/funky/light/*.svg", "https://yastatic.net/weather/i/icons/funky/dark/*.svg", "https://yastatic.net/weather/i/icons/funky/circle/*.svg", "https://yastatic.net/weather/i/icons/funky/flat/*.svg" });
            comboBoxSvgUrl.Location = new System.Drawing.Point(6, 26);
            comboBoxSvgUrl.Name = "comboBoxSvgUrl";
            comboBoxSvgUrl.Size = new System.Drawing.Size(682, 28);
            comboBoxSvgUrl.TabIndex = 0;
            // 
            // textBoxLog
            // 
            textBoxLog.Dock = System.Windows.Forms.DockStyle.Fill;
            textBoxLog.Location = new System.Drawing.Point(0, 268);
            textBoxLog.Multiline = true;
            textBoxLog.Name = "textBoxLog";
            textBoxLog.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            textBoxLog.Size = new System.Drawing.Size(800, 391);
            textBoxLog.TabIndex = 1;
            textBoxLog.WordWrap = false;
            // 
            // colorDialog
            // 
            colorDialog.AnyColor = true;
            colorDialog.FullOpen = true;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            ClientSize = new System.Drawing.Size(800, 659);
            Controls.Add(textBoxLog);
            Controls.Add(groupBoxApi);
            Controls.Add(groupBoxSvg);
            Controls.Add(groupBoxPng);
            Name = "MainForm";
            Text = "Yandex Weather";
            groupBoxPng.ResumeLayout(false);
            groupBoxApi.ResumeLayout(false);
            groupBoxSvg.ResumeLayout(false);
            groupBoxSvg.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)numericUpDownSvgSize).EndInit();
            ResumeLayout(false);
            PerformLayout();
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

