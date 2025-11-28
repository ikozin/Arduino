using FontCostructor.Setting;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FontCostructor
{
    public partial class FilterFontCostructor : UserControl
    {
        public FilterFontCostructor()
        {
            InitializeComponent();
        }

        public void AddPatterns(IEnumerable<PatternItem> list)
        {
            comboBoxPatterns.Items.Clear();
            foreach (var item in list)
            {
                comboBoxPatterns.Items.Add(item);
            }
            comboBoxPatterns.SelectedIndex = 0;
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            PatternItem item = comboBoxPatterns.SelectedItem as PatternItem;
            textBoxFilter.Text += Environment.NewLine;
            textBoxFilter.Text += item.Value;
        }

        private void btnFilter_Click(object sender, EventArgs e)
        {
            string charSet = string.Join(null, textBoxFilter.Lines);
            var list = charSet.GroupBy(c => c).Select(c => c.Key).Order().ToArray();
            textBoxFilter.Text = string.Join(null, list.Select(c => c.ToString()).ToArray());
        }
    }
}
