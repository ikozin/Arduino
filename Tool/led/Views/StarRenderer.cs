using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using LedStarSimulator.Models;

namespace LedStarSimulator.Views;

/// <summary>
/// Рендерит светодиодную звезду на Canvas.
/// Управляет созданием и обновлением визуальных элементов звезды.
/// </summary>
public class StarRenderer
{
    private readonly Canvas _canvas;
    private readonly Ellipse[] _ledElements;
    private readonly Point[] _ledPositions;
    private readonly Dictionary<string, SolidColorBrush> _brushCache = new();
    private readonly Dictionary<string, SolidColorBrush> _strokeBrushCache = new();

    /// <summary>
    /// Событие выбора LED по клику.
    /// </summary>
    public event Action<int>? LedSelected;

    /// <summary>
    /// Создаёт рендерер звезды.
    /// </summary>
    /// <param name="canvas">Canvas для отрисовки.</param>
    /// <param name="ledCount">Количество LED-элементов.</param>
    public StarRenderer(Canvas canvas, int ledCount)
    {
        _canvas = canvas;
        _ledElements = new Ellipse[ledCount];
        _ledPositions = new Point[ledCount];

        BuildStarVisuals();
    }

    /// <summary>
    /// Обновляет цвета LED-элементов.
    /// </summary>
    /// <param name="colors">Массив цветов для всех LED.</param>
    /// <param name="selectedLedIndex">Индекс выбранного LED (или -1, если не выбран).</param>
    public void UpdateColors(Color[] colors, int selectedLedIndex)
    {
        for (int i = 0; i < _ledElements.Length; i++)
        {
            var color = colors[i];
            var brush = GetCachedColorBrush(color.R, color.G, color.B);
            var strokeKey = $"200,{color.R},{color.G},{color.B}";
            if (!_strokeBrushCache.TryGetValue(strokeKey, out var strokeBrush))
            {
                strokeBrush = new SolidColorBrush(Color.FromArgb(200, color.R, color.G, color.B));
                strokeBrush.Freeze();
                _strokeBrushCache[strokeKey] = strokeBrush;
            }

            _ledElements[i].Fill = brush;
            _ledElements[i].Stroke = strokeBrush;

            // Подсветка выбранного LED
            if (i == selectedLedIndex && selectedLedIndex >= 0)
            {
                _ledElements[i].Stroke = Brushes.Yellow;
                _ledElements[i].StrokeThickness = 3;
            }
            else
            {
                _ledElements[i].Stroke = strokeBrush;
                _ledElements[i].StrokeThickness = StarConfig.LineThickness;
            }
        }
    }

    /// <summary>
    /// Очищает кэши кистей.
    /// </summary>
    public void ClearCache()
    {
        _brushCache.Clear();
        _strokeBrushCache.Clear();
    }

    /// <summary>
    /// Строит визуальные элементы звезды на Canvas.
    /// </summary>
    private void BuildStarVisuals()
    {
        var positions = LedStarModelProvider.GetPositions();
        var (offsetX, offsetY) = ComputeCenteringOffset(positions);

        CreateLedElements(positions, offsetX, offsetY);
        DrawStarLines(positions, offsetX, offsetY);
    }

    /// <summary>
    /// Вычисляет смещение для центрирования звезды на Canvas.
    /// </summary>
    private (double OffsetX, double OffsetY) ComputeCenteringOffset(IReadOnlyList<Point> positions)
    {
        var (minX, maxX, minY, maxY) = GetBounds(positions);
        var offsetX = (StarConfig.CanvasSize - (maxX - minX)) / 2 - minX;
        var offsetY = (StarConfig.CanvasSize - (maxY - minY)) / 2 - minY;
        return (offsetX, offsetY);
    }

