using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
