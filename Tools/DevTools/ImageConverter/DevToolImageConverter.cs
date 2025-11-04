using CommonUI;
using ImageConverter.Properties;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

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
