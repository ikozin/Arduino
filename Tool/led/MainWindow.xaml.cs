using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;
using LedStarSimulator.ViewModels;

namespace LedStarSimulator;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    private readonly LedStarViewModel _viewModel;
    private readonly Ellipse[] _ledElements;
    private readonly SolidColorBrush _glowBrush;
    private readonly Dictionary<string, SolidColorBrush> _brushCache = new();
    private readonly Dictionary<string, SolidColorBrush> _strokeBrushCache = new();

    public MainWindow()
    {
        InitializeComponent();
        _viewModel = new LedStarViewModel();
        DataContext = _viewModel;

        _glowBrush = new SolidColorBrush(Colors.Black);
        _ledElements = new Ellipse[_viewModel.Star.Count];
        BuildStarVisuals();

        _viewModel.Star.Changed += OnStarChanged;
    }

    private void BuildStarVisuals()
    {
        var positions = _viewModel.Star.Positions;
        var radius = _viewModel.Star.LedRadius;

        double minX = positions.Min(p => p.X);
        double maxX = positions.Max(p => p.X);
        double minY = positions.Min(p => p.Y);
        double maxY = positions.Max(p => p.Y);
        double offsetX = (500 - (maxX - minX)) / 2 - minX;
        double offsetY = (500 - (maxY - minY)) / 2 - minY;

        for (int i = 0; i < positions.Count; i++)
        {
            double px = positions[i].X + offsetX;
            double py = positions[i].Y + offsetY;

            var ellipse = new Ellipse
            {
                Width = radius * 2,
                Height = radius * 2,
                Fill = GetCachedColorBrush(255, 200, 50),
                Stroke = Brushes.White,
                StrokeThickness = 1.5,
                Opacity = 0.9
            };

            var glow = new Ellipse
            {
                Width = radius * 2.8,
                Height = radius * 2.8,
                Fill = _glowBrush,
                Stroke = null
            };

            Canvas.SetLeft(ellipse, px - radius);
            Canvas.SetTop(ellipse, py - radius);
            Canvas.SetLeft(glow, px - radius * 1.4);
            Canvas.SetTop(glow, py - radius * 1.4);

            var indexText = new TextBlock
            {
                Text = i.ToString(),
                FontSize = radius * 0.7,
                FontWeight = FontWeights.Bold,
                Foreground = Brushes.White,
                HorizontalAlignment = HorizontalAlignment.Center,
                VerticalAlignment = VerticalAlignment.Center,
                TextAlignment = TextAlignment.Center,
                IsHitTestVisible = false
            };
            Canvas.SetLeft(indexText, px - radius);
            Canvas.SetTop(indexText, py - radius);

            StarCanvas.Children.Add(glow);
            StarCanvas.Children.Add(ellipse);
            StarCanvas.Children.Add(indexText);

            _ledElements[i] = ellipse;
        }

        DrawStarLines(positions, offsetX, offsetY);
    }

    private void DrawStarLines(IReadOnlyList<Point> positions, double offsetX, double offsetY)
    {
        for (int i = 1; i < positions.Count; i++)
        {
            int next = (i == positions.Count - 1) ? 1 : i + 1;
            var line = new Line
            {
                X1 = positions[i].X + offsetX,
                Y1 = positions[i].Y + offsetY,
                X2 = positions[next].X + offsetX,
                Y2 = positions[next].Y + offsetY,
                Stroke = Brushes.White,
                StrokeThickness = 1.5,
                Opacity = 0.15
            };
            StarCanvas.Children.Add(line);
        }
    }

    private void UpdateLEDs()
    {
        var color = _viewModel.Star.Colors[0];
        var brush = GetCachedColorBrush(color.R, color.G, color.B);
        var strokeKey = $"200,{color.R},{color.G},{color.B}";
        if (!_strokeBrushCache.TryGetValue(strokeKey, out var strokeBrush))
        {
            strokeBrush = new SolidColorBrush(Color.FromArgb(200, color.R, color.G, color.B));
            _strokeBrushCache[strokeKey] = strokeBrush;
        }
        for (int i = 0; i < _ledElements.Length; i++)
        {
            _ledElements[i].Fill = brush;
            _ledElements[i].Stroke = strokeBrush;
        }

        var glowOpacity = 0.1 + (color.R + color.G + color.B) / (3.0 * 255) * 0.4;
        _glowBrush.Color = Color.FromRgb(color.R, color.G, color.B);
        _glowBrush.Opacity = glowOpacity;
    }

    private SolidColorBrush GetCachedColorBrush(byte r, byte g, byte b)
    {
        var key = $"{r},{g},{b}";
        if (!_brushCache.TryGetValue(key, out var brush))
        {
            brush = new SolidColorBrush(Color.FromArgb(255, r, g, b));
            _brushCache[key] = brush;
        }
        return brush;
    }

    private void OnStarChanged(object? sender, EventArgs e)
    {
        UpdateLEDs();
    }

    private void HexValue_PreviewTextInput(object sender, System.Windows.Input.TextCompositionEventArgs e)
    {
        var tb = (TextBox)sender;
        var text = (tb.Text + e.Text).Trim();
        if (text.Length > 0 && text[0] == '#')
            text = text.Substring(1);

        e.Handled = text.Length > 6 || !text.All(c => char.IsAsciiHexDigit(c));
    }

    private void HexValue_PreviewMouseUp(object sender, System.Windows.Input.MouseEventArgs e)
    {
        var tb = (TextBox)sender;
        var text = tb.Text.Trim();
        if (text.Length > 0 && text[0] == '#')
            text = text.Substring(1);

        if (text.Length > 6 || (text.Length > 0 && !text.All(c => char.IsAsciiHexDigit(c))))
        {
            _viewModel.HexValue = $"#{_viewModel.Star.Red:X2}{_viewModel.Star.Green:X2}{_viewModel.Star.Blue:X2}";
        }
    }

    protected override void OnClosed(EventArgs e)
    {
        _brushCache.Clear();
        _strokeBrushCache.Clear();
        base.OnClosed(e);
    }
}
