using System.Text;

internal class Program
{
    private static int Main(string[] args)
    {
        TextWriter writer;

        if (args.Length == 0)
        {
            writer = Console.Out;
        }
        else if (args.Length == 1)
        {
            string filename = args[0];
            Encoding utf8WithoutBom = new UTF8Encoding(encoderShouldEmitUTF8Identifier: false);
            writer = new StreamWriter(filename, false, utf8WithoutBom);
        }
        else { 
            return -1;
        }

        writer.WriteLine("#pragma once");
        writer.WriteLine();

        for (uint i = 256; i < 1024; i += 256)
        {
            writer.WriteLine(Encoding.UTF8.GetString(Encoding.Default.GetBytes(string.Format("#define B{0:B10}  {0}", i))));
        }
        writer.WriteLine();

        format(writer, "B_{2}_{1}_{0}", 3);

        format(writer, "B_{3}_{2}_{1}_{0}", 4);
        format(writer, "B__{3}__{2}__{1}__{0}", 4);
        format(writer, "B_{3}{2}{1}{0}", 4);
        format(writer, "B_{3}{2}_{1}{0}", 4);

        format(writer, "B_{5}_{4}_{3}{2}{1}{0}", 6);

        format(writer, "B_{6}{5}_{4}_{3}{2}{1}{0}", 7);

        format(writer, "B_{9}_{8}_{7}{6}{5}{4}{3}{2}{1}{0}", 10);

        writer.Flush();
        return 0;
    }
    static uint bitRead(uint data, int bit)
    {
        return data >> bit & 1;
    }
    static void format(TextWriter writer, string format, int bitSize)
    {
        int max = 1 << bitSize;
        object[] param = new object[bitSize];

        for (uint i = 0; i < max; i++)
        {
            for (int n = 0; n < bitSize; n++)
            {
                param[n] = bitRead(i, n);
            }
            string data = string.Format(format, param);
            data = string.Format("#define {0}  {1}", data, i);
            writer.WriteLine(Encoding.UTF8.GetString(Encoding.Default.GetBytes(data)));
        }
        writer.WriteLine();
    }
}