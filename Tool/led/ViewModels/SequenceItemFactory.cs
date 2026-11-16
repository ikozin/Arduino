using LedStarSimulator.Models;

namespace LedStarSimulator.ViewModels;

/// <summary>
/// Фабрика для создания SequenceItem по типу данных.
/// </summary>
public static class SequenceItemFactory
{
    /// <summary>
    /// Создаёт элемент последовательности по коду типа и времени.
    /// </summary>
    /// <param name="typeCode">Код типа данных (0-3).</param>
    /// <param name="time">Значение времени (опциональное).</param>
    /// <returns>Экземпляр SequenceItem подходящего типа.</returns>
    /// <exception cref="InvalidOperationException">Неизвестный код типа.</exception>
    public static SequenceItem FromTypeCode(byte typeCode, short time) => typeCode switch
    {
        0 => new SingleColorItem { Time = time, Type = SequenceItemType.SingleColor },
        1 => new ColorWithIndicesItem { Time = time, Type = SequenceItemType.ColorWithIndices },
        2 => new FullArrayItem { Time = time, Type = SequenceItemType.FullArray },
        3 => new BackgroundWithIndicesItem { Time = time, Type = SequenceItemType.BackgroundWithIndices },
        _ => throw new InvalidOperationException(string.Format(ErrorMessages.UnknownTypeCode, typeCode))
    };
}
