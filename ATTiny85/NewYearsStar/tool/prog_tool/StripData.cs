using System.Drawing;

namespace ProgrTool;

public class LedData
{
    public LedData(System.Drawing.Color color) => Color = color;
    public LedData(): this(System.Drawing.Color.Black) {}
    
    public System.Drawing.Color Color { get; set; }
}

public class StripData
{
    public StripData() : this(0, System.Drawing.Color.Black) {}
    public StripData(UInt16 delay) : this(delay, System.Drawing.Color.Black) {}

    public StripData(System.Drawing.Color color) : this(0, color) {}
    
    public StripData(UInt16 delay, System.Drawing.Color color)
    {
        Count = 21;
        Delay = delay;
        Leds = new LedData[Count];
        for (int i = 0; i < Count; i++)
        {
            Leds[i] = new LedData(color);
        }
    }
    public UInt16 Count { get; private set; }
    public UInt16 Delay { get; set; }
    public LedData[] Leds { get; }

    public void Clear()
    {
        Delay = 0;
        for (int i = 0; i < Count; i++)
        {
            Leds[i].Color = System.Drawing.Color.Black;
        }
    }
    public void Save(BinaryWriter writer)
    {
        writer.Write(Delay);
        for (int i = 0; i < Count; i++)
        {
            writer.Write(Leds[i].Color.R);
            writer.Write(Leds[i].Color.G);
            writer.Write(Leds[i].Color.B);
        }
    }
}