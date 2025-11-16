using CommonUI;
using FontCostructor.Properties;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace FontCostructor
{
    public class DevToolFontCostructor : DevTool<UserControlFontCostructor>
    {
        public DevToolFontCostructor()
        {
            _menu = Resources.Menu;
            _title = Resources.Title;
        }
    }
}
