using System.Drawing;
using System.Linq;

namespace ColorRGB565
{
    public partial class FilterColorRGB565 : UserControl
    {
        private Bitmap? _image = null;
        private Color? _color = null;
        private ListViewColumnSorter lvwColumnSorter;
        private UserControlColorRGB565 _owner;

        public FilterColorRGB565()
        {
            InitializeComponent();

            lvwColumnSorter = new ListViewColumnSorter();
            listViewColors.ListViewItemSorter = lvwColumnSorter;
        }

        public FilterColorRGB565(UserControlColorRGB565 owner) : this()
        {
            _owner = owner;
        }
        public void SetSize(int width, int height)
        {
            textBoxWidth.Text = width.ToString();
            textBoxHeight.Text = height.ToString();
        }

        public void SetLocation(int? x, int? y)
        {
            labelX.Text = x.HasValue ? x!.ToString() : String.Empty;
            labelY.Text = y.HasValue ? y!.ToString() : String.Empty;
        }
        public void SetImage(Bitmap? image, bool isNew)
        {
            _image = image;
            btnAnalysis.Enabled = image != null;
            listViewColors.Enabled = image != null;
            if (isNew) listViewColors.Items.Clear();
        }
        public void SetColor(Color? color)
        {
            _color = color;
            textBoxColorHtml.Text = color.HasValue ? ColorTranslator.ToHtml(color.Value) : String.Empty;
            if (color.HasValue)
            {
                UInt16 r = (UInt16)(color.Value.R & 0x1F);
                UInt16 g = (UInt16)(color.Value.G & 0x3F);
                UInt16 b = (UInt16)(color.Value.B & 0x1F);
                labelR.Text = r.ToString();
                labelG.Text = g.ToString();
                labelB.Text = b.ToString();
                r = (UInt16)(r << 11);
                g = (UInt16)(g << 5);
                b = (UInt16)(b << 0);
                UInt16 color565 = (UInt16)(r | g | b);
                textBoxColorHex.Text = String.Format("0x{0:X4}", color565);
            }
            else
            {
                textBoxColorHex.Text = String.Empty;
                labelR.Text = "0";
                labelG.Text = "0";
                labelB.Text = "0";
            }
        }

        private void btnColor_Click(object sender, EventArgs e)
        {
            colorDialog.Color = _color ?? Color.Black;
            if (colorDialog.ShowDialog(this) != DialogResult.OK) return;
            SetColor(colorDialog.Color);
        }

        private void btnAnalysis_Click(object sender, EventArgs e)
        {
            if (_image == null) return;
            listViewColors.BeginUpdate();
            listViewColors.Items.Clear();
            List<Color> colors = new(1024);
            for (int x = 0; x < _image!.Width; x++)
            {
                for (int y = 0; y < _image!.Height; y++)
                {
                    Color color = _image.GetPixel(x, y);
                    colors.Add(color);
                }
            }
            var list = colors.GroupBy(g => g).Select(g => new KeyValuePair<Color, int>(g.Key, g.Count()));
            foreach (KeyValuePair<Color, int> value in list)
            {
                ListViewItem item = new ListViewItem(ColorTranslator.ToHtml(value.Key));
                item.SubItems.Add(value.Value.ToString());

                item.SubItems.Add(value.Key.R.ToString());
                item.SubItems.Add(value.Key.G.ToString());
                item.SubItems.Add(value.Key.B.ToString());
                listViewColors.Items.Add(item);
            }

            lvwColumnSorter.SortColumn = 0;
            lvwColumnSorter.Order = SortOrder.Ascending;
            listViewColors.Sort();
            listViewColors.EndUpdate();
        }

        private void listViewColors_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            if (e.Column == lvwColumnSorter.SortColumn)
            {
                if (lvwColumnSorter.Order == SortOrder.Ascending)
                {
                    lvwColumnSorter.Order = SortOrder.Descending;
                }
                else
                {
                    lvwColumnSorter.Order = SortOrder.Ascending;
                }
            }
            else
            {
                lvwColumnSorter.SortColumn = e.Column;
                lvwColumnSorter.Order = SortOrder.Ascending;
            }
            listViewColors.Sort();
        }

        private void listViewColors_DoubleClick(object sender, EventArgs e)
        {
            if (listViewColors.SelectedItems.Count != 1) return;
            var item = listViewColors.SelectedItems[0];
            var color = ColorTranslator.FromHtml(item.Text);
            SetColor(color);
        }

        private void replaceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listViewColors.SelectedItems.Count == 01) return;
            foreach (ListViewItem item in listViewColors.SelectedItems)
            {
                var fromColor = ColorTranslator.FromHtml(item.Text);
                var toColor = ColorTranslator.FromHtml(textBoxColorHtml.Text);
                _owner.ReplaceColor(fromColor, toColor);
            }
            btnAnalysis.PerformClick();
        }
    }
}
