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
            ToolStripButton toolStripButtonLoad;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserControlBinToHex));
            ToolStripButton toolStripButtonPaste;
            ToolStripSeparator toolStripSeparator1;
            ToolStripLabel toolStripLabelLen;
            ToolStripSeparator toolStripSeparator2;
            ToolStripButton toolStripButtonCopy;
            ToolStripButton toolStripButtonSave;
            textBoxFile = new TextBox();
            openFileDlg = new OpenFileDialog();
            saveFileDlg = new SaveFileDialog();
            toolStripMenu = new ToolStrip();
            toolStripComboBoxLang = new ToolStripComboBox();
            toolStripComboBoxLen = new ToolStripComboBox();
            toolStripButtonLoad = new ToolStripButton();
            toolStripButtonPaste = new ToolStripButton();
            toolStripSeparator1 = new ToolStripSeparator();
            toolStripLabelLen = new ToolStripLabel();
            toolStripSeparator2 = new ToolStripSeparator();
            toolStripButtonCopy = new ToolStripButton();
            toolStripButtonSave = new ToolStripButton();
            toolStripMenu.SuspendLayout();
            SuspendLayout();
            // 
            // toolStripButtonLoad
            // 
            toolStripButtonLoad.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButtonLoad.Image = (Image)resources.GetObject("toolStripButtonLoad.Image");
            toolStripButtonLoad.ImageTransparentColor = Color.Magenta;
            toolStripButtonLoad.Name = "toolStripButtonLoad";
            toolStripButtonLoad.Size = new Size(73, 25);
            toolStripButtonLoad.Text = "Згрузить";
            toolStripButtonLoad.Click += ToolStripButtonLoad_Click;
            // 
            // toolStripButtonPaste
            // 
            toolStripButtonPaste.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButtonPaste.Image = (Image)resources.GetObject("toolStripButtonPaste.Image");
            toolStripButtonPaste.ImageTransparentColor = Color.Magenta;
            toolStripButtonPaste.Name = "toolStripButtonPaste";
            toolStripButtonPaste.Size = new Size(47, 25);
            toolStripButtonPaste.Text = "Paste";
            toolStripButtonPaste.Click += ToolStripButtonPaste_Click;
            // 
            // toolStripSeparator1
            // 
            toolStripSeparator1.Name = "toolStripSeparator1";
            toolStripSeparator1.Size = new Size(6, 28);
            // 
            // toolStripLabelLen
            // 
            toolStripLabelLen.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripLabelLen.Name = "toolStripLabelLen";
            toolStripLabelLen.Size = new Size(156, 25);
            toolStripLabelLen.Text = "Кол-во байт в строке";
            // 
            // toolStripSeparator2
            // 
            toolStripSeparator2.Name = "toolStripSeparator2";
            toolStripSeparator2.Size = new Size(6, 28);
            // 
            // toolStripButtonCopy
            // 
            toolStripButtonCopy.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButtonCopy.Image = (Image)resources.GetObject("toolStripButtonCopy.Image");
            toolStripButtonCopy.ImageTransparentColor = Color.Magenta;
            toolStripButtonCopy.Name = "toolStripButtonCopy";
            toolStripButtonCopy.Size = new Size(47, 25);
            toolStripButtonCopy.Text = "Copy";
            toolStripButtonCopy.Click += ToolStripButtonCopy_Click;
            // 
            // toolStripButtonSave
            // 
            toolStripButtonSave.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButtonSave.Image = (Image)resources.GetObject("toolStripButtonSave.Image");
            toolStripButtonSave.ImageTransparentColor = Color.Magenta;
            toolStripButtonSave.Name = "toolStripButtonSave";
            toolStripButtonSave.Size = new Size(44, 25);
            toolStripButtonSave.Text = "Save";
            toolStripButtonSave.Click += ToolStripButtonSave_Click;
            // 
            // textBoxFile
            // 
            textBoxFile.AcceptsReturn = true;
            textBoxFile.AcceptsTab = true;
            textBoxFile.Dock = DockStyle.Fill;
            textBoxFile.Font = new Font("Roboto", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 204);
            textBoxFile.Location = new Point(0, 28);
            textBoxFile.Multiline = true;
            textBoxFile.Name = "textBoxFile";
            textBoxFile.ReadOnly = true;
            textBoxFile.ScrollBars = ScrollBars.Both;
            textBoxFile.Size = new Size(814, 422);
            textBoxFile.TabIndex = 8;
            textBoxFile.WordWrap = false;
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
            // toolStripMenu
            // 
            toolStripMenu.ImageScalingSize = new Size(20, 20);
            toolStripMenu.Items.AddRange(new ToolStripItem[] { toolStripComboBoxLang, toolStripButtonLoad, toolStripButtonPaste, toolStripSeparator1, toolStripLabelLen, toolStripComboBoxLen, toolStripSeparator2, toolStripButtonCopy, toolStripButtonSave });
            toolStripMenu.Location = new Point(0, 0);
            toolStripMenu.Name = "toolStripMenu";
            toolStripMenu.Size = new Size(814, 28);
            toolStripMenu.TabIndex = 9;
            toolStripMenu.Text = "toolStrip1";
            // 
            // toolStripComboBoxLang
            // 
            toolStripComboBoxLang.DropDownStyle = ComboBoxStyle.DropDownList;
            toolStripComboBoxLang.Name = "toolStripComboBoxLang";
            toolStripComboBoxLang.Size = new Size(121, 28);
            // 
            // toolStripComboBoxLen
            // 
            toolStripComboBoxLen.DropDownStyle = ComboBoxStyle.DropDownList;
            toolStripComboBoxLen.Items.AddRange(new object[] { "4", "8", "16", "32" });
            toolStripComboBoxLen.Name = "toolStripComboBoxLen";
            toolStripComboBoxLen.Size = new Size(121, 28);
            // 
            // UserControlBinToHex
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(textBoxFile);
            Controls.Add(toolStripMenu);
            Name = "UserControlBinToHex";
            Size = new Size(814, 450);
            toolStripMenu.ResumeLayout(false);
            toolStripMenu.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox textBoxFile;
        private OpenFileDialog openFileDlg;
        private SaveFileDialog saveFileDlg;
        private ToolStrip toolStripMenu;
        private ToolStripComboBox toolStripComboBoxLang;
        private ToolStripComboBox toolStripComboBoxLen;
    }
}
