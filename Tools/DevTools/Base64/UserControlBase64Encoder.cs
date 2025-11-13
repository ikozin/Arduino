using Base64Encoder.Setting;
using CommonUI;
using System.Text.Json;

namespace Base64Encoder
{
    public partial class UserControlBase64Encoder : DevToolViewText
    {
        private readonly MainSetting setting;
        public UserControlBase64Encoder()
        {
            InitializeComponent();

            using FileStream file = new("DevToolBase64Encoder_Setting.json", FileMode.Open);
            if (file == null) return;
            setting = JsonSerializer.Deserialize<MainSetting>(file)!;
            try
            {
                string[] fonts = setting.Font!.Split(';', StringSplitOptions.RemoveEmptyEntries);
                if (!float.TryParse(fonts[1], out float fontSize)) fontSize = 10;
                View.Font = new Font(fonts[0], fontSize, FontStyle.Regular);
            }
            catch (Exception)
            {
            }
        }
        public override void OpenFile(FileStream stream)
        {
            byte[] data = new byte[stream.Length];
            stream.Read(data, 0, data.Length);
            View.Text = System.Convert.ToBase64String(data);
        }
    }
}
