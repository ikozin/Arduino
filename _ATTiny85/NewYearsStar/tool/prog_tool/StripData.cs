using System.Drawing;

namespace ProgrTool;

public class LedData
{
    public LedData(System.Drawing.Color color)
    {
        Color = color;
    }
    public LedData(): this(System.Drawing.Color.White) {}
    
    public System.Drawing.Color Color { get; set; }
}

public class StripData
{
    public StripData()
    {
        Count = 8;
        Leds = new LedData[Count];
        for (int i = 0; i < Count; i++)
        {
            Leds[i] = new LedData();
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