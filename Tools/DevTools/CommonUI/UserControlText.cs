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
