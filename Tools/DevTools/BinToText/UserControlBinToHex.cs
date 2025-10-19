namespace BinToText
{
    using BinToText.Setting;
    using CommonUI;
    using System;
    using System.Text;
    using System.Text.Json;
    using System.Text.RegularExpressions;
    using System.Windows.Forms;
    //
    public partial class UserControlBinToHex : UserControlText
    {
        private readonly MainSetting setting;

        private readonly ToolStripComboBox toolStripComboBoxLang = new();
        private readonly ToolStripLabel toolStripLabelLen = new();
        private readonly ToolStripComboBox toolStripComboBoxLen = new();

        public UserControlBinToHex()
        {
            InitializeComponent();

            toolStripComboBoxLang.DropDownStyle = ComboBoxStyle.DropDownList;
            toolStripLabelLen.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripLabelLen.Text = "Кол-во байт в строке";
            toolStripComboBoxLen.DropDownStyle = ComboBoxStyle.DropDownList;
            toolStripComboBoxLen.Items.AddRange(["4", "8", "16", "32"]);
            CreateToolStrip([toolStripComboBoxLang, toolStripLabelLen, toolStripComboBoxLen]);

            using FileStream file = new("DevToolBinToHex_Setting.json", FileMode.Open);
            if (file == null) return;
            setting = JsonSerializer.Deserialize<MainSetting>(file)!;
            toolStripComboBoxLang.Items.AddRange([.. setting.Langs.Select(s => s.Lang!)]);
            toolStripComboBoxLang.SelectedIndex = toolStripComboBoxLang.Items.Count > 0 ? 0 : -1;
            toolStripComboBoxLen.SelectedIndex = 2;
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
        private void Convert(FileStream stream, LangSetting setting, uint length)
        {
            textBoxView.Text = String.Empty;
            using BinaryReader reader = new(stream);
            int fileSize = (int)stream.Length;
            StringBuilder text = new(fileSize << 2);
            string name = Path.GetFileNameWithoutExtension(stream.Name);
            Regex reg = new(setting.Name!, RegexOptions.Singleline);
            name = reg.Replace(name, "_");
            text.AppendFormat(setting.Header!, name);
            long line = 0;
            while (fileSize-- > 0)
            {
                if (line == 0)
                {
                    line = length;
                    text.AppendLine();

                }
                byte data = reader.ReadByte();
                text.AppendFormat(setting.Value!, data);
                line--;
            }
            text.AppendLine();
            text.AppendLine(setting.Footer);
            textBoxView.Text = text.ToString();
        }
        public override void OpenFile(FileStream stream)
        {
            int index = toolStripComboBoxLang.SelectedIndex;
            LangSetting lang = setting.Langs[index];
            Convert(stream, lang, uint.Parse(toolStripComboBoxLen.Text));
        }

        public override void SaveFile(FileStream stream)
        {
            using StreamWriter writer = new(stream, Encoding.UTF8);
            writer.Write(textBoxView .Text);

        }
    }
}
