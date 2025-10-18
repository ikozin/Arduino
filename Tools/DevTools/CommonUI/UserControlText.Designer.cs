namespace CommonUI
{
    partial class UserControlText
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
            ToolStripButton openToolStripButton;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserControlText));
            ToolStripSeparator toolStripSeparator1;
            ToolStripButton pasteToolStripButtonPaste;
            ToolStripSeparator toolStripSeparator2;
            ToolStripButton copyToolStripButton;
            ToolStripButton saveToolStripButton;
            openFileDlg = new OpenFileDialog();
            saveFileDlg = new SaveFileDialog();
            toolStripContainer = new ToolStripContainer();
            textBoxView = new TextBox();
            toolStripOpen = new ToolStrip();
            toolStripSave = new ToolStrip();
            openToolStripButton = new ToolStripButton();
            toolStripSeparator1 = new ToolStripSeparator();
            pasteToolStripButtonPaste = new ToolStripButton();
            toolStripSeparator2 = new ToolStripSeparator();
            copyToolStripButton = new ToolStripButton();
            saveToolStripButton = new ToolStripButton();
            toolStripContainer.ContentPanel.SuspendLayout();
            toolStripContainer.TopToolStripPanel.SuspendLayout();
            toolStripContainer.SuspendLayout();
            toolStripOpen.SuspendLayout();
            toolStripSave.SuspendLayout();
            SuspendLayout();
            // 
            // openToolStripButton
            // 
            openToolStripButton.Image = (Image)resources.GetObject("openToolStripButton.Image");
            openToolStripButton.ImageTransparentColor = Color.Magenta;
            openToolStripButton.Name = "openToolStripButton";
            openToolStripButton.Size = new Size(69, 24);
            openToolStripButton.Text = "&Open";
            openToolStripButton.Click += OpenToolStripButton_Click;
            // 
            // toolStripSeparator1
            // 
            toolStripSeparator1.Name = "toolStripSeparator1";
            toolStripSeparator1.Size = new Size(6, 27);
            // 
            // pasteToolStripButtonPaste
            // 
            pasteToolStripButtonPaste.Image = (Image)resources.GetObject("pasteToolStripButtonPaste.Image");
            pasteToolStripButtonPaste.ImageTransparentColor = Color.Magenta;
            pasteToolStripButtonPaste.Name = "pasteToolStripButtonPaste";
            pasteToolStripButtonPaste.Size = new Size(67, 24);
            pasteToolStripButtonPaste.Text = "&Paste";
            pasteToolStripButtonPaste.Click += PasteToolStripButtonPaste_Click;
            // 
            // toolStripSeparator2
            // 
            toolStripSeparator2.Name = "toolStripSeparator2";
            toolStripSeparator2.Size = new Size(6, 27);
            // 
            // copyToolStripButton
            // 
            copyToolStripButton.Image = (Image)resources.GetObject("copyToolStripButton.Image");
            copyToolStripButton.ImageTransparentColor = Color.Magenta;
            copyToolStripButton.Name = "copyToolStripButton";
            copyToolStripButton.Size = new Size(67, 24);
            copyToolStripButton.Text = "&Copy";
            copyToolStripButton.Click += CopyToolStripButton_Click;
            // 
            // saveToolStripButton
            // 
            saveToolStripButton.Image = (Image)resources.GetObject("saveToolStripButton.Image");
            saveToolStripButton.ImageTransparentColor = Color.Magenta;
            saveToolStripButton.Name = "saveToolStripButton";
            saveToolStripButton.Size = new Size(64, 24);
            saveToolStripButton.Text = "&Save";
            saveToolStripButton.Click += SaveToolStripButton_Click;
            // 
            // openFileDlg
            // 
            openFileDlg.Filter = "Все файлы|*.*";
            // 
            // saveFileDlg
            // 
            saveFileDlg.Filter = "Все файлы|*.*";
            // 
            // toolStripContainer
            // 
            // 
            // toolStripContainer.ContentPanel
            // 
            toolStripContainer.ContentPanel.Controls.Add(textBoxView);
            toolStripContainer.ContentPanel.Size = new Size(663, 471);
            toolStripContainer.Dock = DockStyle.Fill;
            toolStripContainer.Location = new Point(0, 0);
            toolStripContainer.Name = "toolStripContainer";
            toolStripContainer.Size = new Size(663, 498);
            toolStripContainer.TabIndex = 0;
            toolStripContainer.Text = "toolStripContainer";
            // 
            // toolStripContainer.TopToolStripPanel
            // 
            toolStripContainer.TopToolStripPanel.Controls.Add(toolStripOpen);
            toolStripContainer.TopToolStripPanel.Controls.Add(toolStripSave);
            // 
            // textBoxView
            // 
            textBoxView.Dock = DockStyle.Fill;
            textBoxView.Location = new Point(0, 0);
            textBoxView.Multiline = true;
            textBoxView.Name = "textBoxView";
            textBoxView.ReadOnly = true;
            textBoxView.ScrollBars = ScrollBars.Both;
            textBoxView.Size = new Size(663, 471);
            textBoxView.TabIndex = 0;
            textBoxView.WordWrap = false;
            // 
            // toolStripOpen
            // 
            toolStripOpen.Dock = DockStyle.None;
            toolStripOpen.ImageScalingSize = new Size(20, 20);
            toolStripOpen.Items.AddRange(new ToolStripItem[] { openToolStripButton, toolStripSeparator1, pasteToolStripButtonPaste });
            toolStripOpen.Location = new Point(9, 0);
            toolStripOpen.Name = "toolStripOpen";
            toolStripOpen.Size = new Size(155, 27);
            toolStripOpen.TabIndex = 0;
            // 
            // toolStripSave
            // 
            toolStripSave.Dock = DockStyle.None;
            toolStripSave.ImageScalingSize = new Size(20, 20);
            toolStripSave.Items.AddRange(new ToolStripItem[] { copyToolStripButton, toolStripSeparator2, saveToolStripButton });
            toolStripSave.Location = new Point(164, 0);
            toolStripSave.Name = "toolStripSave";
            toolStripSave.Size = new Size(189, 27);
            toolStripSave.TabIndex = 1;
            // 
            // UserControlText
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(toolStripContainer);
            Name = "UserControlText";
            Size = new Size(663, 498);
            toolStripContainer.ContentPanel.ResumeLayout(false);
            toolStripContainer.ContentPanel.PerformLayout();
            toolStripContainer.TopToolStripPanel.ResumeLayout(false);
            toolStripContainer.TopToolStripPanel.PerformLayout();
            toolStripContainer.ResumeLayout(false);
            toolStripContainer.PerformLayout();
            toolStripOpen.ResumeLayout(false);
            toolStripOpen.PerformLayout();
            toolStripSave.ResumeLayout(false);
            toolStripSave.PerformLayout();
            ResumeLayout(false);
        }

        #endregion
        private OpenFileDialog openFileDlg;
        private SaveFileDialog saveFileDlg;
        public ToolStrip toolStripOpen;
        public TextBox textBoxView;
        public ToolStrip toolStripSave;
        public ToolStripContainer toolStripContainer;
    }
}
