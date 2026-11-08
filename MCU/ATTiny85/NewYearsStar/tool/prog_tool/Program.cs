using System.Linq;
using System.Drawing;

namespace prog_tool;
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
    public static byte[] star_ring_0 = [0];                                 // 1    (1+3+1) = 5
    public static byte[] star_ring_1 = [1, 5, 9, 13, 17];                   // 5    (1+3+5) = 8
    public static byte[] star_ring_2 = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20];// 10   (1+3+10) = 14
    public static byte[] star_ring_3 = [3, 7, 11, 15, 19];                  // 5    (1+3+5) = 8

    public static byte[] ray_0 = [0, 1, 17, 18, 19, 20];
    public static byte[] ray_1 = [0, 1, 2, 3, 4, 5];
    public static byte[] ray_2 = [0, 5, 6, 7, 8, 9];
    public static byte[] ray_3 = [0, 9, 10, 11, 12, 13];
    public static byte[] ray_4 = [0, 13, 14, 15, 16, 17];

    public enum MemoryChip: int
    {
        AT24LC32 = 4096,
        AT24LC64 = 8192,
        AT24LC128 = 16384,
        AT24LC256 = 32768,
        AT24LC512 = 65536
    }

    public static void Main()
    {
        int size = (int)MemoryChip.AT24LC512;
        var buffer = new byte[size];
        Console.WriteLine("Srart");
        using MemoryStream ms = new(buffer);
        for (int i = 0; i < size; i++) ms.WriteByte(0xFF);
        ms.Position = 0;
        using BinaryWriter writer = new(ms);

        WaveOut(writer, 150, Color.Red, Color.Magenta);
        WaveOut(writer, 150, Color.Red, Color.Magenta);
        Wave(writer, 150, Color.Red, Color.Magenta);
        WaveIn(writer, 150, Color.Red, Color.Magenta);
        WaveIn(writer, 150, Color.Red, Color.Magenta);

        StripTool.Get<StripFill>(1000, Color.Black).Save(writer);

        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 7, 11, 15, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([4, 8, 12, 16, 20]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([5, 9, 13, 17, 1]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([6, 10, 14, 18, 2]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 7, 11, 15, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([4, 8, 12, 16, 20]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([5, 9, 13, 17, 1]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([6, 10, 14, 18, 2]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 7, 11, 15, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([4, 8, 12, 16, 20]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([5, 9, 13, 17, 1]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([6, 10, 14, 18, 2]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 7, 11, 15, 19]).SetBack(Color.Red).Save(writer);

        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 7, 11, 15, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([2, 6, 10, 14, 18]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([1, 5, 9, 13, 17]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([20, 4, 8, 12, 16]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 7, 11, 15, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([2, 6, 10, 14, 18]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([1, 5, 9, 13, 17]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([20, 4, 8, 12, 16]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 7, 11, 15, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([2, 6, 10, 14, 18]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([1, 5, 9, 13, 17]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([20, 4, 8, 12, 16]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 7, 11, 15, 19]).SetBack(Color.Red).Save(writer);


        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([1, 2, 3]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 4, 5]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([5, 6, 7]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([7, 8, 9]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([9, 10, 11]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([11, 12, 13]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([13, 14, 15]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([15, 16, 17]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([17, 18, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([19, 20, 1]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([1, 2, 3]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 4, 5]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([5, 6, 7]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([7, 8, 9]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([9, 10, 11]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([11, 12, 13]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([13, 14, 15]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([15, 16, 17]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([17, 18, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([19, 20, 1]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([1, 2, 3]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([3, 4, 5]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([5, 6, 7]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([7, 8, 9]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([9, 10, 11]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([11, 12, 13]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([13, 14, 15]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([15, 16, 17]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([17, 18, 19]).SetBack(Color.Red).Save(writer);
        StripTool.Get<StripFillCount>(150, Color.Magenta).IndicesAdd([19, 20, 1]).SetBack(Color.Red).Save(writer);


        StripTool.Get<StripFill>(1000, Color.Black).Save(writer);

        WaveGradient(writer, 100, Color.Red, [Color.White, Color.Yellow]);
        StripTool.Get<StripFill>(100, Color.Red).Save(writer);
        WaveGradient(writer, 100, Color.Red, [Color.Yellow, Color.White, Color.Yellow]);
        StripTool.Get<StripFill>(100, Color.Red).Save(writer);
        WaveGradient(writer, 100, Color.Red, [Color.Yellow, Color.White, Color.Yellow, Color.White]);
        StripTool.Get<StripFill>(100, Color.Red).Save(writer);
        WaveGradient(writer, 100, Color.Red, [Color.Yellow, Color.Green, Color.White, Color.Blue, Color.Yellow]);
        StripTool.Get<StripFill>(100, Color.Red).Save(writer);

        WaveGradient(writer, 100, Color.Red, [Color.White, Color.Yellow]);
        StripTool.Get<StripFill>(100, Color.Red).Save(writer);
        WaveGradient(writer, 100, Color.Red, [Color.Yellow, Color.White, Color.Yellow]);
        StripTool.Get<StripFill>(100, Color.Red).Save(writer);
        WaveGradient(writer, 100, Color.Red, [Color.Yellow, Color.White, Color.Yellow, Color.White]);
        StripTool.Get<StripFill>(100, Color.Red).Save(writer);
        WaveGradient(writer, 100, Color.Red, [
            Color.FromArgb(255, 255, 141, 0),
            Color.FromArgb(255, 255, 255, 0),
            Color.FromArgb(255, 255, 255, 141),
            Color.FromArgb(255, 255, 255, 255),
            Color.FromArgb(255, 255, 255, 141),
            Color.FromArgb(255, 255, 255, 0),
            Color.FromArgb(255, 255, 141, 0),
            ]);
        StripTool.Get<StripFill>(100, Color.Red).Save(writer);

        StripTool.Get<StripFill>(1000, Color.Black).Save(writer);

        StripTool.Get<StripRaw>(100, Color.Black).Set(Color.Blue, star_ring_0).Set(Color.Blue, star_ring_2).Save(writer);
        StripTool.Get<StripRaw>(100, Color.Black).Set(Color.Blue, star_ring_1).Set(Color.Blue, star_ring_3).Save(writer);
        StripTool.Get<StripRaw>(100, Color.Black).Set(Color.Blue, star_ring_0).Set(Color.Blue, star_ring_2).Save(writer);
        StripTool.Get<StripRaw>(100, Color.Black).Set(Color.Blue, star_ring_1).Set(Color.Blue, star_ring_3).Save(writer);
        StripTool.Get<StripRaw>(100, Color.Black).Set(Color.Blue, star_ring_0).Set(Color.Blue, star_ring_2).Save(writer);
        StripTool.Get<StripRaw>(100, Color.Black).Set(Color.Blue, star_ring_1).Set(Color.Blue, star_ring_3).Save(writer);


        //StripTool.Get<StripFill>(1000, Color.Black).Save(writer);

        for (int i = 0; i < 256; i++)
        {
            StripTool.Get<StripFill>(1, Color.FromArgb(255, i, i, 0)).Save(writer);
        }
        //StripTool.Get<StripFill>(500, Color.FromArgb(255, 255, 255, 0)).Save(writer);

        StripTool.Get<StripFill>(1000, Color.Black).Save(writer);

        for (int i = 0; i < 128; i += 16)
        {
            StripTool.Get<StripFill>(1000, Color.FromArgb(0, 255, 255 - i, 0)).Save(writer);
        }

        StripTool.Get<StripFill>(1000, Color.Black).Save(writer);
        StripTool.Get<StripFill>(1000, Color.Orange).Save(writer);


        using (FileStream file = File.Create("AT24LC512.bin"))
        {
            ms.CopyTo(file);
        }
        Console.WriteLine("Finish");
    }
    public static void Wave(BinaryWriter writer, ushort delay, Color back, Color front)
    {
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_0).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_1).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_2).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_3).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_2).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_1).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_0).SetBack(back).Save(writer);
    }
    public static void WaveOut(BinaryWriter writer, ushort delay, Color back, Color front)
    {
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_0).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_1).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_2).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_3).SetBack(back).Save(writer);
    }
    public static void WaveIn(BinaryWriter writer, ushort delay, Color back, Color front)
    {
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_3).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_2).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_1).SetBack(back).Save(writer);
        StripTool.Get<StripFillCount>(delay, front).IndicesAdd(star_ring_0).SetBack(back).Save(writer);
    }
    public static void WaveGradient(BinaryWriter writer, ushort delay, Color back, Color[] gradient)
    {
        List<StripBase> list = [];
        byte[][] rings = [star_ring_0, star_ring_1, star_ring_2, star_ring_3];
        var gradIdx = gradient.Index().Select(v => v.Index).ToArray();
        var ringIdx = rings.Index().Select(v => v.Index).ToArray();


        if (gradient.Length <= rings.Length)
        {
            for (int i = 1; i <= gradient.Length; i++)
            {
                var l1 = gradIdx.Skip(0).Take(i);
                var l2 = ringIdx.Skip(0).Take(i).Reverse();
                var l3 = l1.Zip(l2).ToList();
                list.Add(StripTool.Get<StripFill>(back));
                l3.ForEach(v =>
                {
                    //Console.WriteLine("grad[{0}], rings[{1}]", v.First, v.Second);
                    list.Add(StripTool.Get<StripCount>(gradient[v.First]).IndicesAdd(rings[v.Second]));
                });
                list.Last().Delay = delay;
                //Console.WriteLine();
            }
            //Console.WriteLine();
            for (int i = 1; i <= rings.Length - gradient.Length; i++)
            {
                var l1 = gradIdx.Skip(0).Take(gradient.Length);
                var l2 = ringIdx.Skip(i).Take(gradient.Length).Reverse();
                var l3 = l1.Zip(l2).ToList();
                list.Add(StripTool.Get<StripFill>(back));
                l3.ForEach(v =>
                {
                    //Console.WriteLine("grad[{0}], rings[{1}]", v.First, v.Second);
                    list.Add(StripTool.Get<StripCount>(gradient[v.First]).IndicesAdd(rings[v.Second]));
                });
                list.Last().Delay = delay;
                //Console.WriteLine();
            }
            //Console.WriteLine();
            for (int i = 1; i < gradient.Length; i++)
            {
                var l1 = gradIdx.Skip(i);
                var l2 = ringIdx.Skip(rings.Length - l1.Count()).Take(l1.Count()).Reverse();
                var l3 = l1.Zip(l2).ToList();
                list.Add(StripTool.Get<StripFill>(back));
                l3.ForEach(v =>
                {
                    //Console.WriteLine("grad[{0}], rings[{1}]", v.First, v.Second);
                    list.Add(StripTool.Get<StripCount>(gradient[v.First]).IndicesAdd(rings[v.Second]));
                });
                list.Last().Delay = delay;
                //Console.WriteLine();
            }
            //Console.WriteLine();
        }
        else {
            for (int i = 1; i <= gradient.Length; i++)
            {
                var l1 = gradIdx.Skip(0).Take(i);
                var l2 = ringIdx.Skip(0).Take(i).Reverse();
                var l3 = l1.Zip(l2).ToList();
                list.Add(StripTool.Get<StripFill>(back));
                l3.ForEach(v =>
                {
                    //Console.WriteLine("grad[{0}], rings[{1}]", v.First, v.Second);
                    list.Add(StripTool.Get<StripCount>(gradient[v.First]).IndicesAdd(rings[v.Second]));
                });
                list.Last().Delay = delay;
                //Console.WriteLine();
            }
            //Console.WriteLine();
            for (int i = 1; i <= gradient.Length - ringIdx.Length; i++)
            {
                var l1 = gradIdx.Skip(i).Take(ringIdx.Length);
                var l2 = ringIdx.Skip(0).Take(ringIdx.Length).Reverse();
                var l3 = l1.Zip(l2).ToList();
                list.Add(StripTool.Get<StripFill>(back));
                l3.ForEach(v =>
                {
                    //Console.WriteLine("grad[{0}], rings[{1}]", v.First, v.Second);
                    list.Add(StripTool.Get<StripCount>(gradient[v.First]).IndicesAdd(rings[v.Second]));
                });
                list.Last().Delay = delay;
                //Console.WriteLine();
            }
            //Console.WriteLine();
            for (int i = 1; i <= ringIdx.Length; i++)
            {
                var l1 = gradIdx.Skip(i).Take(ringIdx.Length);
                var l2 = ringIdx.Skip(0).Take(ringIdx.Length).Reverse();
                var l3 = l1.Zip(l2).ToList();
                list.Add(StripTool.Get<StripFill>(back));
                l3.ForEach(v =>
                {
                    //Console.WriteLine("grad[{0}], rings[{1}]", v.First, v.Second);
                    list.Add(StripTool.Get<StripCount>(gradient[v.First]).IndicesAdd(rings[v.Second]));
                });
                list.Last().Delay = delay;
                //Console.WriteLine();
            }
        }
        list.ForEach(i => i.Save(writer));
    }
}
