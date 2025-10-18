using CommonUI;
using IntelHexEncoder.Properties;

namespace IntelHexEncoder
{
    public class DevToolIntelHexEncoder : DevTool<UserControlIntelHexEncoder>
    {
        public DevToolIntelHexEncoder()
        {
            _menu = Resources.Menu;
            _title = Resources.Title;
        }
    }
}

