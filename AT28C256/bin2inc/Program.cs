using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bin2inc
{
    class Program
    {
        private const int MaxLineCount = 16;
        static void Main(string[] args)
        {
            if (args.Length != 3)
            {
                displayHelp();
                return;
            }
            var arrayName = args[0];
            var binFile = args[1];
            var incFile = args[2];
            try
            {
                StringBuilder text = new StringBuilder(32768);
                var data = File.ReadAllBytes(binFile);
                text.AppendLine(String.Format("const uint8_t {0}[{1}]  PROGMEM =", arrayName, data.Length));
                text.AppendLine("{");
                for (int i = 0; i < data.Length; i++)
                {
                    text.AppendFormat("0x{0:X2}, ", data[i]);
                    if (i % MaxLineCount == MaxLineCount - 1)
                    {
                        text.AppendLine();
                    }
                }
                text.AppendLine("};");
                File.WriteAllText(incFile, text.ToString());
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static void displayHelp()
        {

        }
    }
}
