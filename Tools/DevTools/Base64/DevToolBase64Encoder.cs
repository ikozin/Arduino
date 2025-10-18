using Base64Encoder.Properties;
using CommonUI;

namespace Base64Encoder
{
    public class DevToolBase64Encoder : DevTool<UserControlBase64Encoder>
    {
        public DevToolBase64Encoder()
        {
            _menu = Resources.Menu;
            _title = Resources.Title;
        }
    }
}

