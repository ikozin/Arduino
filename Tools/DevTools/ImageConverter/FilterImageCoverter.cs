namespace ImageConverter
{
    public partial class FilterImageCoverter : UserControl
    {
        public FilterImageCoverter()
        {
            InitializeComponent();
        }

        public void SetSize(int width, int height)
        {
            textBoxWidth.Text = width.ToString();
            textBoxHeight.Text = height.ToString();
        }
    }
}
