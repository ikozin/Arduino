using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageConverter
{
    public partial class FilterImageCoverter : UserControl
    {
        public FilterImageCoverter()
        {
            InitializeComponent();
        }

        public void SetSize(int width, int height)
        {
            textBoxWidth.Text = width.ToString();
            textBoxHeight.Text = height.ToString();
        }
    }
}
