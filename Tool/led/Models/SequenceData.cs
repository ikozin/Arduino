namespace LedStarSimulator.Models;

/// <summary>
/// Тип элемента последовательности данных.
/// </summary>
public enum SequenceItemType
{
    /// <summary>
    /// 1 элемент: R, G, B (3 байта).
    /// </summary>
    SingleColor = 0,

    /// <summary>
    /// 1 элемент: R, G, B (3 байта) + размер массива (1 байт) + индексы LED (массив байт).
    /// </summary>
    ColorWithIndices = 1,

    /// <summary>
    /// Массив из 21 элемента: каждый по 3 байта (R, G, B).
    /// </summary>
    FullArray = 2,

    /// <summary>
    /// 2 цвета: фон (R, G, B) + LED (R, G, B)
    /// + размер массива (1 байт) + индексы LED (массив байт).
    /// </summary>
    BackgroundWithIndices = 3,
}

/// <summary>
/// Расширения для SequenceItemType: размеры данных в байтах.
/// </summary>
public static class SequenceItemTypeExtensions
{
    /// <summary>
    /// Размер фиксированной части данных (заголовок + данные, без переменного массива индексов).
    /// </summary>
    public static int GetFixedSize(this SequenceItemType type) => type switch
    {
        SequenceItemType.SingleColor => 3,
        SequenceItemType.ColorWithIndices => 4,
        SequenceItemType.FullArray => StarConfig.LedCount * 3,
        SequenceItemType.BackgroundWithIndices => 7,
        _ => throw new InvalidOperationException($"Неизвестный тип данных: {type}")
    };
}

/// <summary>
/// Базовый элемент последовательности данных.
/// </summary>
public abstract class SequenceItem
{
    /// <summary>
    /// Время (опциональное, 2 байта, signed int16).
    /// </summary>
    public short Time { get; set; }

    /// <summary>
    /// Тип данных.
    /// </summary>
    public SequenceItemType Type { get; set; }

    /// <summary>
    /// Строковое представление данных для отображения.
    /// </summary>
    public abstract string DataDescription { get; }
}

/// <summary>
/// Тип 0: одиночный цвет (R, G, B — 1 байт каждый).
/// </summary>
public sealed class SingleColorItem : SequenceItem
{
    public byte Red { get; set; }
    public byte Green { get; set; }
    public byte Blue { get; set; }

    public override string DataDescription => $"RGB({Red}, {Green}, {Blue})";
}

/// <summary>
/// Тип 1: цвет + массив индексов LED.
/// </summary>
public sealed class ColorWithIndicesItem : SequenceItem
{
    public byte Red { get; set; }
    public byte Green { get; set; }
    public byte Blue { get; set; }

    /// <summary>
    /// Количество индексов в массиве.
    /// </summary>
    public int IndexCount { get; set; }

    /// <summary>
    /// Массив индексов светодиодов.
    /// </summary>
    public byte[] Indices { get; set; } = Array.Empty<byte>();

    public override string DataDescription => $"RGB({Red}, {Green}, {Blue}) + {IndexCount} LEDs";
}

/// <summary>
/// Тип 2: массив из 21 элемента, по 3 байта каждый (R, G, B).
/// </summary>
public sealed class FullArrayItem : SequenceItem
{
    /// <summary>
    /// 21 элемент: каждый содержит R, G, B.
    /// </summary>
    public (byte R, byte G, byte B)[] Colors { get; set; } = new (byte, byte, byte)[21];

    public override string DataDescription
    {
        get
        {
            var first = Colors[0];
            var last = Colors.Length > 1 ? Colors[Colors.Length - 1] : first;
            return $"Array[{Colors.Length}] RGB({first.R},{first.G},{first.B})...RGB({last.R},{last.G},{last.B})";
        }
    }
}

/// <summary>
/// Тип 3: цвет фона (R, G, B) + цвет светодиодов (R, G, B) + массив индексов LED.
/// </summary>
public sealed class BackgroundWithIndicesItem : SequenceItem
{
    /// <summary>
    /// Цвет фона: R, G, B.
    /// </summary>
    public byte BackgroundRed { get; set; }
    public byte BackgroundGreen { get; set; }
    public byte BackgroundBlue { get; set; }

    /// <summary>
    /// Цвет светодиодов: R, G, B.
    /// </summary>
    public byte LedRed { get; set; }
    public byte LedGreen { get; set; }
    public byte LedBlue { get; set; }

    /// <summary>
    /// Количество индексов в массиве.
    /// </summary>
    public int IndexCount { get; set; }

    /// <summary>
    /// Массив индексов светодиодов.
    /// </summary>
    public byte[] Indices { get; set; } = Array.Empty<byte>();

    public override string DataDescription =>
        $"BG({BackgroundRed},{BackgroundGreen},{BackgroundBlue}) " +
        $"LED({LedRed},{LedGreen},{LedBlue}) " +
        $"+ {IndexCount} LEDs";
}
