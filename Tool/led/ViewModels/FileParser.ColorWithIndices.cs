using LedStarSimulator.Models;
using static LedStarSimulator.ViewModels.ErrorMessages;

namespace LedStarSimulator.ViewModels;

/// <summary>
/// Парсер типа 1: цвет + массив индексов LED.
/// </summary>
public static partial class FileParser
{
    /// <summary>
    /// Парсит тип 1: цвет + массив индексов LED.
    /// </summary>
    private static ColorWithIndicesItem ParseColorWithIndices(byte[] bytes, ref int offset, ColorWithIndicesItem item)
    {
        if (offset + item.Type.GetFixedSize() > bytes.Length)
            throw new InvalidOperationException(ColorWithIndicesInsufficientData);

        item.Red = bytes[offset++];
        item.Green = bytes[offset++];
        item.Blue = bytes[offset++];

        item.IndexCount = bytes[offset++];
        if (offset + item.IndexCount > bytes.Length)
            throw new InvalidOperationException(ColorWithIndicesArrayInsufficientData);

        item.Indices = new byte[item.IndexCount];
        for (int i = 0; i < item.IndexCount; i++)
        {
            item.Indices[i] = bytes[offset++];
        }

        return item;
    }
}