    /// <summary>
    /// Создаёт эллипсы и метки для каждого LED-элемента.
    /// </summary>
    private void CreateLedElements(IReadOnlyList<Point> positions, double offsetX, double offsetY)
    {
        var radius = StarConfig.LedRadius;

        for (int i = 0; i < positions.Count; i++)
        {
            var px = positions[i].X + offsetX;
            var py = positions[i].Y + offsetY;

            // Основной эллипс
            var ellipse = CreateLedEllipse(px, py, radius, i);
            Canvas.SetLeft(ellipse, px - radius);
            Canvas.SetTop(ellipse, py - radius);

            // Текстовая метка индекса
            var indexText = CreateIndexText(i, radius);
            Canvas.SetLeft(indexText, px - radius);
            Canvas.SetTop(indexText, py - radius);

            _canvas.Children.Add(ellipse);
            _canvas.Children.Add(indexText);

            _ledElements[i] = ellipse;
            _ledPositions[i] = new Point(px, py);
        }
    }

    /// <summary>
    /// Создаёт эллипс LED-элемента.
    /// </summary>
    private Ellipse CreateLedEllipse(double px, double py, double radius, int ledIndex)
    {
        var ellipse = new Ellipse
        {
            Width = radius * 2,
            Height = radius * 2,
            Fill = GetCachedColorBrush(
                StarConfig.InitialLedColor.R,
                StarConfig.InitialLedColor.G,
                StarConfig.InitialLedColor.B),
            Stroke = StarConfig.StrokeBrush,
            StrokeThickness = StarConfig.LineThickness,
            Opacity = StarConfig.LedOpacity,
            Cursor = Cursors.Hand
        };

        // Обработчик клика на каждом эллипсе
        ellipse.PreviewMouseLeftButtonDown += (sender, e) =>
        {
            e.Handled = true;
            LedSelected?.Invoke(ledIndex);
        };

        return ellipse;
    }

    /// <summary>
    /// Создаёт текстовую метку с индексом LED.
    /// </summary>
    private static TextBlock CreateIndexText(int index, double radius)
    {
        return new TextBlock
        {
            Text = index.ToString(),
            FontSize = radius * 0.7,
            FontWeight = FontWeights.Bold,
            Foreground = StarConfig.TextBrush,
            HorizontalAlignment = HorizontalAlignment.Center,
            VerticalAlignment = VerticalAlignment.Center,
            TextAlignment = TextAlignment.Center,
            IsHitTestVisible = false
        };
    }

    /// <summary>
    /// Рисует линии между последовательными LED-элементами.
    /// </summary>
    private void DrawStarLines(IReadOnlyList<Point> positions, double offsetX, double offsetY)
    {
        for (int i = 1; i < positions.Count; i++)
        {
            int next = (i == positions.Count - 1) ? 1 : i + 1;
            var line = new Line
            {
                X1 = positions[i - 1].X + offsetX,
                Y1 = positions[i - 1].Y + offsetY,
                X2 = positions[i].X + offsetX,
                Y2 = positions[i].Y + offsetY,
                Stroke = StarConfig.LineBrush,
                StrokeThickness = StarConfig.LineThickness,
                Opacity = StarConfig.LineOpacity,
                IsHitTestVisible = false
            };
            _canvas.Children.Add(line);
        }
    }

    /// <summary>
    /// Получает границы списка точек.
    /// </summary>
    private static (double MinX, double MaxX, double MinY, double MaxY) GetBounds(IReadOnlyList<Point> positions)
    {
        double minX = positions[0].X;
        double maxX = positions[0].X;
        double minY = positions[0].Y;
        double maxY = positions[0].Y;

        for (int i = 1; i < positions.Count; i++)
        {
            var p = positions[i];
            if (p.X < minX) minX = p.X;
            if (p.X > maxX) maxX = p.X;
            if (p.Y < minY) minY = p.Y;
            if (p.Y > maxY) maxY = p.Y;
        }

        return (minX, maxX, minY, maxY);
    }

    /// <summary>
    /// Получает или создаёт кэшированную кисть цвета и замораживает её для потокобезопасности.
    /// </summary>
    private SolidColorBrush GetCachedColorBrush(byte r, byte g, byte b)
    {
        var key = $"{r},{g},{b}";
        if (!_brushCache.TryGetValue(key, out var brush))
        {
            brush = new SolidColorBrush(Color.FromArgb(255, r, g, b));
            brush.Freeze();
            _brushCache[key] = brush;
        }
        return brush;
    }
}
