using GenBinDefs.Setting;
using System.Data;

namespace GenBinDefs
{
    public partial class FilterGenBinDefs : UserControl
    {
        private LangSetting _lang;
        public LangSetting Lang
        {
            get
            {
                return _lang;
            }
            set
            {
                if (_lang != value)
                {
                    _lang = value;
                    FillPatternList(_lang);
                }
            }
        }

        public FilterGenBinDefs()
        {
            InitializeComponent();
        }

        private void FillPatternList(LangSetting lang)
        {
            checkedListBox.Items.Clear();
            if (_lang == null) return;

            foreach (string item in lang.Defines)
            {
                int index = checkedListBox.Items.Add(item);
                checkedListBox.SetItemChecked(index, true);
            }
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
            if (Lang == null) return;
            var list = _lang.Defines.ToList();
            var except = checkedListBox.CheckedItems.Cast<string>();
            if (!except.Any()) return;
            Lang.Defines = [.. list.Except(except)];
            FillPatternList(Lang);
        }

        private void btnPatternAdd_Click(object sender, EventArgs e)
        {
            if (Lang == null) return;
            var list = Lang.Defines.ToList();
            if (list.Contains(textBoxPattern.Text)) return;

            list.Add(textBoxPattern.Text);
            Lang.Defines = list.Order().ToArray();
            FillPatternList(Lang);

        }
    }
}
