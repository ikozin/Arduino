using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Media;
using LedStarSimulator.Models;
using Microsoft.Win32;
using static LedStarSimulator.ViewModels.ErrorMessages;

namespace LedStarSimulator.ViewModels;

/// <summary>
/// ViewModel для LED Star Simulator.
/// Связывает модель с представлением через INotifyPropertyChanged и ICommand.
/// </summary>
public class LedStarViewModel : INotifyPropertyChanged
{
    private readonly LedStarModel _star;
    private int _red;
    private int _green;
    private int _blue;
    private string _hexValue;
    private int _selectedLedIndex;

    public LedStarViewModel()
    {
        _star = new LedStarModel();
        _red = _star.Red;
        _green = _star.Green;
        _blue = _star.Blue;
        _selectedLedIndex = _star.SelectedLedIndex;
        _allLedsMode = _star.AllLedsMode;
        _hexValue = HexValidator.FormatHex((byte)_red, (byte)_green, (byte)_blue);
        _colorPreviewBrush = CreateColorBrush();

        // Быстрые команды цветов
        SetRedCommand = new RelayCommand(_ => SetColor(255, 0, 0));
        SetGreenCommand = new RelayCommand(_ => SetColor(0, 255, 0));
        SetBlueCommand = new RelayCommand(_ => SetColor(0, 64, 255));
        SetWhiteCommand = new RelayCommand(_ => SetColor(255, 255, 255));
        SetBlackCommand = new RelayCommand(_ => SetColor(0, 0, 0));
        SetYellowCommand = new RelayCommand(_ => SetColor(255, 255, 0));
        SetCyanCommand = new RelayCommand(_ => SetColor(0, 255, 255));
        SetPinkCommand = new RelayCommand(_ => SetColor(255, 0, 255));

        // Команда открытия файла
        OpenFileCommand = new RelayCommand(_ => OpenFile());

        // Команды анимации
        ExecuteCommand = new RelayCommand(_ => ExecuteSelected(), _ => SelectedSequenceItem is not null && !_isAnimating);
        ExecuteAllCommand = new RelayCommand(_ => ExecuteAll(), _ => SequenceItems.Count > 0 && !_isAnimating);
    }

    // ===== Кисть предпросмотра цвета =====

    /// <summary>Кисть для границы предпросмотра цвета, замороженная для потокобезопасности.</summary>
    public SolidColorBrush ColorPreviewBrush => _colorPreviewBrush;

    private void InvalidateColorBrush()
    {
        _colorPreviewBrush.Freeze();
        _colorPreviewBrush = CreateColorBrush();
    }

    private static SolidColorBrush CreateColorBrush()
    {
        var brush = new SolidColorBrush(Color.FromRgb(255, 200, 50));
        brush.Freeze();
        return brush;
    }

    // ===== INotifyPropertyChanged =====
    public event PropertyChangedEventHandler? PropertyChanged;

