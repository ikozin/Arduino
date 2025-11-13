using CommonUI;
using ViewHex.Properties;

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

