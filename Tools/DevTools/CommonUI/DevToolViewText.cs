using System.Text;

namespace CommonUI
{
    public class DevToolViewText : DevToolViewCustom<TextBox>
    {
        public DevToolViewText()
        {
            splitContainer.Panel2.SuspendLayout();
            View.Multiline = true;
            View.ReadOnly = true;
            View.ScrollBars = ScrollBars.Both;
            //textBoxView.Size = new Size(663, 471);
            //textBoxView.TabIndex = 0;
            View.WordWrap = false;
            splitContainer.Panel2.ResumeLayout(false);
            splitContainer.Panel2.PerformLayout();
        }

        public override void SetClipboardData()
        {
            Clipboard.SetText(View.Text);
        }
        public override void SaveFile(FileStream stream)
        {
            using StreamWriter writer = new(stream, Encoding.UTF8);
            writer.Write(View.Text);
        }

    }
}
