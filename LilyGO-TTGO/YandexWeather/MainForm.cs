using Newtonsoft.Json;
using Svg;
using System;
using System.Drawing;
using System.IO;
using System.Net.Http;
using System.Windows.Forms;

namespace YandexWeather
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            comboBoxPngUrl.SelectedIndex = 0;
            comboBoxSvgUrl.SelectedIndex = 0;
            comboBoxApiUrl.SelectedIndex = 0;
            if (!String.IsNullOrEmpty(textBoxSvgColor.Text))
            {
                colorDialog.Color = ColorTranslator.FromHtml(textBoxSvgColor.Text);
            }
        }

        private void btnPng_Click(object sender, EventArgs e)
        {
            if (!CheckLoadParam(comboBoxPngUrl.Text))
                return;
            if (folderBrowserDialog.ShowDialog(this) != DialogResult.OK)
                return;

            ClearLog();

            (string url, string fileExt, string[] list) = GetLoadParam(comboBoxPngUrl.Text, ".png");

            WriteLog("Загрузка файлов PNG");
            using (HttpClient client = new())
            {
                foreach (var item in list)
                {
                    var fileName = Path.ChangeExtension(item, fileExt);
                    var link = new Uri(new Uri(url), fileName);
                    try
                    {
                        // client.DefaultRequestHeaders.Add("X-Yandex-Weather-Key", "837f22c6-d139-4aa2-8579-e3712309b744");
                        var data = client.GetByteArrayAsync(link).GetAwaiter().GetResult();
                        fileName = Path.Combine(folderBrowserDialog.SelectedPath, fileName);
                        File.WriteAllBytes(fileName, data);
                        WriteLog(String.Format("{0} - Загружен", link.AbsoluteUri));
                    }
                    catch (Exception ex)
                    {
                        WriteLog(String.Format("{0} - {1}", link.AbsoluteUri,  ex.Message));
                    }
                }
            }
            WriteLog("");
        }

        private void btnSvg_Click(object sender, EventArgs e)
        {
            Color? color = null;
            int? size = 0; 
            if (!CheckLoadParam(comboBoxSvgUrl.Text))
                return;
            if (folderBrowserDialog.ShowDialog(this) != DialogResult.OK)
                return;

            ClearLog();

            if (!String.IsNullOrEmpty(textBoxSvgColor.Text))
            {
                try
                {
                    color = ColorTranslator.FromHtml(textBoxSvgColor.Text);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(this, ex.Message, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
            if (numericUpDownSvgSize.Value > 0)
            {
                size = (int)numericUpDownSvgSize.Value;
            }
            //textBoxSvgColor.Text = ColorTranslator.ToHtml(colorDialog.Color);

            (string url, string fileExt, string[] list) = GetLoadParam(comboBoxSvgUrl.Text, ".svg");

            WriteLog("Загрузка файлов SVG");
            using (HttpClient client = new())
            {
                foreach (var item in list)
                {
                    var fileName = Path.ChangeExtension(item, fileExt);
                    var link = new Uri(new Uri(url), fileName);
                    try
                    {
                        var data = client.GetByteArrayAsync(link).GetAwaiter().GetResult();
                        fileName = Path.Combine(folderBrowserDialog.SelectedPath, fileName);
                        File.WriteAllBytes(fileName, data);
                        var filePng = Path.ChangeExtension(fileName, "png");
                        SaveSvgToPng(fileName, filePng, color, size, size);
                        WriteLog(String.Format("{0} - Загружен", link.AbsoluteUri));
                    }
                    catch (Exception ex)
                    {
                        WriteLog(String.Format("{0} - {1}", link.AbsoluteUri, ex.Message));
                    }
                }
            }
            WriteLog("");
        }

        private void ClearLog()
        {
            textBoxLog.Text = String.Empty;
        }

        private void WriteLog(string message)
        {
            textBoxLog.Text += message;
            textBoxLog.Text += Environment.NewLine;
        }

        private bool CheckLoadParam(string url)
        {
            if (String.IsNullOrEmpty(url))
            {
                MessageBox.Show(this, "Не выбран источник загрузки", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            if (!url.Contains("*.", StringComparison.CurrentCulture))
            {
                MessageBox.Show(this, "Неверный формат источника (*.png)", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            if (!File.Exists("imagelist.json"))
            {
                MessageBox.Show(this, "Файл с перечнем не найден: imagelist.json", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            return true;
        }

        private static (string url, string fileExt, string[] list) GetLoadParam(string param, string fileExt = null)
        {
            int index = param.IndexOf("*.");
            if (String.IsNullOrEmpty(fileExt)) fileExt = param[(index + 1)..];
            string url = (index > 0) ? param.Substring(0, index) : param;
            string lines = File.ReadAllText("imagelist.json");
            var list = JsonConvert.DeserializeObject<string[]>(lines);

            return (url, fileExt, list);
        }
        
        private void btnApiLoad_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(comboBoxApiUrl.Text))
            {
                MessageBox.Show(this, "Не выбран источник", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (String.IsNullOrEmpty(comboBoxApiKey.Text))
            {
                MessageBox.Show(this, "Не выбран ключ", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            try
            {
                ClearLog();

                using HttpClient client = new();
                client.DefaultRequestHeaders.Add("X-Yandex-Weather-Key", comboBoxApiKey.Text);
                var data = client.GetStringAsync(comboBoxApiUrl.Text).GetAwaiter().GetResult();
                var info = JsonConvert.DeserializeObject(data);
                WriteLog(JsonConvert.SerializeObject(info, Formatting.Indented));
            }
            catch (Exception ex)
            {
                WriteLog(ex.Message);
            }
            WriteLog("");
        }
        
        private static void SaveSvgToPng(string inputPath, string outputPath, Color? color, int? width, int? height)
        {
            var svgDocument = SvgDocument.Open(inputPath);
            if (width.HasValue) svgDocument.Width = width.Value;
            if (height.HasValue) svgDocument.Height = height.Value;

            using Bitmap bitmap = new((int)svgDocument.Width.Value, (int)svgDocument.Height.Value);
            using Graphics g = Graphics.FromImage(bitmap);
            if (color.HasValue) g.Clear(color.Value);
            svgDocument.Draw(bitmap);
            bitmap.Save(outputPath);
        }

        private void textBoxSvgColor_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (colorDialog.ShowDialog(this) != DialogResult.OK) return;
            textBoxSvgColor.Text = ColorTranslator.ToHtml(colorDialog.Color);
        }
    }
}
