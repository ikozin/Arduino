using BinToText.Properties;
using CommonUI;

namespace BinToText
{
    public class DevToolBinToHex: DevTool<UserControlBinToHex>
    {
        public DevToolBinToHex()
        {
            _menu = Resources.Menu;
            _title = Resources.Title;
        }
    }
}
