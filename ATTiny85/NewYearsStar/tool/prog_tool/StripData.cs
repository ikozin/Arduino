namespace ProgrTool;


public class LedData
{
    public LedData(System.Drawing.Color color) => Color = color;
    public LedData() : this(System.Drawing.Color.Black) { }

    public System.Drawing.Color Color { get; set; }
}

public class StripFill
{
    public const UInt16 Count = 21;
    public StripFill() : this(0, System.Drawing.Color.Black) { }
    public StripFill(UInt16 delay) : this(delay, System.Drawing.Color.Black) { }
    public StripFill(System.Drawing.Color color) : this(0, color) { }

    public StripFill(UInt16 delay, System.Drawing.Color color)
    {
        Delay = delay;
        Led = new LedData(color);
    }
    public UInt16 Delay { get; set; }
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


public class StripCount
{
    public StripCount() : this(0, System.Drawing.Color.Black) { }
    public StripCount(UInt16 delay) : this(delay, System.Drawing.Color.Black) { }
    public StripCount(System.Drawing.Color color) : this(0, color) { }

    public StripCount(UInt16 delay, System.Drawing.Color color)
    {
        Delay = delay;
        Led = new LedData(color);
        Indexies = new List<byte>();
    }
    public UInt16 Delay { get; set; }
    public LedData Led { get; set; }
    public List<byte> Indexies { get; private set; }
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