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
        private readonly ToolStripButton toolStripButton = new();

        private readonly MainSetting setting;

        public UserControlFontCostructor()
        {
            InitializeComponent();
            toolStripOpen.Visible = false;

            using FileStream file = new("DevToolFontCostructor_Setting.json", FileMode.Open);
            if (file == null) return;
            setting = JsonSerializer.Deserialize<MainSetting>(file)!;

            toolStripButton.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButton.Text = "&Generate";
            toolStripButton.Click += RunToolStripButton_Click;


            CreateToolStrip([toolStripButton]);
            AddFilterControl(_filter);
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
        private void RunToolStripButton_Click(object? sender, EventArgs e)
        {
            //StringBuilder text = new(4096);

            string charSet = string.Join(null, _filter.textBoxFilter.Lines);
            var list = charSet.GroupBy(c => c).Select(c => c.Key).Order().ToArray();

            View.Lines = list.Select(c => c.ToString()).ToArray();

        }
    }
}
