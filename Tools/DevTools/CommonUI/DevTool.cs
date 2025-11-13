namespace CommonUI
{
    public class DevTool<UI> : IDevTool where UI : UserControl, new()
    {
        protected string _menu;
        protected string _title;
        public DevTool()
        {
            _menu = "Menu";
            _title = "Title";
        }
        public string Menu { get { return _menu; } }
        public string Title { get { return _title; } }

        public UserControl GetUserControl()
        {
            UI control = new UI();
            control.Dock = DockStyle.Fill;
            control.Location = new Point(0, 0);
            control.TabIndex = 0;
            return control;
        }

    }
}
