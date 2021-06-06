using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;

namespace radioeditor
{
    public class Record
    {
        public short Freq { get; set; }
        public string Name { get; set; }
    }
    public enum ConverterType: int
    {
        JSON    = 1,
        DAT     = 2,
    };

    class Program
    {
        public const int MaxListSize = 64;
        public const int MaxNameSize = 78;
        static void Main(string[] args)
        {
            (var type, var fileJson, var fileList) = ParseArgs(args);

            switch (type)
            {
                case ConverterType.JSON:
                    ConverterJson(fileJson, fileList);
                    return;
                case ConverterType.DAT:
                    ConverterDat(fileList, fileJson);
                    return;
            }
            Console.WriteLine("Параметры запуска\r\n  /i:radiolist.dat /o:radiolist.json\r\n  /i:radiolist.json /o:radiolist.dat\r\n");
        }
        private static (ConverterType? type, string fileJson, string fileDat) ParseArgs(string[] args)
        {
            ConverterType? type = null;
            string fileJson = null;
            string fileList = null;

            foreach (var item in args)
            {
                if (item.StartsWith("/i:"))
                {
                    string fileName = item.Remove(0, 3).Trim();
                    string fileExt = Path.GetExtension(fileName);
                    if (fileExt == ".json")
                    {
                        type = ConverterType.JSON;
                        fileJson = fileName;
                    }
                    if (fileExt == ".dat")
                    {
                        type = ConverterType.DAT;
                        fileList = fileName;
                    }
                }
                if (item.StartsWith("/o:"))
                {
                    string fileName = item.Remove(0, 3).Trim();
                    string fileExt = Path.GetExtension(fileName);
                    if (fileExt == ".json") fileJson = fileName;
                    if (fileExt == ".dat") fileList = fileName;
                }
            }
            return (type, fileJson, fileList);
        }
        private static void ConverterDat(string fileList, string fileJson)
        {
            List<Record> list = new ();
            using FileStream stream = File.OpenRead(fileList);
            using BinaryReader reader = new(stream);
            try
            {
                while (true)
                {
                    Record rec = new();
                    rec.Freq = reader.ReadInt16();
                    rec.Name = Encoding.UTF8.GetString(reader.ReadBytes(MaxNameSize)).TrimEnd('\0');

                    if (rec.Freq == 0) break;
                    list.Add(rec);
                    Console.WriteLine("{0}, {1}", rec.Freq, rec.Name);
                }
            }
            catch (EndOfStreamException)
            {
            }

            var options = new JsonSerializerOptions
            {
                AllowTrailingCommas = true,
                Encoder = JavaScriptEncoder.Create(UnicodeRanges.BasicLatin, UnicodeRanges.Cyrillic),
                WriteIndented = true,
            };
            var data = JsonSerializer.SerializeToUtf8Bytes(list, options);
            File.WriteAllBytes(fileJson, data);
        }
        private static void ConverterJson(string fileJson, string fileList)
        {
            var options = new JsonSerializerOptions
            {
                AllowTrailingCommas = true,
                Encoder = JavaScriptEncoder.Create(UnicodeRanges.BasicLatin, UnicodeRanges.Cyrillic),
                WriteIndented = true,
            };
            var text = File.ReadAllText(fileJson);
            var list = JsonSerializer.Deserialize<List<Record>>(text, options);
            int count = Math.Min(list.Count, MaxListSize);
            byte[] buffer = new byte[MaxNameSize];
            using FileStream stream = File.OpenWrite(fileList);
            using BinaryWriter writer = new(stream);
            for (int i = 0; i < count; i++)
            {
                var rec = list[i];
                Console.WriteLine("{0}, {1}", rec.Freq, rec.Name);
                writer.Write(rec.Freq);
                Array.Clear(buffer, 0, buffer.Length);
                var data = Encoding.UTF8.GetBytes(rec.Name);
                int size = Math.Min(data.Length, MaxNameSize - 1);
                Array.Copy(data, buffer, size);
                writer.Write(buffer);
            }
            buffer = new byte[MaxNameSize + 2];
            Array.Clear(buffer, 0, buffer.Length);
            while (count++ < MaxListSize)
            {
                writer.Write(buffer);
            }
        }
    }
}
