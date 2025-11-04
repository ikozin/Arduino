using CommonUI;
using ImageConverter.Setting;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace ImageConverter
{
    public partial class UserControlImageConverter : DevToolViewCustom<PictureBox>
    {
        private FilterImageCoverter _filter = new() ;
        private Bitmap _bitmap = null;
        private readonly MainSetting _setting;
        public UserControlImageConverter()
        {
            InitializeComponent();
            View.SizeMode = PictureBoxSizeMode.CenterImage;
            View.BorderStyle = BorderStyle.Fixed3D;


            using FileStream file = new("ImageCoverter_Setting.json", FileMode.Open);
            if (file == null) return;
            _setting = JsonSerializer.Deserialize<MainSetting>(file)!;
            AddFilterControl(_filter);
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
        
        public override void OpenFile(FileStream stream)
        {
            View.Image?.Dispose();
            _bitmap?.Dispose();
            try
            {
                _filter.SetSize(0, 0);
                _bitmap = new Bitmap(Image.FromStream(stream));
                View.Image = _bitmap;
                _filter.SetSize(_bitmap.Width, _bitmap.Height);
            }
            catch (Exception)
            {
            }
        }

        public override void SaveFile(FileStream stream)
        {

        }

        public override void SetClipboardData()
        {

        }
    }
}
