namespace DevTools
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            ToolStripMenuItem fileToolStripMenuFile;
            menuStripMain = new MenuStrip();
            toolsToolStripMenuTools = new ToolStripMenuItem();
            panelMain = new Panel();
            fileToolStripMenuFile = new ToolStripMenuItem();
            menuStripMain.SuspendLayout();
            SuspendLayout();
            // 
            // fileToolStripMenuFile
            // 
            fileToolStripMenuFile.Name = "fileToolStripMenuFile";
            fileToolStripMenuFile.Size = new Size(46, 24);
            fileToolStripMenuFile.Text = "&File";
            fileToolStripMenuFile.ToolTipText = "File";
            // 
            // menuStripMain
            // 
            menuStripMain.ImageScalingSize = new Size(20, 20);
            menuStripMain.Items.AddRange(new ToolStripItem[] { fileToolStripMenuFile, toolsToolStripMenuTools });
            menuStripMain.Location = new Point(0, 0);
            menuStripMain.Name = "menuStripMain";
            menuStripMain.Size = new Size(855, 28);
            menuStripMain.TabIndex = 0;
            menuStripMain.Text = "menuStrip1";
            // 
            // toolsToolStripMenuTools
            // 
            toolsToolStripMenuTools.Name = "toolsToolStripMenuTools";
            toolsToolStripMenuTools.Size = new Size(58, 24);
            toolsToolStripMenuTools.Text = "&Tools";
            // 
            // panelMain
            // 
            panelMain.BorderStyle = BorderStyle.Fixed3D;
            panelMain.Dock = DockStyle.Fill;
            panelMain.Location = new Point(0, 28);
            panelMain.Name = "panelMain";
            panelMain.Size = new Size(855, 468);
            panelMain.TabIndex = 1;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(855, 496);
            Controls.Add(panelMain);
            Controls.Add(menuStripMain);
            MainMenuStrip = menuStripMain;
            Name = "MainForm";
            Text = "DevTools";
            menuStripMain.ResumeLayout(false);
            menuStripMain.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ToolStripMenuItem toolsToolStripMenuTools;
        private MenuStrip menuStripMain;
        private Panel panelMain;
    }
}
