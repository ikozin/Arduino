namespace CommonUI
{
    partial class DevToolViewCustom<T>
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DevToolViewCustom<T>));
            ToolStripSeparator toolStripSeparator1;
            ToolStripButton pasteToolStripButtonPaste;
            ToolStripSeparator toolStripSeparator2;
            ToolStripButton copyToolStripButton;
            ToolStripButton saveToolStripButton;
            openFileDlg = new OpenFileDialog();
            saveFileDlg = new SaveFileDialog();
            toolStripContainer = new ToolStripContainer();
            splitContainer = new SplitContainer();
            toolStripSave = new ToolStrip();
            toolStripOpen = new ToolStrip();
            openToolStripButton = new ToolStripButton();
            toolStripSeparator1 = new ToolStripSeparator();
            pasteToolStripButtonPaste = new ToolStripButton();
            toolStripSeparator2 = new ToolStripSeparator();
            copyToolStripButton = new ToolStripButton();
            saveToolStripButton = new ToolStripButton();
            toolStripContainer.ContentPanel.SuspendLayout();
            toolStripContainer.TopToolStripPanel.SuspendLayout();
            toolStripContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer).BeginInit();
            splitContainer.Panel2.SuspendLayout();
            splitContainer.SuspendLayout();
            toolStripSave.SuspendLayout();
            toolStripOpen.SuspendLayout();
            SuspendLayout();
            // 
            // openToolStripButton
            // 
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
            copyToolStripButton.Name = "copyToolStripButton";
            copyToolStripButton.Size = new Size(67, 24);
            copyToolStripButton.Text = "&Copy";
            copyToolStripButton.Click += CopyToolStripButton_Click;
            // 
            // saveToolStripButton
            // 
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
            toolStripContainer.BottomToolStripPanelVisible = false;
            // 
            // toolStripContainer.ContentPanel
            // 
            toolStripContainer.ContentPanel.Controls.Add(splitContainer);
            toolStripContainer.ContentPanel.Size = new Size(663, 471);
            toolStripContainer.Dock = DockStyle.Fill;
            toolStripContainer.LeftToolStripPanelVisible = false;
            toolStripContainer.Location = new Point(0, 0);
            toolStripContainer.Name = "toolStripContainer";
            toolStripContainer.RightToolStripPanelVisible = false;
            toolStripContainer.Size = new Size(663, 498);
            toolStripContainer.TabIndex = 0;
            toolStripContainer.Text = "toolStripContainer";
            // 
            // toolStripContainer.TopToolStripPanel
            // 
            toolStripContainer.TopToolStripPanel.Controls.Add(toolStripOpen);
            toolStripContainer.TopToolStripPanel.Controls.Add(toolStripSave);
            // 
            // splitContainer
            // 
            splitContainer.Dock = DockStyle.Fill;
            splitContainer.Location = new Point(0, 0);
            splitContainer.Name = "splitContainer";
            splitContainer.Panel1Collapsed = true;
            splitContainer.Panel1MinSize = 200;
            // 
            // splitContainer.Panel2
            // 
            splitContainer.Size = new Size(663, 471);
            splitContainer.SplitterDistance = 200;
            splitContainer.TabIndex = 1;
            // 
            // toolStripOpen
            // 
            toolStripOpen.AllowMerge = false;
            toolStripOpen.Dock = DockStyle.None;
            toolStripOpen.ImageScalingSize = new Size(20, 20);
            toolStripOpen.Items.AddRange(new ToolStripItem[] { openToolStripButton, toolStripSeparator1, pasteToolStripButtonPaste });
            toolStripOpen.LayoutStyle = ToolStripLayoutStyle.HorizontalStackWithOverflow;
            toolStripOpen.Location = new Point(0, 0);
            toolStripOpen.Name = "toolStripOpen";
            toolStripOpen.Size = new Size(155, 27);
            toolStripOpen.TabIndex = 0;
            // 
            // toolStripSave
            // 
            toolStripSave.Dock = DockStyle.None;
            toolStripSave.ImageScalingSize = new Size(20, 20);
            toolStripSave.Items.AddRange(new ToolStripItem[] { copyToolStripButton, toolStripSeparator2, saveToolStripButton });
            toolStripSave.LayoutStyle = ToolStripLayoutStyle.HorizontalStackWithOverflow;
            toolStripSave.Location = new Point(120, 0);
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
            toolStripContainer.TopToolStripPanel.ResumeLayout(false);
            toolStripContainer.TopToolStripPanel.PerformLayout();
            toolStripContainer.ResumeLayout(false);
            toolStripContainer.PerformLayout();
            splitContainer.Panel2.ResumeLayout(false);
            splitContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer).EndInit();
            splitContainer.ResumeLayout(false);
            toolStripSave.ResumeLayout(false);
            toolStripSave.PerformLayout();
            toolStripOpen.ResumeLayout(false);
            toolStripOpen.PerformLayout();
            ResumeLayout(false);
        }

        #endregion
        private OpenFileDialog openFileDlg;
        private SaveFileDialog saveFileDlg;
        public ToolStrip toolStripOpen;
        public ToolStrip toolStripSave;
        public ToolStripContainer toolStripContainer;
        protected SplitContainer splitContainer;
    }
}
