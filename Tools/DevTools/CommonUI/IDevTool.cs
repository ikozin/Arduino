namespace CommonUI
{
    public interface IDevTool
    {
        public string Menu { get; }
        public string Title { get; }

        public UserControl GetUserControl();

    }
}
