using System.Windows;
using System.Windows.Media;

namespace LedStarSimulator.Models;

/// <summary>
/// Модель светодиодной звезды: вычисляет позиции 21 LED и управляет их цветом.
/// </summary>
public class LedStarModel
{
    public int Count => _leds.Count;

    public IReadOnlyList<Point> Positions => _positionsCache ??= _leds.Select(l => l.Position).ToList();

    public IReadOnlyList<Color> Colors => _colorsCache ??= _leds.Select(l => l.Color).ToList();

    public int Red
    {
        get => _red;
        set { if (_red != value) { _red = Clamp(value); UpdateColors(); } }
    }

    public int Green
    {
        get => _green;
        set { if (_green != value) { _green = Clamp(value); UpdateColors(); } }
    }

    public int Blue
    {
        get => _blue;
        set { if (_blue != value) { _blue = Clamp(value); UpdateColors(); } }
    }

    public double LedRadius { get; set; } = 14;

    public event EventHandler? Changed;

    private int _red = 255;
    private int _green = 200;
    private int _blue = 50;
    private int _prevRed = 255;
    private int _prevGreen = 200;
    private int _prevBlue = 50;

    private readonly List<LedItem> _leds = new(21);
    private IReadOnlyList<Point>? _positionsCache;
    private IReadOnlyList<Color>? _colorsCache;

    public LedStarModel()
    {
        CalculateStarGeometry();
        UpdateColors();
    }

    public void UpdateColors()
    {
        if (_red == _prevRed && _green == _prevGreen && _blue == _prevBlue)
            return;

        var color = Color.FromRgb((byte)Red, (byte)Green, (byte)Blue);
        foreach (var led in _leds)
            led.Color = color;

        _colorsCache = null;
        _prevRed = _red;
        _prevGreen = _green;
        _prevBlue = _blue;

        Changed?.Invoke(this, EventArgs.Empty);
    }

    private void CalculateStarGeometry()
    {
        var cx = 0.0;
        var cy = 0.0;
        var outerR = 150.0;
        var innerR = outerR * 0.4;

        // Предвычислим вершины
        var outerPts = new Point[5];
        var innerPts = new Point[5];

        for (int i = 0; i < 5; i++)
        {
            double outerAngle = -Math.PI / 2 + i * 2 * Math.PI / 5;
            double innerAngle = -Math.PI / 2 + Math.PI / 5 + i * 2 * Math.PI / 5;

            outerPts[i] = new Point(
                cx + outerR * Math.Cos(outerAngle),
                cy + outerR * Math.Sin(outerAngle));

            innerPts[i] = new Point(
                cx + innerR * Math.Cos(innerAngle),
                cy + innerR * Math.Sin(innerAngle));
        }

        _leds.Clear();

        // Центральный LED
        _leds.Add(new LedItem(new Point(cx, cy)));

        // 5 лучей: начинаем с внутреннего кончика (нижний), идём по часовой стрелке
        int start = 2;
        for (int step = 0; step < 5; step++)
        {
            int i = (start + step) % 5;
            int next = (i + 1) % 5;

            var inner = innerPts[i];
            var outer = outerPts[next];
            var nextInner = innerPts[next];

            // 1. Внутренний кончик
            _leds.Add(new LedItem(new Point(inner.X, inner.Y)));
            // 2. Ребро (внутренний → следующий внешний)
            _leds.Add(new LedItem(new Point((inner.X + outer.X) / 2, (inner.Y + outer.Y) / 2)));
            // 3. Внешний кончик
            _leds.Add(new LedItem(new Point(outer.X, outer.Y)));
            // 4. Ребро (внешний → внутренний следующего луча)
            _leds.Add(new LedItem(new Point((outer.X + nextInner.X) / 2, (outer.Y + nextInner.Y) / 2)));
        }
    }

    private static int Clamp(int v) => v < 0 ? 0 : v > 255 ? 255 : v;
}

/// <summary>
/// Отдельный светодиод.
/// </summary>
internal sealed class LedItem
{
    public Point Position { get; }
    public Color Color { get; set; }

    public LedItem(Point position) => Position = position;
}
