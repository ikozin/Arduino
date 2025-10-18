using CommonUI;
using GenBinDefs.Properties;

namespace GenBinDefs
{
    public class DevToolGenBinDefs : DevTool<UserControlGenBinDefs>
    {
        public DevToolGenBinDefs()
        {
            _menu = Resources.Menu;
            _title = Resources.Title;
        }
    }
}

