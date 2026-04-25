namespace ProgrTool;

public class LedData(System.Drawing.Color color)
{
    public const int MaxLed = 21;
    public LedData() : this(System.Drawing.Color.Black) { }
    public System.Drawing.Color Color { get; set; } = color;
}
public static class StripTool
{
    public static byte GetR(this System.Drawing.Color color) => color.R;
    public static byte GetG(this System.Drawing.Color color) => color.G;
    public static byte GetB(this System.Drawing.Color color) => color.B;

    public static byte Fade8(this byte x, byte b) { return (byte)(((UInt16)(x) * ((b) + 1)) >> 8); }
    public static byte Fade8R(this System.Drawing.Color color, byte b) { return Fade8(color.GetR(), (b)); }
    public static byte Fade8G(this System.Drawing.Color color, byte b) { return Fade8(color.GetG(), (b)); }
    public static byte Fade8B(this System.Drawing.Color color, byte b) { return Fade8(color.GetB(), (b)); }
    public static System.Drawing.Color GetFade(this System.Drawing.Color data, byte val)
    {
        if (data.ToArgb() == 0) return System.Drawing.Color.Black;
        val = (byte)(255 - val);
        return System.Drawing.Color.FromArgb(data.Fade8R(val), data.Fade8G(val), data.Fade8B(val));
    }
    public static System.Drawing.Color MWheel(int color, byte bright)
    {
        byte r = 0, g = 0, b = 0;
        if (color <= 255)
        {                         // красный макс, зелёный растёт
            r = 255;
            g = (byte)color;
            b = 0;
        }
        else if (color > 255 && color <= 510)
        {   // зелёный макс, падает красный
            r = (byte)(510 - color);
            g = 255;
            b = 0;
        }
        else if (color > 510 && color <= 765)
        {   // зелёный макс, растёт синий
            r = 0;
            g = 255;
            b = (byte)(color - 510);
        }
        else if (color > 765 && color <= 1020)
        {  // синий макс, падает зелёный
            r = 0;
            g = (byte)(1020 - color);
            b = 255;
        }
        else if (color > 1020 && color <= 1275)
        { // синий макс, растёт красный
            r = (byte)(color - 1020);
            g = 0;
            b = 255;
        }
        else if (color > 1275 && color <= 1530)
        { // красный макс, падает синий
            r = 255;
            g = 0;
            b = (byte)(1530 - color);
        }
        if (bright != 255)
        {
            r = r.Fade8(bright);
            g = g.Fade8(bright);
            b = b.Fade8(bright);
        }
        return System.Drawing.Color.FromArgb(r, g, b);
    }
    public static System.Drawing.Color MWheel8(byte color, byte bright)
    {
        byte r, g, b;
        byte shift;
        if (color > 170)
        {
            shift = (byte)((color - 170) * 3);
            r = shift;
            g = 0;
            b = (byte)(255 - shift);
        }
        else if (color > 85)
        {
            shift = (byte)((color - 85) * 3);
            r = 0;
            g = (byte)(255 - shift);
            b = shift;
        }
        else
        {
            shift = (byte)(color * 3);
            r = (byte)(255 - shift);
            g = shift;
            b = 0;
        }
        if (bright != 255)
        {
            r = Fade8(r, bright);
            g = Fade8(g, bright);
            b = Fade8(b, bright);
        }
        return System.Drawing.Color.FromArgb(r, g, b);
    }
    public static System.Drawing.Color GetBlend(int x, int amount, System.Drawing.Color c0, System.Drawing.Color c1)
    {
        while (x >= amount) x -= amount;
        amount -= 1;
        return System.Drawing.Color.FromArgb(
        c0.GetR() + (c1.GetR() - c0.GetR()) * x / amount,
        c0.GetG() + (c1.GetG() - c0.GetG()) * x / amount,
        c0.GetB() + (c1.GetB() - c0.GetB()) * x / amount
        );
    }

