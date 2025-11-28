using CommonUI;
using FontCostructor.Setting;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FontCostructor
{
    public partial class UserControlFontCostructor : DevToolViewText
    {
        private FilterFontCostructor _filter = new();
        private readonly ToolStripComboBox toolStripComboBoxLang = new();
        private readonly ToolStripButton toolStripButton = new();

        private readonly MainSetting setting;

        public UserControlFontCostructor()
        {
            InitializeComponent();
            toolStripOpen.Visible = false;

            using FileStream file = new("DevToolFontCostructor_Setting.json", FileMode.Open);
            if (file == null) return;
            setting = JsonSerializer.Deserialize<MainSetting>(file)!;

            toolStripComboBoxLang.DropDownStyle = ComboBoxStyle.DropDownList;
            toolStripComboBoxLang.Items.AddRange([.. setting.Langs]);
            toolStripComboBoxLang.SelectedIndex = toolStripComboBoxLang.Items.Count > 0 ? 0 : -1;

            toolStripButton.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButton.Text = "&Generate";
            toolStripButton.Click += RunToolStripButton_Click;

            CreateToolStrip([toolStripComboBoxLang, toolStripButton]);
            AddFilterControl(_filter);
            try
            {
                string[] fonts = setting.Font!.Split(';', StringSplitOptions.RemoveEmptyEntries);
                if (!float.TryParse(fonts[1], out float fontSize)) fontSize = 10;
                View.Font = new Font(fonts[0], fontSize, FontStyle.Regular);
                _filter.AddPatterns(setting.Patterns);
            }
            catch (Exception)
            {
            }
        }
        private void RunToolStripButton_Click(object? sender, EventArgs e)
        {
            StringBuilder text = new(4096);
            LangSetting lang = toolStripComboBoxLang.SelectedItem as LangSetting;

            string charSet = string.Join(null, _filter.textBoxFilter.Lines);
            var list = charSet.GroupBy(c => c).Select(c => c.Key).Order().ToArray();
            charSet = string.Join(null, list);
            for (int i = 0; i < charSet.Length; i++)
            {
                int value = char.ConvertToUtf32(charSet, i);
                text.AppendFormat(lang.Value, value);
                text.AppendLine();
            }
            View.Text = text.ToString();
        }
    }
}
