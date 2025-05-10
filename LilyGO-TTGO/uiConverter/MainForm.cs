using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using System.Windows.Forms;


namespace uiConverter
{
    public partial class MainForm : Form
    {
        private Bitmap _bitmap = null;
        public MainForm()
        {
            InitializeComponent();
            comboBoxSizeMode.DataSource = Enum.GetNames(typeof(PictureBoxSizeMode));
            comboBoxScale.SelectedIndex = 0;
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            if (openFileDlg.ShowDialog(this) != DialogResult.OK) return;
            if (!LoadImage(openFileDlg.FileName)) return;

            textBoxWidth.Text = _bitmap.Width.ToString();
            textBoxHeight.Text = _bitmap.Height.ToString();
            numericPosX.Value = 0;
            numericPosY.Value = 0;
            textBoxBackColor.Text = ColorTranslator.ToHtml(_bitmap.GetPixel(0, 0));
            textBoxForeColor.Text = ColorTranslator.ToHtml(Color.FromArgb(0, 0, 0));
            btnSave.Enabled = true;
            panelInfo.Enabled = true;
        }

        private int GetScale()
        {
            return int.Parse(comboBoxScale.SelectedItem.ToString());
        }
        private bool LoadImage(string fileName, bool silent = false)
        {
            try
            {
                _bitmap?.Dispose();
                _bitmap = new Bitmap(Image.FromFile(fileName));
                ScaleImage(_bitmap, silent);
            }
            catch (Exception ex)
            {
                if (!silent)
                {
                    MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                return false;
            }
            return true;
        }
        private bool ScaleImage(Bitmap bitmap, bool silent = false)
        {
            try
            {
                if (bitmap == null) return false;
                int scale = GetScale();
                int width = bitmap.Width * scale;
                int height = bitmap.Height * scale;
                var rect = new Rectangle(0, 0, width, height);
                PixelFormat format = bitmap.PixelFormat;
                Bitmap image = new(width, height, format);

                image.SetResolution(bitmap.HorizontalResolution, bitmap.VerticalResolution);

                using (var graphics = Graphics.FromImage(image))
                {
                    graphics.CompositingMode = CompositingMode.SourceCopy;
                    graphics.CompositingQuality = CompositingQuality.HighQuality;
                    graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;
                    graphics.SmoothingMode = SmoothingMode.HighQuality;
                    graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;

                    using (var wrapMode = new ImageAttributes())
                    {
                        wrapMode.SetWrapMode(WrapMode.TileFlipXY);
                        graphics.DrawImage(bitmap, rect, 0, 0, bitmap.Width, bitmap.Height, GraphicsUnit.Pixel, wrapMode);
                    }
                }
                pictureBox.Image?.Dispose();
                pictureBox.Image = image;
            }
            catch (Exception ex)
            {
                if (!silent)
                {
                    MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                return false;
            }
            return true;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            var fileName = Path.ChangeExtension(openFileDlg.FileName, "raw");
            using (FileStream stream = File.Create(fileName))
            {
                libConverter.rgb565 tool = new();
                tool.WriteData(stream, _bitmap, checkBoxSwap.Checked);
            }
        }

        private void btnSaveWH_Click(object sender, EventArgs e)
        {
            var fileName = Path.ChangeExtension(openFileDlg.FileName, "raw");
            using (FileStream stream = File.Create(fileName))
            {
                libConverter.rgb565 tool = new libConverter.rgb565();
                tool.WriteData(stream, _bitmap, checkBoxSwap.Checked, (ushort)_bitmap.Width, (ushort)_bitmap.Height);
            }
        }

        private void comboBoxSizeMode_SelectionChangeCommitted(object sender, EventArgs e)
        {
            pictureBox.SizeMode = (PictureBoxSizeMode)Enum.Parse(typeof(PictureBoxSizeMode), ((ComboBox)sender).SelectedItem.ToString());
        }

        private void comboBoxScale_SelectionChangeCommitted(object sender, EventArgs e)
        {
            ScaleImage(_bitmap, false);
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

            pictureBox.Capture = false;
            pictureBox.Cursor = Cursors.Default;
            pictureBox.Tag = null;

            if (textBox != null)
            {
                if (e.Location.X > _bitmap.Width - 1) return;
                if (e.Location.Y > _bitmap.Height - 1) return;
                textBox.Text = ColorTranslator.ToHtml(_bitmap.GetPixel(e.Location.X, e.Location.Y));
            }
        }

        private void btnHexClip_Click(object sender, EventArgs e)
        {
            if (_bitmap == null) return;
            const int length = 16;
            using MemoryStream memory = new();
            libConverter.rgb565 tool = new();
            tool.WriteData(memory, _bitmap, checkBoxSwap.Checked);
            memory.Seek(0, SeekOrigin.Begin);
            using BinaryReader reader = new(memory);
            StringBuilder text = new((int)reader.BaseStream.Length * 6 + (int)reader.BaseStream.Length / length);
            for (int i = 0; i < reader.BaseStream.Length; i++)
            {
                if (i % length == 0) text.AppendLine();
                byte b = reader.ReadByte();
                text.AppendFormat("0x{0:X2}, ", b);
            }
            text.AppendLine();
            Clipboard.SetText(text.ToString());
        }
    }
}
