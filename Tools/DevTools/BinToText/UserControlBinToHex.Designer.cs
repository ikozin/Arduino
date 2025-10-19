namespace BinToText
{
    partial class UserControlBinToHex
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            openFileDlg = new OpenFileDialog();
            saveFileDlg = new SaveFileDialog();
            SuspendLayout();
            // 
            // openFileDlg
            // 
            openFileDlg.Filter = "Все файлы|*.*";
            openFileDlg.RestoreDirectory = true;
            // 
            // saveFileDlg
            // 
            saveFileDlg.Filter = "Все файлы|*.*";
            // 
            // UserControlBinToHex
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            Name = "UserControlBinToHex";
            Size = new Size(814, 450);
            ResumeLayout(false);
        }

        #endregion
        private OpenFileDialog openFileDlg;
        private SaveFileDialog saveFileDlg;
    }
}
