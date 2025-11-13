using Base64Encoder;
using BinToText;
using ColorRGB565;
using CommonUI;
using GenBinDefs;
using ImageConverter;
using IntelHexEncoder;
using ViewHex;

namespace DevTools
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            RegisterDevTool(new DevToolBinToHex());
            RegisterDevTool(new DevToolGenBinDefs());
            RegisterDevTool(new DevToolBase64Encoder());
            RegisterDevTool(new DevToolViewHex());
            RegisterDevTool(new DevToolIntelHexEncoder());
            RegisterDevTool(new DevToolImageConverter());
            RegisterDevTool(new DevToolColorRGB565());

        }

        void RegisterDevTool(IDevTool tool)
        {
            menuStripMain.SuspendLayout();
            ToolStripMenuItem item = new()
            {
                Text = tool.Menu,
                Tag = tool,
            };
            item.Click += ToolStripMenuItem_Click;
            toolsToolStripMenuTools.DropDownItems.Add(item);
            menuStripMain.ResumeLayout(false);
            menuStripMain.PerformLayout();
        }
        void SetCurrentDevTool(IDevTool tool)
        {
            panelMain.SuspendLayout();
            while (panelMain.Controls.Count > 0)
            {
                Control control = panelMain.Controls[panelMain.Controls.Count - 1];
                panelMain.Controls.Remove(control);
                control.Dispose();
            }
            panelMain.Controls.Add(tool.GetUserControl());
            panelMain.ResumeLayout(false);
            panelMain.PerformLayout();
        }
        private void ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (sender is not ToolStripMenuItem item) return;
            if (item.Tag is not IDevTool tool) return;
            SetCurrentDevTool(tool);
            foreach (ToolStripMenuItem menuItem in toolsToolStripMenuTools.DropDownItems)
            {
                menuItem.Checked = false;
            }
            item.Checked = true;
        }

    }
}
