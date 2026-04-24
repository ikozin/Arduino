using System;
using System.Drawing;

namespace ProgrTool;
/*

                 (11)
                 
               (10)(12)
       
(07)  (08)  (09)      (13)  (14)  (15)
    (06)                      (16)
                 (00)
           (05)        (17)
                 
                 (01)
         (04)            (18)
            (02)     (20)
      (03)                  (19) 

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

        StripFill fill;
        StripCount count;

        using FileStream file = File.Create("AT24LC512.bin");
        using BinaryWriter writer = new(file);

        //SetLight(writer, Color.Red, star_ring_0, new(1000));
        //SetLight(writer, Color.Red, star_ring_1, new(1000));
        //SetLight(writer, Color.Red, star_ring_2, new(1000));
        //SetLight(writer, Color.Red, star_ring_3, new(1000));
        //SetLight(writer, Color.Black, star_ring_0, data);
        //SetLight(writer, Color.Black, star_ring_1, data);
        //SetLight(writer, Color.Black, star_ring_2, data);
        //SetLight(writer, Color.Black, star_ring_3, data);

        //RunningLight(writer, Color.Magenta, star_ring_1, new StripData(200));
        //RunningLight(writer, Color.Magenta, star_ring_2, new StripData(200));
        //RunningLight(writer, Color.Magenta, star_ring_3, new StripData(200));

        (new StripFill(000, Color.Red)).Save(writer);

        count = new StripCount(100, Color.Magenta);
        count.Indexies.AddRange(star_ring_0);
        count.Save(writer);

        count = new StripCount(Color.Red);
        count.Indexies.AddRange(star_ring_0);
        count.Save(writer);
        count = new StripCount(100, Color.Magenta);
        count.Indexies.AddRange(star_ring_1);
        count.Save(writer);

        count = new StripCount(Color.Red);
        count.Indexies.AddRange(star_ring_1);
        count.Save(writer);
        count = new StripCount(100, Color.Magenta);
        count.Indexies.AddRange(star_ring_2);
        count.Save(writer);

        count = new StripCount(Color.Red);
        count.Indexies.AddRange(star_ring_2);
        count.Save(writer);
        count = new StripCount(100, Color.Magenta);
        count.Indexies.AddRange(star_ring_3);
        count.Save(writer);

        count = new StripCount(Color.Red);
        count.Indexies.AddRange(star_ring_3);
        count.Save(writer);
        count = new StripCount(100, Color.Magenta);
        count.Indexies.AddRange(star_ring_2);
        count.Save(writer);

        count = new StripCount(Color.Red);
        count.Indexies.AddRange(star_ring_2);
        count.Save(writer);
        count = new StripCount(100, Color.Magenta);
        count.Indexies.AddRange(star_ring_1);
        count.Save(writer);

        count = new StripCount(Color.Red);
        count.Indexies.AddRange(star_ring_1);
        count.Save(writer);
        count = new StripCount(100, Color.Magenta);
        count.Indexies.AddRange(star_ring_0);
        count.Save(writer);


        //count = new StripCount(100, Color.Green);
        //count.Indexies.AddRange(star_ring_0);
        //count.Save(writer);

        //count = new StripCount(100, Color.Green);
        //count.Indexies.AddRange(star_ring_1);
        //count.Save(writer);

        //count = new StripCount(100, Color.Green);
        //count.Indexies.AddRange(star_ring_2);
        //count.Save(writer);

        //count = new StripCount(100, Color.Green);
        //count.Indexies.AddRange(star_ring_3);
        //count.Save(writer);

        //count = new StripCount(100, Color.Red);
        //count.Indexies.AddRange(star_ring_0);
        //count.Save(writer);

        //count = new StripCount(100, Color.Red);
        //count.Indexies.AddRange(star_ring_1);
        //count.Save(writer);

        //count = new StripCount(100, Color.Red);
        //count.Indexies.AddRange(star_ring_2);
        //count.Save(writer);

        //count = new StripCount(100, Color.Red);
        //count.Indexies.AddRange(star_ring_3);
        //count.Save(writer);

        file.Close();
        Console.WriteLine("Finish");
    }
}