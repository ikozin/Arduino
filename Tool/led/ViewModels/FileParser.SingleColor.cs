using LedStarSimulator.Models;
using static LedStarSimulator.ViewModels.ErrorMessages;

namespace LedStarSimulator.ViewModels;

/// <summary>
/// Парсер типа 0: одиночный цвет (R, G, B — 1 байт каждый).
/// </summary>
public static partial class FileParser
{
    /// <summary>
    /// Парсит тип 0: одиночный цвет (R, G, B — 1 байт каждый).
    /// </summary>
    private static SingleColorItem ParseSingleColor(byte[] bytes, ref int offset, SingleColorItem item)
    {
        if (offset + item.Type.GetFixedSize() > bytes.Length)
            throw new InvalidOperationException(SingleColorInsufficientData);

        item.Red = bytes[offset++];
        item.Green = bytes[offset++];
        item.Blue = bytes[offset++];
        return item;
    }
}