    public static T Get<T>() where T : StripBase
    {
        return (Activator.CreateInstance(typeof(T), [(ushort)0, System.Drawing.Color.Black]) as T)!;
    }
    public static T Get<T>(UInt16 delay) where T : StripBase
    {
        return (Activator.CreateInstance(typeof(T), [delay, System.Drawing.Color.Black]) as T)!;
    }
    public static T Get<T>(System.Drawing.Color color) where T : StripBase
    {
        return (Activator.CreateInstance(typeof(T), [(ushort)0, color]) as T)!;
    }
    public static T Get<T>(UInt16 delay, System.Drawing.Color color) where T : StripBase
    {
        return (Activator.CreateInstance(typeof(T), [delay, color]) as T)!;
    }
}
public class StripBase
{
    public UInt16 Delay { get; set; }
}
public class StripFill : StripBase
{
    public const UInt16 Count = 21;
    public StripFill(UInt16 delay, System.Drawing.Color color)
    {
        Delay = delay;
        Led = new LedData(color);
    }
    public LedData Led { get; set; }
    public void Clear()
    {
        Delay = 0;
        Led = new LedData();
    }
    public void Save(BinaryWriter writer)
    {
        if (Delay == 0)
        {
            writer.Write((byte)0x00);
        }
        else
        {
            writer.Write((byte)0x80);
            writer.Write(Delay);
        }
        writer.Write(Led.Color.R);
        writer.Write(Led.Color.G);
        writer.Write(Led.Color.B);
    }
}
public class StripCount : StripBase
{
    public StripCount(UInt16 delay, System.Drawing.Color color)
    {
        Delay = delay;
        Led = new LedData(color);
        Indexies = [];
    }
    public LedData Led { get; set; }
    public List<byte> Indexies { get; private set; }
    public StripCount IndexiesAdd(IEnumerable<byte> list)
    {
        Indexies.AddRange(list);
        return this;
    }
    public StripCount IndexiesClear()
    {
        Indexies.Clear();
        return this;
    }
    public void Clear()
    {
        Delay = 0;
        Led = new LedData();
        Indexies.Clear();
    }
    public void Save(BinaryWriter writer)
    {
        if (Delay == 0)
        {
            writer.Write((byte)0x01);
        }
        else
        {
            writer.Write((byte)0x81);
            writer.Write(Delay);
        }
        writer.Write(Led.Color.R);
        writer.Write(Led.Color.G);
        writer.Write(Led.Color.B);
        writer.Write((byte)Indexies.Count);
        foreach (int i in Indexies)
        {
            writer.Write((byte)i);
        }
    }
}
public class StripRaw : StripBase
{
    public StripRaw(UInt16 delay, System.Drawing.Color color)
    {
        Delay = delay;
        Leds = new LedData[LedData.MaxLed];
        for (int i = 0; i < Leds.Length; i++)
        {
            Leds[i] = new LedData(color);
        }
    }
    public LedData[] Leds { get; private set; }
    public StripRaw Set(System.Drawing.Color color, int[] indexies)
    {
        foreach (int i in indexies)
        {
            Leds[i].Color = color;
        }
        return this;
    }
    public void Save(BinaryWriter writer)
    {
        if (Delay == 0)
        {
            writer.Write((byte)0x02);
        }
        else
        {
            writer.Write((byte)0x82);
            writer.Write(Delay);
        }
        for (int i = 0; i < Leds.Length; i++)
        {
            LedData led = Leds[i];
            writer.Write(led.Color.R);
            writer.Write(led.Color.G);
            writer.Write(led.Color.B);
        }
    }
}
public class StripGradient
{
    public StripGradient(int size) => Colors = new System.Drawing.Color[size];
    public System.Drawing.Color[] Colors { get; private set; }
    public System.Drawing.Color Get(int x, int amount)
    {
        int sectorSize = (amount + Colors.Length - 2) / (Colors.Length - 1); // (x+y-1)/y
        int sector = x / sectorSize;
        return StripTool.GetBlend(x - sector * sectorSize, sectorSize, Colors[sector], Colors[sector + 1]);
    }
}
