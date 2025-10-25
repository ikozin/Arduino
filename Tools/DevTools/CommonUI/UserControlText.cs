namespace CommonUI
{
    public partial class UserControlText : UserControl
    {
        public UserControlText()
        {
            InitializeComponent();
        }

        public virtual void OpenFile(FileStream stream)
        {

        }
        public virtual void SaveFile(FileStream stream)
        {

        }
        public void CreateToolStrip(ToolStripItem[] toolStripItems) {
            ToolStrip toolStripMenu = new();
            toolStripMenu.SuspendLayout();
            toolStripMenu.Items.AddRange(toolStripItems);
            toolStripMenu.Location = new Point(0, 0);
            toolStripMenu.ResumeLayout(false);
            toolStripMenu.PerformLayout();
            toolStripContainer.TopToolStripPanel.Controls.Add(toolStripMenu);
        }

        public void AddFilterControl(UserControl filter)
        {
            splitContainer.Panel1.SuspendLayout();
            splitContainer.Panel1Collapsed = false;
            splitContainer.Panel1.Controls.Add(filter);
            filter.Dock = DockStyle.Fill;
            splitContainer.Panel1.ResumeLayout(false);
            splitContainer.Panel1.PerformLayout();
        }
        private void OpenToolStripButton_Click(object sender, EventArgs args)
        {
            if (openFileDlg.ShowDialog() != DialogResult.OK) return;
            using FileStream stream = new(openFileDlg.FileName, FileMode.Open);
            OpenFile(stream);
        }

        private void PasteToolStripButtonPaste_Click(object sender, EventArgs args)
        {
            IDataObject? data = Clipboard.GetDataObject();
            if (data == null) return;
            if (!data.GetDataPresent(DataFormats.FileDrop)) return;
            string[] files = (string[])data.GetData(DataFormats.FileDrop)!;
            using FileStream stream = new(files[0], FileMode.Open);
            OpenFile(stream);
        }

        private void CopyToolStripButton_Click(object sender, EventArgs args)
        {
            Clipboard.SetText(textBoxView.Text);
        }

        private void SaveToolStripButton_Click(object sender, EventArgs e)
        {
            if (saveFileDlg.ShowDialog(this) == DialogResult.Cancel) return;
            using FileStream stream = new(saveFileDlg.FileName, FileMode.Create);
            SaveFile(stream);
        }
    }
}
