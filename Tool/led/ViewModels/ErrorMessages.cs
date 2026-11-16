namespace LedStarSimulator.ViewModels;

/// <summary>
/// Унифицированные сообщения об ошибках.
/// </summary>
public static class ErrorMessages
{
    // ===== Ошибки парсинга файлов =====
    public const string SingleColorInsufficientData = "Недостаточно данных для SingleColor";
    public const string ColorWithIndicesInsufficientData = "Недостаточно данных для ColorWithIndices";
    public const string ColorWithIndicesArrayInsufficientData = "Недостаточно данных для массива индексов";
    public const string FullArrayInsufficientData = "Недостаточно данных для FullArray";
    public const string BackgroundWithIndicesInsufficientData = "Недостаточно данных для BackgroundWithIndices";
    public const string BackgroundWithIndicesArraySizeInsufficientData = "Недостаточно данных для размера массива BackgroundWithIndices";
    public const string BackgroundWithIndicesArrayInsufficientData = "Недостаточно данных для массива индексов BackgroundWithIndices";
    public const string UnknownTypeCode = "Неизвестный тип данных: {0}";

    // ===== Общие ошибки =====
    public const string FileLoadError = "Ошибка при загрузке файла:\n{0}";
    public const string FileLoadErrorTitle = "Ошибка";
}
