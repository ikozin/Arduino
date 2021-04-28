using System;
using System.Drawing;
using System.IO;

namespace libConverter
{
    public class rgb565
    {
        public ushort ColorToRGB565(Color color)
        {
            return (ushort)(((color.R & 0b11111000) << 8) | ((color.G & 0b11111100) << 3) | (color.B >> 3));
        }

        public void WriteBitmap(Stream stream, Bitmap bitmap, bool swap)
        {
            for (int y = 0; y < bitmap.Height; y++)
            {
                for (int x = 0; x < bitmap.Width; x++)
                {
                    Color pixel = bitmap.GetPixel(x, y);
                    ushort rgb565 = ColorToRGB565(pixel);
                    byte[] buf = BitConverter.GetBytes(rgb565);
                    if (swap)
                    {
                        Array.Reverse(buf);
                    }
                    stream.Write(buf);
                }
            }
            stream.Flush();
        }

        public void WriteRawData(Stream stream, Bitmap bitmap, bool swap, ushort posX, ushort posY, Color foreColor, Color backColor)
        {
            ushort rgb565;
            rgb565 = ColorToRGB565(foreColor);
            foreach (var item in BitConverter.GetBytes(rgb565)) stream.WriteByte(item);
            rgb565 = ColorToRGB565(backColor);
            foreach (var item in BitConverter.GetBytes(rgb565)) stream.WriteByte(item);
            foreach (var item in BitConverter.GetBytes((ushort)posX)) stream.WriteByte(item);
            foreach (var item in BitConverter.GetBytes((ushort)posY)) stream.WriteByte(item);
            foreach (var item in BitConverter.GetBytes((ushort)bitmap.Width)) stream.WriteByte(item);
            foreach (var item in BitConverter.GetBytes((ushort)bitmap.Height)) stream.WriteByte(item);
            WriteBitmap(stream, bitmap, swap);
        }
    }
}
