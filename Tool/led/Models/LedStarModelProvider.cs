using System.Windows;
using LedStarSimulator.Models;

namespace LedStarSimulator.Models;

/// <summary>
/// Провайдер геометрии звезды.
/// Выносит вычисление позиций из LedStarModel для разделения ответственности.
/// </summary>
public static class LedStarModelProvider
{
    /// <summary>
    /// Получает позиции LED-элементов.
    /// </summary>
    public static IReadOnlyList<Point> GetPositions()
    {
        var cx = 0.0;
        var cy = 0.0;
        var outerR = StarConfig.OuterRadius;
        var innerR = outerR * StarConfig.InnerRatio;

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

        var positions = new List<Point>(StarConfig.LedCount);

        // Центральный LED
        positions.Add(new Point(cx, cy));

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
            positions.Add(new Point(inner.X, inner.Y));
            // 2. Ребро (внутренний → следующий внешний)
            positions.Add(new Point((inner.X + outer.X) / 2, (inner.Y + outer.Y) / 2));
            // 3. Внешний кончик
            positions.Add(new Point(outer.X, outer.Y));
            // 4. Ребро (внешний → внутренний следующего луча)
            positions.Add(new Point((outer.X + nextInner.X) / 2, (outer.Y + nextInner.Y) / 2));
        }

        return positions;
    }
}
