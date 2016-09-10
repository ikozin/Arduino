using System;
using System.IO;
using System.IO.Ports;
using System.Resources;
using System.Text;
using System.Windows.Forms;

namespace BT
{
    public partial class BtMainForm : Form
    {
        private readonly byte[] _data = new byte[1024];

        public BtMainForm()
        {
            InitializeComponent();
            comboBoxBaudRate.SelectedIndex = 6;
            btnRefreshComList_Click(null, null);
            SetEnableControls();
        }

        private void btnRefreshComList_Click(object sender, EventArgs e)
        {
            comboBoxComList.Items.Clear();
            comboBoxComList.Items.AddRange(SerialPort.GetPortNames());
            if (comboBoxComList.Items.Count > 0) comboBoxComList.SelectedIndex = comboBoxComList.Items.Count - 1;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                if (!serialPort.IsOpen)
                {
                    serialPort.PortName = comboBoxComList.SelectedItem.ToString();
                    serialPort.BaudRate = int.Parse(comboBoxBaudRate.SelectedItem.ToString());
                    serialPort.Open();
                    btnConnect.Text = @"Отключится";
                }
                else
                {
                    serialPort.Close();
                    btnConnect.Text = @"Подключиться";
                }
            }
            catch (Exception ex)
            {
                ShowError(ex.ToString());
            }
            SetEnableControls();
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            try
            {
                string text = textBoxSend.Text;
                if (checkBoxNewLine.Checked) text += Environment.NewLine;
                byte[] data = Encoding.ASCII.GetBytes(text);
                serialPort.Write(data, 0, data.Length);
                //textBoxData.Text += text;
            }
            catch (Exception ex)
            {
                ShowError(ex.ToString());
            }
        }

        private void SetEnableControls()
        {
            btnRefreshComList.Enabled = !serialPort.IsOpen;
            comboBoxComList.Enabled = !serialPort.IsOpen;
            comboBoxBaudRate.Enabled = !serialPort.IsOpen;

            textBoxData.Enabled = serialPort.IsOpen;
            textBoxSend.Enabled = serialPort.IsOpen;
            checkBoxNewLine.Enabled = serialPort.IsOpen;
            btnSend.Enabled = serialPort.IsOpen;
        }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int len = serialPort.Read(_data, 0, _data.Length);
            string text = Encoding.ASCII.GetString(_data, 0, len);
            Invoke(new Action<string>(SetDataText), text);
        }

        private void serialPort_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            Invoke(new Action<string>(ShowError), e.ToString());
        }

        private void SetDataText(string text)
        {
            textBoxData.Text += text;
            textBoxData.SelectionStart = textBoxData.Text.Length;
            textBoxData.ScrollToCaret();
        }

        private void ShowError(string message)
        {
            MessageBox.Show(this, message, "");
        }

        private void copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (textBoxData.SelectionLength > 0) textBoxData.Copy();
        }

        private void cutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (textBoxData.SelectionLength > 0) textBoxData.Cut();
        }

        private void pasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Clipboard.GetDataObject().GetDataPresent(DataFormats.Text + Environment.NewLine))
                textBoxData.Paste();
        }

        private void selectAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBoxData.SelectAll();
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBoxData.Clear();
        }

        private void toolStripMenuItem_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem menu = (ToolStripMenuItem) sender;
            textBoxSend.Text = menu.Text;
            btnSend.PerformClick();
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            string[] resNames = GetType().Assembly.GetManifestResourceNames();
            using (Stream stream = GetType().Assembly.GetManifestResourceStream("BT.HC-05.pdf"))
            using (FileStream file = File.OpenWrite("BT.HC-05.pdf"))
            {
                byte[] data = new byte[stream.Length];
                stream.Read(data, 0, data.Length);
                file.Write(data, 0, data.Length);
            }
            System.Diagnostics.Process.Start("BT.HC-05.pdf");
        }
    }
}