using CommonUI;
using HexIO;
using IntelHexEncoder.Setting;
using System.Globalization;
using System.Text;
using System.Text.Json;

namespace IntelHexEncoder
{
    public partial class UserControlIntelHexEncoder : DevToolViewText
    {
        private readonly ToolStripLabel toolStripLabelAddress = new();
        private readonly ToolStripTextBox toolStripTextBoxAddress = new();

        private readonly MainSetting setting;
        private byte[] memory = [];
        public UserControlIntelHexEncoder()
        {
            InitializeComponent();

            toolStripLabelAddress.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripLabelAddress.Text = "Адрес:";
            toolStripTextBoxAddress.Text = "0000";
            CreateToolStrip([toolStripLabelAddress, toolStripTextBoxAddress]);

            using FileStream file = new("DevToolIntelHexEncoder_Setting.json", FileMode.Open);
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

        private void Convert()
        {
            if (!int.TryParse(toolStripTextBoxAddress.Text, NumberStyles.HexNumber, null, out int addr))
            {
                MessageBox.Show(this, "Ошибка в адресе", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            using MemoryStream stream = new(memory.Length << 3);
            using IntelHexStreamWriter writer = new(stream);
            var chunks = memory.Chunk(16);
            foreach (var chunk in chunks)
            {
                writer.WriteDataRecord((ushort)addr, chunk);
                addr += chunk.Length;
            }
            writer.Close();
            View.Text = Encoding.UTF8.GetString(stream.ToArray());
        }
        public override void OpenFile(FileStream stream)
        {
            memory = new byte[stream.Length];
            stream.Read(memory, 0, memory.Length);
            Convert();
        }
    }
}
