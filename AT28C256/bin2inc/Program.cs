using System;
using System.IO;
using System.Linq;
using System.Text;

namespace bin2inc
{
    class Program
    {
        private const int MaxLineCount = 16;
        static void Main(string[] args)
        {
            try
            {
                switch (args.Length)
                {
                    case 3:
                    {
                        var arrayName = args[0];
                        var binFile = args[1];
                        var incFile = args[2];
                        var data = File.ReadAllBytes(binFile);
                        GenerateIncludeFile(arrayName, data, incFile);
                        break;
                    }
                    case 4:
                    {
                        var sParam = args[0];
                        var fParam = args[1];
                        var arrayName = args[2];
                        var incFile = args[3];
                        int size;
                        int data = 0;
                        if (!GetIntParam(sParam, "/S:", out size) || !GetIntParam(fParam, "/F:", out data))
                        {
                            displayHelp();
                            return;
                        }
                        byte[] dataArray = Enumerable.Repeat((byte)data, size).ToArray();
                        GenerateIncludeFile(arrayName, dataArray, incFile);
                        break;
                    }
                    default:
                    {
                        displayHelp();
                        return;
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        static bool GetIntParam(string param, string prefix, out int value)
        {
            value = 0;
            if (!param.StartsWith(prefix))
            {
                return false;
            }
            param = param.Remove(0, prefix.Length);
            return int.TryParse(param, out value);
        }

        static void GenerateIncludeFile(string arrayName, byte[] dataArray, string includeFile)
        {
            StringBuilder text = new StringBuilder(32768);
            text.AppendLine(String.Format("const uint8_t {0}[{1}]  PROGMEM =", arrayName, dataArray.Length));
            text.AppendLine("{");
            for (int i = 0; i < dataArray.Length; i++)
            {
                text.AppendFormat("0x{0:X2}, ", dataArray[i]);
                if (i % MaxLineCount == MaxLineCount - 1)
                {
                    text.AppendLine();
                }
            }
            text.AppendLine("};");
            File.WriteAllText(includeFile, text.ToString());
        }

        static void displayHelp()
        {
            Console.WriteLine("bin2inc <array_name> <input_binary_path> <output_header_path>");
            Console.WriteLine("bin2inc /S:<size> /F:<padding_byte> <array_name> <output_header_path>");
        }
    }
}
