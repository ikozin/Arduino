namespace LedStarSimulator.ViewModels;

/// <summary>
/// Валидатор HEX-значений цвета.
/// </summary>
public static class HexValidator
{
    /// <summary>
    /// Максимальная длина HEX-строки с символом #.
    /// </summary>
    private const int MaxLengthWithHash = 7;

    /// <summary>
    /// Максимальная длина HEX-строки без символа #.
    /// </summary>
    private const int MaxLengthWithoutHash = 6;

    /// <summary>
    /// Проверяет, является ли символ допустимой шестнадцатеричной цифрой.
    /// </summary>
    public static bool IsAsciiHexDigit(char c) => char.IsAsciiHexDigit(c);

    /// <summary>
    /// Проверяет, валидна ли HEX-строка для ввода.
    /// </summary>
    /// <param name="text">Входящая строка (с # или без).</param>
    /// <returns>True если валидна.</returns>
    public static bool IsValid(string text)
    {
        if (string.IsNullOrEmpty(text))
            return true;

        var cleanText = RemoveHash(text);
        return cleanText.Length <= MaxLengthWithoutHash && cleanText.All(IsAsciiHexDigit);
    }

    /// <summary>
    /// Проверяет, можно ли разрешить ввод нового символа.
    /// </summary>
    /// <param name="currentText">Текущий текст в поле.</param>
    /// <param name="newChar">Новый символ.</param>
    /// <returns>True если ввод разрешён.</returns>
    public static bool CanAcceptInput(string currentText, char newChar)
    {
        var combined = RemoveHash(currentText) + newChar;
        return combined.Length <= MaxLengthWithoutHash && IsAsciiHexDigit(newChar);
    }

    /// <summary>
    /// Извлекает HEX-значение из строки (удаляет # если есть).
    /// </summary>
    public static string ExtractHex(string text)
    {
        var clean = RemoveHash(text);
        return clean.Length == 6 ? clean : string.Empty;
    }

    /// <summary>
    /// Формирует HEX-строку из RGB-компонент.
    /// </summary>
    public static string FormatHex(byte r, byte g, byte b) => $"#{r:X2}{g:X2}{b:X2}";

    /// <summary>
    /// Удаляет символ # из начала строки.
    /// </summary>
    private static string RemoveHash(string text)
    {
        if (string.IsNullOrEmpty(text))
            return string.Empty;

        var clean = text.Trim();
        return clean.Length > 0 && clean[0] == '#' ? clean.Substring(1) : clean;
    }
}
