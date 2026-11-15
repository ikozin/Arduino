using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Input;
using System.Windows.Media;
using LedStarSimulator.Models;

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
    private byte _lastBrushR = 255;
    private byte _lastBrushG = 200;
    private byte _lastBrushB = 50;

    public LedStarViewModel()
    {
        _star = new LedStarModel();
        _red = _star.Red;
        _green = _star.Green;
        _blue = _star.Blue;
        _hexValue = $"#{_red:X2}{_green:X2}{_blue:X2}";

        SetRedCommand = new RelayCommand(_ => SetColor(255, 0, 0));
        SetGreenCommand = new RelayCommand(_ => SetColor(0, 255, 0));
        SetBlueCommand = new RelayCommand(_ => SetColor(0, 68, 255));
        SetWhiteCommand = new RelayCommand(_ => SetColor(255, 255, 255));
        SetBlackCommand = new RelayCommand(_ => SetColor(0, 0, 0));
        SetYellowCommand = new RelayCommand(_ => SetColor(255, 255, 0));
        SetCyanCommand = new RelayCommand(_ => SetColor(0, 255, 255));
        SetPinkCommand = new RelayCommand(_ => SetColor(255, 0, 255));
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

    // ===== Color Properties =====
    public int Red
    {
        get => _red;
        set
        {
            if (SetProperty(ref _red, value))
            {
                _star.Red = value;
                UpdateHexFromModel();
                OnPropertyChanged(nameof(ColorPreviewBrush));
            }
        }
    }

    public int Green
    {
        get => _green;
        set
        {
            if (SetProperty(ref _green, value))
            {
                _star.Green = value;
                UpdateHexFromModel();
                OnPropertyChanged(nameof(ColorPreviewBrush));
            }
        }
    }

    public int Blue
    {
        get => _blue;
        set
        {
            if (SetProperty(ref _blue, value))
            {
                _star.Blue = value;
                UpdateHexFromModel();
                OnPropertyChanged(nameof(ColorPreviewBrush));
            }
        }
    }

    // ===== Hex Value =====
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

    // ===== Color Preview Brush =====
    private SolidColorBrush? _colorPreviewBrush;

    public SolidColorBrush ColorPreviewBrush
    {
        get
        {
            var r = (byte)Red;
            var g = (byte)Green;
            var b = (byte)Blue;
            if (_colorPreviewBrush is null || _lastBrushR != r || _lastBrushG != g || _lastBrushB != b)
            {
                _colorPreviewBrush = new SolidColorBrush(Color.FromRgb(r, g, b));
                _lastBrushR = r;
                _lastBrushG = g;
                _lastBrushB = b;
            }
            return _colorPreviewBrush;
        }
    }

    // ===== Commands =====
    public ICommand SetRedCommand { get; }
    public ICommand SetGreenCommand { get; }
    public ICommand SetBlueCommand { get; }
    public ICommand SetWhiteCommand { get; }
    public ICommand SetBlackCommand { get; }
    public ICommand SetYellowCommand { get; }
    public ICommand SetCyanCommand { get; }
    public ICommand SetPinkCommand { get; }

    // ===== Model =====
    public LedStarModel Star => _star;

    // ===== Initialization =====
    private void SetColor(int r, int g, int b)
    {
        _star.Red = r;
        _star.Green = g;
        _star.Blue = b;
        _star.UpdateColors();
        SyncFromModel();
    }

    private void SyncFromModel()
    {
        Red = _star.Red;
        Green = _star.Green;
        Blue = _star.Blue;
    }

    // ===== Hex Parsing =====
    private void ParseHexValue(string text)
    {
        var hex = text.Trim();
        if (hex.Length > 0 && hex[0] == '#')
            hex = hex.Substring(1);

        if (hex.Length == 6 && int.TryParse(hex, System.Globalization.NumberStyles.HexNumber, null, out int color))
        {
            _star.Red = (color >> 16) & 0xFF;
            _star.Green = (color >> 8) & 0xFF;
            _star.Blue = color & 0xFF;
            _star.UpdateColors();
            SyncFromModel();
        }
        else if (hex.Length == 6)
        {
            // Invalid hex - reset to current value
            UpdateHexFromModel();
        }
    }

    private void UpdateHexFromModel()
    {
        HexValue = $"#{_star.Red:X2}{_star.Green:X2}{_star.Blue:X2}";
    }
}
