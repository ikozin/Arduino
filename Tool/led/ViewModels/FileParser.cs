using System.Collections.ObjectModel;
using System.IO;
using LedStarSimulator.Models;
using static LedStarSimulator.ViewModels.ErrorMessages;

namespace LedStarSimulator.ViewModels;

/// <summary>
/// Парсит бинарные файлы данных последовательности.
/// Поддерживает 4 типа данных с опциональным полем времени.
/// </summary>
public static partial class FileParser
{
    // ===== Константы формата файла =====

    /// <summary>Конец данных (0xFF).</summary>
    private const byte FileEndMarker = 0xFF;

    /// <summary>Маска для извлечения кода типа (младшие 7 бит).</summary>
    private const byte TypeCodeMask = 0x7F;

    /// <summary>Флаг наличия поля времени (старший бит).</summary>
    private const byte HasTimeFlag = 0x80;

    // ===== Основной метод парсинга =====

    /// <summary>
    /// Парсит бинарный файл и возвращает коллекцию элементов последовательности.
    /// </summary>
    /// <param name="filePath">Путь к файлу.</param>
    /// <returns>Коллекция распарсенных элементов.</returns>
    /// <exception cref="FileNotFoundException">Файл не найден.</exception>
    /// <exception cref="InvalidOperationException">Ошибка формата данных.</exception>
    public static ObservableCollection<SequenceItem> Parse(string filePath)
    {
        var bytes = File.ReadAllBytes(filePath);
        var items = new ObservableCollection<SequenceItem>();
        var offset = 0;

        while (offset < bytes.Length)
        {
            byte typeByte = bytes[offset++];

            // Проверка конца данных
            if (typeByte == FileEndMarker)
                break;

            // Извлечение кода типа и проверка наличия поля времени
            bool hasTime = (typeByte & HasTimeFlag) != 0;
            byte typeCode = (byte)(typeByte & TypeCodeMask);
            short time = 0;

            if (hasTime)
            {
                if (offset + 1 >= bytes.Length)
                    break;
                time = (short)((bytes[offset + 1] << 8) | bytes[offset]);
                offset += 2;
            }

            // Создание базового элемента через фабрику
            var item = SequenceItemFactory.FromTypeCode(typeCode, time);

            // Парсинг данных элемента по типу
            item = ParseItemData(bytes, ref offset, item);

            items.Add(item);
        }

        return items;
    }

    /// <summary>
    /// Парсит данные элемента в зависимости от его типа.
    /// </summary>
    private static SequenceItem ParseItemData(byte[] bytes, ref int offset, SequenceItem item)
    {
        return item switch
        {
            SingleColorItem singleColor => ParseSingleColor(bytes, ref offset, singleColor),
            ColorWithIndicesItem colorWithIndices => ParseColorWithIndices(bytes, ref offset, colorWithIndices),
            FullArrayItem fullArray => ParseFullArray(bytes, ref offset, fullArray),
            BackgroundWithIndicesItem backgroundWithIndices => ParseBackgroundWithIndices(bytes, ref offset, backgroundWithIndices),
            _ => throw new InvalidOperationException(UnknownTypeCode)
        };
    }
}