    private void OnPropertyChanged([CallerMemberName] string? propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    private bool SetProperty<T>(ref T field, T value, [CallerMemberName] string? propertyName = null)
    {
        if (EqualityComparer<T>.Default.Equals(field, value))
            return false;
        field = value;
        OnPropertyChanged(propertyName);
        return true;
    }

    // ===== Свойства цвета =====

    /// <summary>Красный компонент (0-255).</summary>
    public int Red
    {
        get => _red;
        set => SetColorComponent(ref _red, value, (r, g, b) => _star.Red = r);
    }

    /// <summary>Зелёный компонент (0-255).</summary>
    public int Green
    {
        get => _green;
        set => SetColorComponent(ref _green, value, (r, g, b) => _star.Green = g);
    }

    /// <summary>Синий компонент (0-255).</summary>
    public int Blue
    {
        get => _blue;
        set => SetColorComponent(ref _blue, value, (r, g, b) => _star.Blue = b);
    }

    private void SetColorComponent(ref int field, int value, Action<int, int, int> setToStar)
    {
        if (SetProperty(ref field, value))
        {
            setToStar(_red, _green, _blue);
            UpdateHexFromModel();
            InvalidateColorBrush();
            OnPropertyChanged(nameof(ColorPreviewBrush));
        }
    }

    // ===== HEX-значение =====

    /// <summary>Цвет в HEX-формате (например, "#FFCC32").</summary>
    public string HexValue
    {
        get => _hexValue;
        set
        {
            if (SetProperty(ref _hexValue, value))
            {
                ParseHexValue(value);
            }
        }
    }

    // ===== Выбор LED =====

    /// <summary>Доступные индексы LED для привязки ComboBox.</summary>
    public IEnumerable<int> LedIndices { get; } = Enumerable.Range(0, StarConfig.LedCount);

    /// <summary>Индекс выбранного LED (0-20).</summary>
    public int SelectedLedIndex
    {
        get => _selectedLedIndex;
        set
        {
            if (SetProperty(ref _selectedLedIndex, value))
            {
                _star.SelectedLedIndex = value;
                UpdateSelectedLedColor();
            }
        }
    }

    public bool AllLedsMode
    {
        get => _allLedsMode;
        set
        {
            if (SetProperty(ref _allLedsMode, value))
            {
                _star.AllLedsMode = value;
                // Синхронизировать значения цвета из модели при переключении в режим "все LED"
                if (value)
                {
                    SyncFromModel();
                }
            }
        }
    }

    private bool _allLedsMode;

    /// <summary>Флаг анимации — блокирует команды во время выполнения.</summary>
    private bool _isAnimating;

    /// <summary>Кисть предпросмотра цвета, замороженная для потокобезопасности.</summary>
    private SolidColorBrush _colorPreviewBrush;

    // ===== Команды =====
    public ICommand SetRedCommand { get; }
    public ICommand SetGreenCommand { get; }
    public ICommand SetBlueCommand { get; }
    public ICommand SetWhiteCommand { get; }
    public ICommand SetBlackCommand { get; }
    public ICommand SetYellowCommand { get; }
    public ICommand SetCyanCommand { get; }
    public ICommand SetPinkCommand { get; }
    public ICommand OpenFileCommand { get; }
    public ICommand ExecuteCommand { get; }
    public ICommand ExecuteAllCommand { get; }

    // ===== Модель =====

    /// <summary>Доступ к внутренней модели звезды для рендеринга.</summary>
    internal LedStarModel Star => _star;

    // ===== Данные последовательности =====
    private readonly ObservableCollection<SequenceItem> _sequenceItems = new();
    public ObservableCollection<SequenceItem> SequenceItems => _sequenceItems;
    public string CurrentFileName { get; private set; } = string.Empty;

    /// <summary>Выбранный элемент последовательности в DataGrid.</summary>
    public SequenceItem? SelectedSequenceItem { get; set; }

    // ===== Применение цвета =====

    private void SetColor(int r, int g, int b)
    {
        _red = r;
        _green = g;
        _blue = b;
        _star.Red = r;
        _star.Green = g;
        _star.Blue = b;
        _star.UpdateColors();
        UpdateHexFromModel();
        OnPropertyChanged(nameof(Red));
        OnPropertyChanged(nameof(Green));
        OnPropertyChanged(nameof(Blue));
        OnPropertyChanged(nameof(ColorPreviewBrush));
        InvalidateColorBrush();

        if (!_allLedsMode)
        {
            UpdateSelectedLedColor();
        }
    }

    private void SyncFromModel()
    {
        Red = _star.Red;
        Green = _star.Green;
        Blue = _star.Blue;
    }

    private void UpdateSelectedLedColor()
    {
        var color = _star.GetLedColor(_selectedLedIndex);
        Red = color.R;
        Green = color.G;
        Blue = color.B;
    }

    // ===== Парсинг HEX =====

    private void ParseHexValue(string text)
    {
        var hex = HexValidator.ExtractHex(text);
        if (hex.Length == 6 && int.TryParse(hex, NumberStyles.HexNumber, null, out int color))
        {
            _star.Red = (color >> 16) & 0xFF;
            _star.Green = (color >> 8) & 0xFF;
            _star.Blue = color & 0xFF;
            _star.UpdateColors();
            SyncFromModel();
        }
        else if (hex.Length == 6)
        {
            // Неверный HEX — сбросить к текущему значению
            UpdateHexFromModel();
        }
    }

    private void UpdateHexFromModel()
    {
        HexValue = HexValidator.FormatHex((byte)_star.Red, (byte)_star.Green, (byte)_star.Blue);
    }

    // ===== Загрузка файлов =====

    private void OpenFile()
    {
        var dialog = new OpenFileDialog
        {
            Title = "Открыть файл данных",
            Filter = "Файлы данных (*.bin)|*.bin|Все файлы|*.*",
            DefaultExt = ".bin"
        };

        if (dialog.ShowDialog() != true)
            return;

        try
        {
            var fileName = dialog.FileName;
            _sequenceItems.Clear();

            var parsedItems = FileParser.Parse(fileName);
            foreach (var item in parsedItems)
            {
                _sequenceItems.Add(item);
            }
            CurrentFileName = Path.GetFileName(fileName);
        }
        catch (Exception ex)
        {
            _sequenceItems.Clear();
            CurrentFileName = string.Empty;
            System.Windows.MessageBox.Show(
                string.Format(FileLoadError, ex.Message),
                FileLoadErrorTitle,
                System.Windows.MessageBoxButton.OK,
                System.Windows.MessageBoxImage.Error);
        }
    }

    // ===== Анимация =====

    /// <summary>Выполнить анимацию выбранного элемента.</summary>
    private async void ExecuteSelected()
    {
        if (SelectedSequenceItem is null)
            return;

        _isAnimating = true;
        try
        {
            switch (SelectedSequenceItem)
            {
                case SingleColorItem singleColor:
                    ExecuteSingleColor(singleColor);
                    break;
                case ColorWithIndicesItem colorWithIndices:
                    ExecuteColorWithIndices(colorWithIndices);
                    break;
                case FullArrayItem fullArray:
                    ExecuteFullArray(fullArray);
                    break;
                case BackgroundWithIndicesItem backgroundWithIndices:
                    ExecuteBackgroundWithIndices(backgroundWithIndices);
                    break;
            }

            if (SelectedSequenceItem.Time > 0)
                await Task.Delay(SelectedSequenceItem.Time);
        }
        catch (Exception ex)
        {
            System.Windows.MessageBox.Show(
                $"Ошибка анимации:\n{ex.Message}",
                "Ошибка",
                System.Windows.MessageBoxButton.OK,
                System.Windows.MessageBoxImage.Error);
        }
        finally
        {
            _isAnimating = false;
        }
    }

    /// <summary>Выполнить анимацию всех элементов последовательности.</summary>
    private async void ExecuteAll()
    {
        _isAnimating = true;
        try
        {
            foreach (var item in _sequenceItems)
            {
                switch (item)
                {
                    case SingleColorItem singleColor:
                        ExecuteSingleColor(singleColor);
                        break;
                    case ColorWithIndicesItem colorWithIndices:
                        ExecuteColorWithIndices(colorWithIndices);
                        break;
                    case FullArrayItem fullArray:
                        ExecuteFullArray(fullArray);
                        break;
                    case BackgroundWithIndicesItem backgroundWithIndices:
                        ExecuteBackgroundWithIndices(backgroundWithIndices);
                        break;
                }

                if (item.Time > 0)
                    await Task.Delay(item.Time);
            }
        }
        catch (Exception ex)
        {
            System.Windows.MessageBox.Show(
                $"Ошибка анимации:\n{ex.Message}",
                "Ошибка",
                System.Windows.MessageBoxButton.OK,
                System.Windows.MessageBoxImage.Error);
        }
        finally
        {
            _isAnimating = false;
        }
    }

    /// <summary>Заглушка анимации для типа 0: одиночный цвет.</summary>
    private void ExecuteSingleColor(SingleColorItem item)
    {
        // TODO: реализовать анимацию одиночного цвета
        _star.Red = item.Red;
        _star.Green = item.Green;
        _star.Blue = item.Blue;
        _star.UpdateColors();
        SyncFromModel();
    }

    /// <summary>Заглушка анимации для типа 1: цвет + массив индексов.</summary>
    private void ExecuteColorWithIndices(ColorWithIndicesItem item)
    {
        // TODO: реализовать анимацию цвета с индексами
        var color = Color.FromRgb(item.Red, item.Green, item.Blue);
        for (int i = 0; i < item.Indices.Length; i++)
        {
            _star.SetLedColor(item.Indices[i], color);
        }
        _star.UpdateColors();
    }

    /// <summary>Заглушка анимации для типа 2: полный массив.</summary>
    private void ExecuteFullArray(FullArrayItem item)
    {
        // TODO: реализовать анимацию полного массива
        for (int i = 0; i < item.Colors.Length; i++)
        {
            var c = item.Colors[i];
            _star.SetLedColor(i, Color.FromRgb(c.R, c.G, c.B));
        }
        _star.UpdateColors();
    }

    /// <summary>Заглушка анимации для типа 3: цвет фона + цвет LED + массив индексов.</summary>
    private void ExecuteBackgroundWithIndices(BackgroundWithIndicesItem item)
    {
        // TODO: реализовать анимацию фона + цвета LED с индексами
        var bg = Color.FromRgb(item.BackgroundRed, item.BackgroundGreen, item.BackgroundBlue);
        var led = Color.FromRgb(item.LedRed, item.LedGreen, item.LedBlue);

        // Устанавливаем цвет фона (все LED)
        for (int i = 0; i < _star.Count; i++)
            _star.SetLedColor(i, bg);
        _star.UpdateColors();

        // Устанавливаем цвет LED для выбранных индексов
        for (int i = 0; i < item.Indices.Length; i++)
        {
            _star.SetLedColor(item.Indices[i], led);
        }
        _star.UpdateColors();
    }
}
