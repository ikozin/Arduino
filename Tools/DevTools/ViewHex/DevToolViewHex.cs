using CommonUI;
using ViewHex.Properties;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace ViewHex
{
    public class DevToolViewHex : DevTool<UserControlViewHex>
    {
        public DevToolViewHex()
        {
            _menu = Resources.Menu;
            _title = Resources.Title;
        }
    }
}

