using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace CommonUI
{
    public interface IDevTool
    {
        public string Menu { get; }
        public string Title { get; }
        public string ToolTip { get; }

        public UserControl GetUserControl();

    }
}
