using ColorRGB565.Setting;
using CommonUI;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Text.Json;
using System.Windows.Forms;

namespace ColorRGB565
{
    public partial class UserControlColorRGB565 : DevToolViewCustom<PictureBox>
    {
        private FilterColorRGB565 _filter = null;
        private Bitmap? _bitmap = null;
        private readonly MainSetting _setting;

        private readonly ToolStripLabel toolStripLabelScale = new();
        private readonly ToolStripComboBox toolStripComboBoxScale = new();
        private int _scale = 1;

        public UserControlColorRGB565()
        {
            InitializeComponent();

            _filter = new(this);

            toolStripLabelScale.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripLabelScale.Text = "Масштаб";

            toolStripComboBoxScale.DropDownStyle = ComboBoxStyle.DropDownList;
            toolStripComboBoxScale.Items.AddRange(["x1", "x2", "x4", "x8", "x16"]);
            toolStripComboBoxScale.SelectedIndex = 0;
            toolStripComboBoxScale.SelectedIndexChanged += ToolStripComboBoxScale_SelectedIndexChanged;

            CreateToolStrip([toolStripLabelScale, toolStripComboBoxScale]);

            View.SizeMode = PictureBoxSizeMode.CenterImage;
            View.BorderStyle = BorderStyle.Fixed3D;
            View.MouseMove += View_MouseMove;
            View.MouseClick += View_MouseClick;

            _filter.SetLocation(null, null);
            _filter.SetImage(_bitmap, true);
            AddFilterControl(_filter);

            using FileStream file = new("ColorRGB565_Setting.json", FileMode.Open);
            if (file == null) return;
            _setting = JsonSerializer.Deserialize<MainSetting>(file)!;
            try
            {
                string[] fonts = _setting.Font!.Split(';', StringSplitOptions.RemoveEmptyEntries);
                if (!float.TryParse(fonts[1], out float fontSize)) fontSize = 10;
                //View.Font = new Font(fonts[0], fontSize, FontStyle.Regular);
            }
            catch (Exception)
            {
            }
        }

        private void ToolStripComboBoxScale_SelectedIndexChanged(object? sender, EventArgs e)
        {
            ToolStripComboBox combo = (ToolStripComboBox)sender!;
            _scale = (int)System.Math.Pow(2, combo.SelectedIndex);
            Bitmap? image = GetImage(_bitmap, _scale);
            _filter.SetImage(null, false);
            if (image == null) return;
            View.Image?.Dispose();
            View.Image = image;
            _filter.SetImage(_bitmap, false);
        }

        private void View_MouseMove(object? sender, MouseEventArgs e)
        {
            if (_bitmap == null) return;
            
            int left = (View.Size.Width - View.Image.Size.Width) >> 1;
            int right = left + View.Image.Size.Width + 1;

            int top = (View.Size.Height - View.Image.Size.Height) >> 1;
            int bottom = top + View.Image.Size.Height + 1;

            int? x = (e.Location.X >= left && e.Location.X <= right) ? (e.Location.X - left) / _scale : null;
            int? y = (e.Location.Y >= top && e.Location.Y <= bottom) ? (e.Location.Y - top) / _scale : null;

            if (x.HasValue && y.HasValue)
            {
                _filter.SetLocation(x, y);
            }
            else
            {
                _filter.SetLocation(null, null);
            }
        }
        private void View_MouseClick(object? sender, MouseEventArgs e)
        {
            if (_bitmap == null) return;
            if (e.Button != MouseButtons.Left) return;

            int left = (View.Size.Width - View.Image.Size.Width) >> 1;
            int right = left + View.Image.Size.Width + 1;

            int top = (View.Size.Height - View.Image.Size.Height) >> 1;
            int bottom = top + View.Image.Size.Height + 1;

            int? x = (e.Location.X >= left && e.Location.X <= right) ? (e.Location.X - left) / _scale : null;
            int? y = (e.Location.Y >= top && e.Location.Y <= bottom) ? (e.Location.Y - top) / _scale : null;
            if (x.HasValue && y.HasValue)
            {
                Color color = _bitmap.GetPixel(x.Value, y.Value);
                _filter.SetColor(color);
            }
        }
        public void ReloadImage()
        {
            View.Image?.Dispose();
            View.Image = GetImage(_bitmap, _scale);
        }

        public void ReplaceColor(Color fromColor, Color toColor)
        {
            for (int x = 0; x < _bitmap!.Width; x++)
            {
                for (int y = 0; y < _bitmap!.Height; y++)
                {
                    Color color = _bitmap.GetPixel(x, y);
                    if (color != fromColor) continue;
                    _bitmap.SetPixel(x, y, toColor);
                }
            }
            ReloadImage();

        }

        public override void OpenFile(FileStream stream)
        {
            View.Image?.Dispose();
            _bitmap?.Dispose();
            try
            {
                _filter.SetSize(0, 0);
                _bitmap = new Bitmap(Image.FromStream(stream));
                ReloadImage();
                //View.Image?.Dispose();
                //View.Image = GetImage(_bitmap, _scale);
                _filter.SetImage(_bitmap, true);
                _filter.SetSize(_bitmap.Width, _bitmap.Height);
            }
            catch (Exception)
            {
            }
        }

        public override void SaveFile(FileStream stream)
        {
            if (_bitmap == null) return;
            _bitmap.Save(stream, ImageFormat.Png);
        }

        public override void SetClipboardData()
        {

        }

        private Bitmap? GetImage(Bitmap? bitmap, int scale)
        {
            if (bitmap == null) return null;
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

                using var wrapMode = new ImageAttributes();
                wrapMode.SetWrapMode(WrapMode.TileFlipXY);
                graphics.DrawImage(bitmap, rect, 0, 0, bitmap.Width, bitmap.Height, GraphicsUnit.Pixel, wrapMode);
            }
            return image;
        }

    }
}
