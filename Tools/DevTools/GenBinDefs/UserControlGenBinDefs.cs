using CommonUI;
using GenBinDefs.Setting;
using System.Data;
using System.Text;
using System.Text.Json;
using System.Text.RegularExpressions;

namespace GenBinDefs
{
    public partial class UserControlGenBinDefs : DevToolViewText
    {
        private FilterGenBinDefs _fliter = new();
        private readonly ToolStripComboBox toolStripComboBoxLang = new();
        private readonly ToolStripButton toolStripButton = new();

        private readonly MainSetting setting;
        public UserControlGenBinDefs()
        {
            InitializeComponent();
            toolStripOpen.Visible = false;

            using FileStream file = new("DevToolGenBinDefs_Setting.json", FileMode.Open);
            if (file == null) return;
            setting = JsonSerializer.Deserialize<MainSetting>(file)!;

            toolStripComboBoxLang.SelectedIndexChanged += ToolStripComboBoxLang_SelectedIndexChanged;
            toolStripComboBoxLang.Items.AddRange([.. setting.Langs.Select(s => s.Lang!)]);
            toolStripComboBoxLang.SelectedIndex = toolStripComboBoxLang.Items.Count > 0 ? 0 : -1;

            toolStripButton.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButton.Text = "&Generate";
            toolStripButton.Click += RunToolStripButton_Click;


            CreateToolStrip([toolStripComboBoxLang, toolStripButton]);
            AddFilterControl(_fliter);
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

        private void ToolStripComboBoxLang_SelectedIndexChanged(object? sender, EventArgs e)
        {
            int index = toolStripComboBoxLang.SelectedIndex;
            _fliter.Lang = setting.Langs[index];
        }

        private void RunToolStripButton_Click(object? sender, EventArgs e)
        {
            StringBuilder text = new(4096);
            int index = toolStripComboBoxLang.SelectedIndex;
            LangSetting lang = setting.Langs[index];
            foreach (var pattern in lang.Defines.Order())
            {
                GenerateDefies(text, pattern, lang);
            }
            View.Text = text.ToString();
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
    }
}
