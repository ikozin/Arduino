using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Media;

namespace LedStarSimulator.Models;

/// <summary>
/// Модель управления цветом светодиодной звезды.
/// Не содержит геометрию — позиции управляются через LedStarModelProvider.
/// </summary>
public class LedStarModel
{
    /// <summary>Количество LED-элементов.</summary>
    public int Count => StarConfig.LedCount;

    /// <summary>
    /// Индекс выбранного LED (0-20).
    /// </summary>
    public int SelectedLedIndex
    {
        get => _selectedLedIndex;
        set
        {
            if (_selectedLedIndex != value)
            {
                _selectedLedIndex = ClampIndex(value);
                SelectedLedIndexChanged?.Invoke(this, _selectedLedIndex);
            }
        }
    }

    /// <summary>
    /// true — изменения цвета применяются ко всем LED.
    /// false — изменения цвета применяются только к выбранному LED.
    /// </summary>
    public bool AllLedsMode
    {
        get => _allLedsMode;
        set
        {
            if (_allLedsMode != value)
            {
                _allLedsMode = value;
                OnPropertyChanged(nameof(AllLedsMode));
            }
        }
    }

    private bool _allLedsMode = true;

    /// <summary>
    /// Текущий цвет, компонент R (0-255).
    /// </summary>
    public int Red
    {
        get => _red;
        set => SetColorComponent(ref _red, value, (r, g, b) => _red = r);
    }

    /// <summary>
    /// Текущий цвет, компонент G (0-255).
    /// </summary>
    public int Green
    {
        get => _green;
        set => SetColorComponent(ref _green, value, (r, g, b) => _green = g);
    }

    /// <summary>
    /// Текущий цвет, компонент B (0-255).
    /// </summary>
    public int Blue
    {
        get => _blue;
        set => SetColorComponent(ref _blue, value, (r, g, b) => _blue = b);
    }

    private void SetColorComponent(ref int field, int value, Action<int, int, int> setToFields)
    {
        if (field != value)
        {
            field = Clamp(value);
            setToFields(_red, _green, _blue);
            UpdateColors();
        }
    }

    /// <summary>Событие изменения цветов LED.</summary>
    public event EventHandler? Changed;

    /// <summary>Событие изменения индекса выбранного LED.</summary>
    public event EventHandler<int>? SelectedLedIndexChanged;

    /// <summary>Событие изменения свойства (для AllLedsMode).</summary>
    public event PropertyChangedEventHandler? PropertyChanged;

    private void OnPropertyChanged([CallerMemberName] string? propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    /// <summary>
    /// Текущий цвет в формате Color.
    /// </summary>
    public Color Color => Color.FromRgb((byte)Red, (byte)Green, (byte)Blue);

    /// <summary>
    /// Массив цветов для каждого LED.
    /// </summary>
    public Color[] LedColors => _ledColors;

    private int _selectedLedIndex = 0;
    private int _red = 255;
    private int _green = 200;
    private int _blue = 50;
    private int _prevRed = 255;
    private int _prevGreen = 200;
    private int _prevBlue = 50;

    /// <summary>
    /// Цвета всех LED. Когда AllLedsMode = true, все цвета одинаковые.
    /// </summary>
    private readonly Color[] _ledColors;

    public LedStarModel()
    {
        _ledColors = new Color[StarConfig.LedCount];
        var defaultColor = Color.FromRgb((byte)_red, (byte)_green, (byte)_blue);
        for (int i = 0; i < _ledColors.Length; i++)
            _ledColors[i] = defaultColor;
    }

    /// <summary>
    /// Обновляет кэш цвета и генерирует событие Changed.
    /// </summary>
    public void UpdateColors()
    {
        if (_red == _prevRed && _green == _prevGreen && _blue == _prevBlue)
            return;

        var newColor = Color.FromRgb((byte)Red, (byte)Green, (byte)Blue);

        if (_allLedsMode)
        {
            // Применить ко всем LED
            for (int i = 0; i < _ledColors.Length; i++)
                _ledColors[i] = newColor;
        }
        else
        {
            // Применить только к выбранному LED
            _ledColors[_selectedLedIndex] = newColor;
        }

        _prevRed = _red;
        _prevGreen = _green;
        _prevBlue = _blue;

        Changed?.Invoke(this, EventArgs.Empty);
    }

    /// <summary>
    /// Устанавливает цвет для конкретного LED.
    /// </summary>
    public void SetLedColor(int index, Color color)
    {
        if (index >= 0 && index < _ledColors.Length)
        {
            _ledColors[index] = color;
            Changed?.Invoke(this, EventArgs.Empty);
        }
    }

    /// <summary>
    /// Получает цвет конкретного LED.
    /// </summary>
    public Color GetLedColor(int index)
    {
        if (index >= 0 && index < _ledColors.Length)
            return _ledColors[index];
        return Color.FromRgb((byte)_red, (byte)_green, (byte)_blue);
    }

    private static int Clamp(int v) => v < 0 ? 0 : v > 255 ? 255 : v;

    private static int ClampIndex(int index) => index < 0 ? 0 : index >= StarConfig.LedCount ? StarConfig.LedCount - 1 : index;
}
