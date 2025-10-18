using CommonUI;
using System.Text;
using System.Text.Json;
using ViewHex.Setting;

namespace ViewHex
{
    public partial class UserControlViewHex : UserControlText
    {
        private readonly MainSetting setting;
        private byte[] memory = new byte[0];
        public UserControlViewHex()
        {
            InitializeComponent();

            toolStripSave.Enabled = false;
            toolStripSave.Visible = false;

            using FileStream file = new("DevToolViewHex_Setting.json", FileMode.Open);
            if (file == null) return;
            setting = JsonSerializer.Deserialize<MainSetting>(file)!;
            try
            {
                string[] fonts = setting.Font!.Split(';', StringSplitOptions.RemoveEmptyEntries);
                if (!float.TryParse(fonts[1], out float fontSize)) fontSize = 10;
                textBoxView.Font = new Font(fonts[0], fontSize, FontStyle.Regular);
            }
            catch (Exception)
            {
            }
        }

        public override void OpenFile(FileStream stream)
        {
            memory = new byte[stream.Length];
            stream.Read(memory, 0, memory.Length);
            DisplayHex();
        }

        public override void SaveFile(FileStream stream)
        {
            memory = new byte[stream.Length];
            stream.Read(memory, 0, memory.Length);
            DisplayHex();
        }

        private void DisplayHex()
        {
            StringBuilder text = new StringBuilder((int)memory.Length << 2);
            text.AppendLine("    │ 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
                text.Append("────┼─────────────────────────────────────────────────");

            for (int i = 0; i < memory.Length; i++)
            {
                if (i % 16 == 0)
                {
                    text.AppendLine();
                    text.AppendFormat("{0:X4}│", i);
                }
                text.AppendFormat(" {0:X2}", memory[i]);

            }
            textBoxView.Text = text.ToString();
        }
    }
}
