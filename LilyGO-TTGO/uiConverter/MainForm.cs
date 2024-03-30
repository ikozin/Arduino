using System;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;


namespace uiConverter
{
    public partial class MainForm : Form
    {
        private const int MaxWidth = 240;
        private const int MaxHeigth = 135;

        private Bitmap _bitmap = null;
        public MainForm()
        {
            InitializeComponent();
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            if (openFileDlg.ShowDialog(this) != DialogResult.OK) return;
            if (!LoadImage(openFileDlg.FileName)) return;
            pictureBox.Image = _bitmap;
            textBoxWidth.Text = pictureBox.Image.Width.ToString();
            textBoxHeight.Text = pictureBox.Image.Height.ToString();
            numericPosX.Value = Math.Max(((MaxWidth - pictureBox.Image.Width) / 2), 0);
            numericPosY.Value = 0;
            textBoxBackColor.Text = ColorTranslator.ToHtml(_bitmap.GetPixel(0, 0));
            textBoxForeColor.Text = ColorTranslator.ToHtml(Color.FromArgb(0, 0, 0));
            btnSaveRaw.Enabled = true;
            panelInfo.Enabled = true;
        }

        private bool LoadImage(string fileName, bool silent = false)
        {
            try
            {
                _bitmap = new Bitmap(Image.FromFile(fileName));
            }
            catch (Exception ex)
            {
                if (!silent)
                {
                    MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                return false;
            }
            if (_bitmap.Width > MaxWidth || _bitmap.Height > MaxHeigth)
            {
                _bitmap.Dispose();
                _bitmap = null;
                if (!silent)
                {
                    MessageBox.Show(this, "Image is too big", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                return false;
            }
            return true;
        }
        private void textBoxColor_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            pictureBox.Capture = true;
            pictureBox.Cursor = Cursors.Cross;
            pictureBox.Tag = sender;
        }

        private void pictureBox_MouseClick(object sender, MouseEventArgs e)
        {
            if (!pictureBox.Capture) return;
            var textBox = pictureBox.Tag as TextBox;
            if (textBox != null)
            {
                if (e.Location.X > _bitmap.Width - 1) return;
                if (e.Location.Y > _bitmap.Height - 1) return;
                textBox.Text = ColorTranslator.ToHtml(_bitmap.GetPixel(e.Location.X, e.Location.Y));
            }
            pictureBox.Tag = null;
            pictureBox.Cursor = Cursors.Default;
            pictureBox.Capture = false;
        }

        private void btnSaveRaw_Click(object sender, EventArgs e)
        {
            var fileName = Path.ChangeExtension(openFileDlg.FileName, "raw");
            Color backColor = ColorTranslator.FromHtml(textBoxBackColor.Text);
            Color foreColor = ColorTranslator.FromHtml(textBoxForeColor.Text);
            ushort posX = (ushort)numericPosX.Value;
            ushort posY = (ushort)numericPosY.Value;
            using (FileStream stream = File.Create(fileName))
            {
                libConverter.rgb565 tool = new libConverter.rgb565();
                tool.WriteRawData(stream, _bitmap, checkBoxSwap.Checked, posX, posY, foreColor, backColor);
            }
        }

        private void btnBatch_Click(object sender, EventArgs e)
        {
            folderBrowserDialog.Description = "Выберите директорию с картинками";
            if (folderBrowserDialog.ShowDialog(this) != DialogResult.OK) return;
            var sourceDir = folderBrowserDialog.SelectedPath;

            folderBrowserDialog.Description = "Выберите директорию для сохранения";
            if (folderBrowserDialog.ShowDialog(this) != DialogResult.OK) return;
            var targetDir = folderBrowserDialog.SelectedPath;

            int totalFiles = 0;
            int errorFiles = 0;
            var errorNames = new StringBuilder(1024);
            long maxSize = 0;
            libConverter.rgb565 tool = new libConverter.rgb565();
            foreach (var item in Directory.EnumerateFiles(sourceDir))
            {
                totalFiles++;
                if (LoadImage(item, true))
                {
                    string fileName = Path.Combine(targetDir, Path.GetFileName(item));
                    using (var stream = File.Create(fileName))
                    {
                        tool.WriteBitmap(stream, _bitmap, true, Color.FromArgb(0, 0, 0, 0), Color.FromArgb(0, 0x4D, 0x8D, 0xEE));
                        maxSize = Math.Max(stream.Length, maxSize);
                    }
                }
                else
                {
                    errorNames.AppendFormat("{0}{1}", Path.GetFileName(item), Environment.NewLine);
                    errorFiles++;
                }
            }
            MessageBox.Show(this, String.Format("Всего обработано: {1} файлов.{0}Из них с ошибкой: {2}{0}{3}{0}Максимальный размер: {4}",
                Environment.NewLine, totalFiles, errorFiles, errorNames.ToString(), maxSize), "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
