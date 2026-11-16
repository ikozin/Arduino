namespace LedStarSimulator.Models;

/// <summary>
/// Константы конфигурации светодиодной звезды.
/// </summary>
public static class StarConfig
{
    /// <summary>Количество LED-элементов.</summary>
    public const int LedCount = 21;

    /// <summary>Внешний радиус звезды (пиксели).</summary>
    public const double OuterRadius = 150.0;

    /// <summary>Коэффициент внутреннего радиуса (отношение к внешнему).</summary>
    public const double InnerRatio = 0.4;

    /// <summary>Радиус одного LED-элемента (пиксели).</summary>
    public const double LedRadius = 14.0;

    /// <summary>Размер Canvas для отрисовки (пиксели).</summary>
    public const double CanvasSize = 500.0;

    /// <summary>Толщина линий связи.</summary>
    public const double LineThickness = 1.5;

    /// <summary>Прозрачность линий связи.</summary>
    public const double LineOpacity = 0.15;

    /// <summary>Прозрачность LED-элемента.</summary>
    public const double LedOpacity = 0.9;

    /// <summary>Коэффициент размера glow-эффекта (отношение к радиусу).</summary>
    public const double GlowRadiusFactor = 1.4;

    /// <summary>Минимальная opacity glow.</summary>
    public const double GlowOpacityMin = 0.1;

    // ===== Цвета =====

    /// <summary>Цвет линии связи.</summary>
    public static readonly System.Windows.Media.Brush LineBrush = System.Windows.Media.Brushes.White;

    /// <summary>Цвет текста метки.</summary>
    public static readonly System.Windows.Media.Brush TextBrush = System.Windows.Media.Brushes.White;

    /// <summary>Цвет обводки LED.</summary>
    public static readonly System.Windows.Media.Brush StrokeBrush = System.Windows.Media.Brushes.White;

    /// <summary>Цвет начального заполнения LED (жёлтый).</summary>
    public static readonly System.Windows.Media.Color InitialLedColor = System.Windows.Media.Color.FromRgb(255, 200, 50);
}
