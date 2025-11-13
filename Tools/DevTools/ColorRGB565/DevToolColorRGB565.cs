using ColorRGB565.Properties;
using CommonUI;

namespace ColorRGB565
{
    public class DevToolColorRGB565 : DevTool<UserControlColorRGB565>
    {
        public DevToolColorRGB565()
        {
            _menu = Resources.Menu;
            _title = Resources.Title;
        }
    }
}
