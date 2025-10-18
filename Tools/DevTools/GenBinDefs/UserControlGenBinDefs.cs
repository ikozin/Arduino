using GenBinDefs.Setting;
using System.Data;
using System.Text;
using System.Text.Json;
using System.Text.RegularExpressions;

namespace GenBinDefs
{
    public partial class UserControlGenBinDefs : UserControl
    {
        private readonly MainSetting setting;
        public UserControlGenBinDefs()
        {
            InitializeComponent();
            using FileStream file = new("DevToolGenBinDefs_Setting.json", FileMode.Open);
            if (file == null) return;
            setting = JsonSerializer.Deserialize<MainSetting>(file)!;
            toolStripComboBoxLang.Items.AddRange([.. setting.Langs.Select(s => s.Lang!)]);
            toolStripComboBoxLang.SelectedIndex = toolStripComboBoxLang.Items.Count > 0 ? 0 : -1;
            try
            {
                string[] fonts = setting.Font!.Split(';', StringSplitOptions.RemoveEmptyEntries);
                if (!float.TryParse(fonts[1], out float fontSize)) fontSize = 10;
                textBoxDefs.Font = new Font(fonts[0], fontSize, FontStyle.Regular);
            }
            catch (Exception)
            {
            }
        }

        private void FillPatternList(LangSetting lang)
        {
            string[] items = lang.Defines;
            checkedListBox.Items.Clear();
            foreach (string item in items)
            {
                int index = checkedListBox.Items.Add(item);
                checkedListBox.SetItemChecked(index, true);
            }
        }

        [GeneratedRegex("(?:{\\d})", RegexOptions.Singleline)]
        private static partial Regex regex();

        static void GenerateDefies(StringBuilder text, string pattern, LangSetting lang)
        {
            try
            {
                int max = 0;
                Regex reg = regex();
                MatchCollection matches = reg.Matches(pattern);
                foreach (Match match in matches)
                {

                    int value = int.Parse(match.Value.Replace('{', ' ').Replace('}', ' '));
                    if (max > value) continue;
                    max = value;
                }

                max = 1 << (max + 1);
                string last = "";
                for (int i = 0; i < max; i++)
                {
                    int b_00 = (i & 0x0001) > 0 ? 1 : 0;
                    int b_01 = (i & 0x0002) > 0 ? 1 : 0;
                    int b_02 = (i & 0x0004) > 0 ? 1 : 0;
                    int b_03 = (i & 0x0008) > 0 ? 1 : 0;
                    int b_04 = (i & 0x0010) > 0 ? 1 : 0;
                    int b_05 = (i & 0x0020) > 0 ? 1 : 0;
                    int b_06 = (i & 0x0040) > 0 ? 1 : 0;
                    int b_07 = (i & 0x0080) > 0 ? 1 : 0;
                    int b_08 = (i & 0x0100) > 0 ? 1 : 0;
                    int b_09 = (i & 0x0200) > 0 ? 1 : 0;
                    int b_10 = (i & 0x0400) > 0 ? 1 : 0;
                    int b_11 = (i & 0x0800) > 0 ? 1 : 0;
                    int b_12 = (i & 0x1000) > 0 ? 1 : 0;
                    int b_13 = (i & 0x2000) > 0 ? 1 : 0;
                    int b_14 = (i & 0x4000) > 0 ? 1 : 0;
                    int b_15 = (i & 0x8080) > 0 ? 1 : 0;
                    string line = string.Format(pattern,
                        b_00, b_01, b_02, b_03,
                        b_04, b_05, b_06, b_07,
                        b_08, b_09, b_10, b_11,
                        b_12, b_13, b_14, b_15);
                    if (last == line) continue;
                    text.AppendFormat(lang.Prefix!, line);
                    text.AppendFormat(lang.Value!, i);
                    text.AppendLine();
                }
            }
            catch (Exception)
            {
            }
        }

        private void ToolStripComboBoxLang_SelectedIndexChanged(object sender, EventArgs e)
        {
            int lang = toolStripComboBoxLang.SelectedIndex;
            FillPatternList(setting.Langs[lang]);
        }

        private void ToolStripMenuItemList_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem menuItem = (ToolStripMenuItem)sender;
            if (bool.TryParse(menuItem.Tag!.ToString(), out bool check))
            {
                for (int i = 0; i < checkedListBox.Items.Count; i++)
                {
                    checkedListBox.SetItemChecked(i, check);
                }
            }
        }

        private void BtnPatternDel_Click(object sender, EventArgs e)
        {
            int index = toolStripComboBoxLang.SelectedIndex;
            LangSetting lang = setting.Langs[index];
            var list = lang.Defines.ToList();
            var except = checkedListBox.CheckedItems.Cast<string>();
            if (!except.Any()) return;
            lang.Defines = [.. list.Except(except)];
            FillPatternList(lang);
        }

        private void ToolStripButtonTask_Click(object sender, EventArgs e)
        {
            int index = toolStripComboBoxLang.SelectedIndex;
            LangSetting lang = setting.Langs[index];
            StringBuilder text = new(1024);
            text.AppendLine(lang.Header);
            var defs = checkedListBox.CheckedItems.Cast<string>().GroupBy(i => i);
            foreach (IGrouping<string, string> def in defs)
            {
                string pattern = def.Key;
                if (string.IsNullOrWhiteSpace(pattern)) continue;
                GenerateDefies(text, pattern, lang);
                text.AppendLine();
            }

            text.AppendLine(lang.Footer);
            textBoxDefs.Text = text.ToString();
        }

        private void ToolStripButtonCopy_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(textBoxDefs.Text);
        }

        private void ToolStripButtonSave_Click(object sender, EventArgs e)
        {
            if (saveFileDlg.ShowDialog(this) == DialogResult.Cancel) return;
            using FileStream file = new(saveFileDlg.FileName, FileMode.Create);
            using StreamWriter writer = new(file, Encoding.UTF8);
            writer.Write(textBoxDefs.Text);
        }
    }
}
