using CommonUI;
using ImageConverter.Properties;

namespace ImageConverter
{
    public class DevToolImageConverter : DevTool<UserControlImageConverter>
    {
        public DevToolImageConverter()
        {
            _menu = Resources.Menu;
            _title = Resources.Title;
        }
    }
}
