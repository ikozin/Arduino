using System;
using System.Drawing;

namespace ProgrTool;
/*

                 ( 7)
                 
               ( 6)( 8)
       
( 3)  ( 4)  ( 5)      ( 9)  (10)  (11)
    ( 2)                      (12)
                 ( 0)
           ( 1)        (13)
                 
                 (17)
         (20)            (14)
            (18)    (16)
      (19)                  (15) 

*/

internal class Program
{
    public static byte[] star_all = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20];
    public static byte[] star_ring_0 = [0];
    public static byte[] star_ring_1 = [1, 5, 9, 13, 17];
    public static byte[] star_ring_2 = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20];
    public static byte[] star_ring_3 = [3, 7, 11, 15, 19];


    public static void Main(string[] args)
    {
        Console.WriteLine("Srart");

        using FileStream file = File.Create("AT24LC512.bin");
        using BinaryWriter writer = new(file);

        SetLight(writer, Color.Red, star_ring_0, new StripData(200));
        SetLight(writer, Color.Red, star_ring_1, new StripData(200));
        SetLight(writer, Color.Red, star_ring_2, new StripData(200));
        SetLight(writer, Color.Red, star_ring_3, new StripData(200));
        SetLight(writer, Color.Black, star_all, new StripData(200));

        RunningLight(writer, Color.Magenta, star_ring_1, new StripData(200));
        RunningLight(writer, Color.Magenta, star_ring_2, new StripData(200));
        RunningLight(writer, Color.Magenta, star_ring_3, new StripData(200));

        SetLight(writer, Color.Black, star_all, new StripData(0));

        file.Close();
    }

    private static void SetLight(BinaryWriter writer, Color color, byte[] raw, StripData data)
    {
        for (int i = 0; i < raw.Length; i++) {
            data.Leds[raw[i]].Color = color;
        }
        data.Save(writer);
    }

    private static void RunningLight(BinaryWriter writer, Color color, byte[] raw, StripData data)
    {
        UInt16 delay = data.Delay;
        for (int i = 0; i < raw.Length; i++) {
            data.Clear();
            data.Delay = delay;
            data.Leds[raw[i]].Color = color;
            data.Save(writer);
        }
    }
}