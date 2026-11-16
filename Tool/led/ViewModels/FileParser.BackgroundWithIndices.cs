using LedStarSimulator.Models;
using static LedStarSimulator.ViewModels.ErrorMessages;

namespace LedStarSimulator.ViewModels;

/// <summary>
/// Парсер типа 3: цвет фона + цвет LED + массив индексов.
/// </summary>
public static partial class FileParser
{
    /// <summary>
    /// Парсит тип 3: цвет фона + цвет LED + массив индексов.
    /// </summary>
    private static BackgroundWithIndicesItem ParseBackgroundWithIndices(byte[] bytes, ref int offset, BackgroundWithIndicesItem item)
    {
        if (offset + item.Type.GetFixedSize() > bytes.Length)
            throw new InvalidOperationException(BackgroundWithIndicesInsufficientData);

        item.BackgroundRed = bytes[offset++];
        item.BackgroundGreen = bytes[offset++];
        item.BackgroundBlue = bytes[offset++];
        item.LedRed = bytes[offset++];
        item.LedGreen = bytes[offset++];
        item.LedBlue = bytes[offset++];

        if (offset >= bytes.Length)
            throw new InvalidOperationException(BackgroundWithIndicesArraySizeInsufficientData);

        item.IndexCount = bytes[offset++];
        if (offset + item.IndexCount > bytes.Length)
            throw new InvalidOperationException(BackgroundWithIndicesArrayInsufficientData);

        item.Indices = new byte[item.IndexCount];
        for (int i = 0; i < item.IndexCount; i++)
        {
            item.Indices[i] = bytes[offset++];
        }

        return item;
    }
}
