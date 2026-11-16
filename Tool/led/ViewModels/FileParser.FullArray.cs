using LedStarSimulator.Models;
using static LedStarSimulator.ViewModels.ErrorMessages;

namespace LedStarSimulator.ViewModels;

/// <summary>
/// Парсер типа 2: массив из 21 элемента, по 3 байта каждый (R, G, B).
/// </summary>
public static partial class FileParser
{
    /// <summary>
    /// Парсит тип 2: массив из 21 элемента, по 3 байта каждый (R, G, B).
    /// </summary>
    private static FullArrayItem ParseFullArray(byte[] bytes, ref int offset, FullArrayItem item)
    {
        if (offset + item.Type.GetFixedSize() > bytes.Length)
            throw new InvalidOperationException(FullArrayInsufficientData);

        for (int i = 0; i < 21; i++)
        {
            item.Colors[i] = (bytes[offset++], bytes[offset++], bytes[offset++]);
        }

        return item;
    }
}
