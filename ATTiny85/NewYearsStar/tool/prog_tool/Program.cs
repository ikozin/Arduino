using System;
using System.Drawing;

namespace ProgrTool;

internal class Program
{

    public static void Main(string[] args)
    {
        Console.WriteLine("Srart");

        using FileStream file = File.Create("AT24LC512.bin");
        using BinaryWriter writer = new BinaryWriter(file);
        RunningLight(writer, 200, Color.Red);
        RunningLight(writer, 200, Color.Green);
        RunningLight(writer, 200, Color.Blue);
        file.Close();
    }

    private static void RunningLight(BinaryWriter writer, UInt16 delay, Color color)
    {
        StripData data = new StripData();
        for (int i = 0; i < data.Count; i++) {
            data.Clear();
            data.Delay = delay;
            data.Leds[i].Color = color;
            data.Save(writer);
        }
        return;
    }
}