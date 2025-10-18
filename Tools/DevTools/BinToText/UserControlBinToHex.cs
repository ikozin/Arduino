namespace BinToText
{
    using BinToText.Setting;
    using System;
    using System.Text;
    using System.Text.Json;
    using System.Text.RegularExpressions;
    using System.Windows.Forms;
    //
    public partial class UserControlBinToHex : UserControl
    {
        private readonly MainSetting setting;
        public UserControlBinToHex()
        {
            InitializeComponent();
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
                textBoxFile.Font = new Font(fonts[0], fontSize, FontStyle.Regular);
            }
            catch (Exception)
            {
            }
        }
        private void Convert(string fileName, LangSetting setting, uint length)
        {
            textBoxFile.Text = String.Empty;
            using FileStream stream = new(fileName, FileMode.Open);
            using BinaryReader reader = new(stream);
            int fileSize = (int)stream.Length;
            StringBuilder text = new(fileSize << 2);
            string name = Path.GetFileNameWithoutExtension(fileName);
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
            textBoxFile.Text = text.ToString();
        }
        private void ToolStripButtonLoad_Click(object sender, EventArgs e)
        {
            int index = toolStripComboBoxLang.SelectedIndex;
            if (index == -1) return;
            if (openFileDlg.ShowDialog() == DialogResult.Cancel) return;
            LangSetting lang = setting.Langs[index];
            Convert(openFileDlg.FileName, lang, uint.Parse(toolStripComboBoxLen.Text));
        }

        private void ToolStripButtonPaste_Click(object sender, EventArgs e)
        {
            int index = toolStripComboBoxLang.SelectedIndex;
            if (index == -1) return;
            IDataObject? data = Clipboard.GetDataObject();
            if (data == null) return;
            if (!data.GetDataPresent(DataFormats.FileDrop)) return;
            string[] files = (string[])data.GetData(DataFormats.FileDrop)!;
            LangSetting lang = setting.Langs[index];
            Convert(files[0], lang, uint.Parse(toolStripComboBoxLen.Text));
        }

        private void ToolStripButtonCopy_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(textBoxFile.Text);
        }

        private void ToolStripButtonSave_Click(object sender, EventArgs e)
        {
            if (saveFileDlg.ShowDialog(this) == DialogResult.Cancel) return;
            using FileStream file = new(saveFileDlg.FileName, FileMode.Create);
            using StreamWriter writer = new(file, Encoding.UTF8);
            writer.Write(textBoxFile.Text);

        }
    }
}
