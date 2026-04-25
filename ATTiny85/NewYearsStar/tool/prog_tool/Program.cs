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

    public static byte[] ray_0 = [0, 1, 17, 18, 19, 20];
    public static byte[] ray_1 = [0, 1, 2, 3, 4, 5];
    public static byte[] ray_2 = [0, 5, 6, 7, 8, 9];
    public static byte[] ray_3 = [0, 9, 10, 11, 12, 13];
    public static byte[] ray_4 = [0, 13, 14, 15, 16, 17];


    public static void Main(string[] args)
    {
        Console.WriteLine("Srart");

        using FileStream file = File.Create("AT24LC512.bin");
        using BinaryWriter writer = new(file);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(star_ring_0).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(star_ring_1).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(star_ring_2).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(star_ring_2).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(star_ring_1).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(star_ring_0).Save(writer);

        StripTool.Get<StripRaw>(500, Color.Black).Save(writer);
        StripTool.Get<StripRaw>(500, Color.WhiteSmoke).Save(writer);
        StripTool.Get<StripRaw>(500, Color.DarkMagenta).Save(writer);
        StripTool.Get<StripRaw>(500, Color.Black).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_0).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_1).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_2).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_4).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_2).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_1).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, Color.Magenta).IndexiesAdd(ray_0).Save(writer);

        StripGradient gradient = new StripGradient(3);
        gradient.Colors[0] = Color.Red;
        gradient.Colors[1] = Color.Yellow;
        gradient.Colors[1] = Color.White;

        StripTool.Get<StripRaw>(500, Color.Black).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(0, 5)).IndexiesAdd(star_ring_0).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(1, 5)).IndexiesAdd(star_ring_0).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(0, 5)).IndexiesAdd(star_ring_1).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(2, 5)).IndexiesAdd(star_ring_0).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(1, 5)).IndexiesAdd(star_ring_1).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(0, 5)).IndexiesAdd(star_ring_2).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(3, 5)).IndexiesAdd(star_ring_0).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(2, 5)).IndexiesAdd(star_ring_1).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(1, 5)).IndexiesAdd(star_ring_2).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(0, 5)).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(4, 5)).IndexiesAdd(star_ring_0).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(3, 5)).IndexiesAdd(star_ring_1).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(2, 5)).IndexiesAdd(star_ring_2).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(1, 5)).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(3, 5)).IndexiesAdd(star_ring_0).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(4, 5)).IndexiesAdd(star_ring_1).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(3, 5)).IndexiesAdd(star_ring_2).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(2, 5)).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(2, 5)).IndexiesAdd(star_ring_0).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(3, 5)).IndexiesAdd(star_ring_1).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(4, 5)).IndexiesAdd(star_ring_2).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(3, 5)).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(1, 5)).IndexiesAdd(star_ring_0).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(2, 5)).IndexiesAdd(star_ring_1).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(3, 5)).IndexiesAdd(star_ring_2).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(4, 5)).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(0, 5)).IndexiesAdd(star_ring_0).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(1, 5)).IndexiesAdd(star_ring_1).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(2, 5)).IndexiesAdd(star_ring_2).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(3, 5)).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(0, 5)).IndexiesAdd(star_ring_1).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(1, 5)).IndexiesAdd(star_ring_2).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(2, 5)).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(gradient.Get(0, 5)).IndexiesAdd(star_ring_2).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(1, 5)).IndexiesAdd(star_ring_3).Save(writer);

        StripTool.Get<StripFill>(Color.Red).Save(writer);
        StripTool.Get<StripCount>(100, gradient.Get(0, 5)).IndexiesAdd(star_ring_3).Save(writer);

        file.Close();
        Console.WriteLine("Finish");
    }
}