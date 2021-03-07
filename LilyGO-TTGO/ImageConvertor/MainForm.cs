using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageConvertor
{
    public partial class MainForm : Form
    {
        private Bitmap _bitmap = null;
        public MainForm()
        {
            InitializeComponent();
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            if (openFileDlg.ShowDialog(this) != DialogResult.OK) return;
            _bitmap = new Bitmap(Image.FromFile(openFileDlg.FileName));
            pictureBox.Image = _bitmap;
            textBoxWidth.Text = pictureBox.Image.Width.ToString();
            textBoxHeight.Text = pictureBox.Image.Height.ToString();
            AnalizeImage();
            panelTool.Enabled = true;
            numericPosX.Value = ((240 - pictureBox.Image.Width) / 2);
            numericPosY.Value = 0;
            panelSave.Enabled = true;
            btnSave.Enabled = true;
        }

        private void AnalizeImage()
        {
            listViewColor.SelectedItems.Clear();
            listViewColor.BeginUpdate();
            listViewColor.Items.Clear();
            Dictionary<Color, int> colorList = new Dictionary<Color, int>();

            for (int y = 0; y < _bitmap.Height; y++)
            {
                for (int x = 0; x < _bitmap.Width; x++)
                {
                    Color pixel = _bitmap.GetPixel(x, y);
                    if (!colorList.ContainsKey(pixel))
                    {
                        colorList.Add(pixel, 0);
                    }
                    colorList[pixel]++;
                }
            }

            foreach (var item in colorList)
            {
                ListViewItem row = new ListViewItem();
                row.Text = String.Format("{0:X2}{1:X2}{2:X2}{3:X2}", item.Key.A, item.Key.R, item.Key.G, item.Key.B);
                row.SubItems.Add(item.Value.ToString());
                row.Tag = item.Key;
                listViewColor.Items.Add(row);
            }
            listViewColor.Sort();
            //listViewColor.AutoResizeColumn(0, ColumnHeaderAutoResizeStyle.ColumnContent);
            //listViewColor.AutoResizeColumn(1, ColumnHeaderAutoResizeStyle.ColumnContent);
            listViewColor.EndUpdate();
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            pictureBox.Image.Save(openFileDlg.FileName);
        }

        private void listViewColor_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListViewItem row = (listViewColor.SelectedItems.Count > 0) ?
                listViewColor.SelectedItems[0] :
                null;

            textBoxColorFrom.Text = row?.Text;
            textBoxBackColor.Text = row?.Text;
            textBoxBackColor.Tag = row?.Tag;
        }

        private void btnChangeColor_Click(object sender, EventArgs e)
        {
            ListViewItem row = (listViewColor.SelectedItems.Count > 0) ?
                listViewColor.SelectedItems[0] :
                null;
            if (row == null) return;

            Color colorFrom = (Color)row.Tag;
            Color colorTo = Color.FromArgb((int)numericToA.Value, (int)numericToR.Value, (int)numericToG.Value, (int)numericToB.Value);

            for (int y = 0; y < _bitmap.Height; y++)
            {
                for (int x = 0; x < _bitmap.Width; x++)
                {
                    Color pixel = _bitmap.GetPixel(x, y);
                    if (pixel == colorFrom)
                    {
                        _bitmap.SetPixel(x, y, colorTo);
                    }
                }
            }
            pictureBox.Image = _bitmap;
            AnalizeImage();
        }

        private void btnSelectColor_Click(object sender, EventArgs e)
        {
            Color colorTo = Color.FromArgb((int)numericToA.Value, (int)numericToR.Value, (int)numericToG.Value, (int)numericToB.Value);
            colorDialog.Color = colorTo;
            if (colorDialog.ShowDialog(this) != DialogResult.OK) return;

            numericToA.Value = colorDialog.Color.A;
            numericToR.Value = colorDialog.Color.R;
            numericToG.Value = colorDialog.Color.G;
            numericToB.Value = colorDialog.Color.B;
        }

        private ushort convertColor2rgb565(Color color)
        {
            return (ushort)(((color.R & 0b11111000) << 8) | ((color.G & 0b11111100) << 3) | (color.B >> 3));

        }
        private void btnSave565_Click(object sender, EventArgs e)
        {
            if (int.Parse(textBoxWidth.Text) > 240 || int.Parse(textBoxHeight.Text) > 135)
            {
                MessageBox.Show(this, "Привышен максимальный размер, маскимум 240x135", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            try
            {
                if (textBoxBackColor.Text.Length == 0)
                    throw new ArgumentOutOfRangeException("BackColor");

                var fileName = Path.ChangeExtension(openFileDlg.FileName, "raw");
                using (FileStream stream = File.Create(fileName))
                {
                    ushort rgb565;
                    byte[] buf;
                    rgb565 = convertColor2rgb565(GetForeColor());
                    foreach (var item in BitConverter.GetBytes(rgb565)) stream.WriteByte(item);
                    rgb565 = convertColor2rgb565((Color)textBoxBackColor.Tag);
                    foreach (var item in BitConverter.GetBytes(rgb565)) stream.WriteByte(item);
                    foreach (var item in BitConverter.GetBytes((ushort)numericPosX.Value)) stream.WriteByte(item);
                    foreach (var item in BitConverter.GetBytes((ushort)numericPosY.Value)) stream.WriteByte(item);
                    foreach (var item in BitConverter.GetBytes((ushort)pictureBox.Image.Width)) stream.WriteByte(item);
                    foreach (var item in BitConverter.GetBytes((ushort)pictureBox.Image.Height)) stream.WriteByte(item);

                    for (int y = 0; y < _bitmap.Height; y++)
                    {
                        for (int x = 0; x < _bitmap.Width; x++)
                        {
                            Color pixel = _bitmap.GetPixel(x, y);
                            rgb565 = convertColor2rgb565(pixel);
                            buf = BitConverter.GetBytes(rgb565);
                            if (checkBoxSwap.Checked)
                            {
                                Array.Reverse(buf);
                            }
                            stream.Write(buf);
                        }
                    }
                    stream.Flush();
                    if (stream.Length > 49152)
                    {
                        MessageBox.Show(this, "Превышен максимальный размер файла 49152 байта", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private Color GetForeColor()
        {
            if (textBoxForeColor.Text.Length != 8 && textBoxForeColor.Text.Length != 6)
                throw new ArgumentOutOfRangeException("ForeColor");
            string colorText = textBoxForeColor.Text;
            return ColorTranslator.FromHtml("#" + colorText);
        }
    }
}
