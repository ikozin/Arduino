# LedStarSimulator — Документация проекта

## Обзор

LedStarSimulator — десктопное приложение (WPF, .NET 10) для симуляции светодиодной звезды. Позволяет управлять цветом 21 LED-элемента, расположенных на 5-конечной звезде.

---

## Архитектура

Проект построен по паттерну **MVVM** (Model-View-ViewModel):

```
Models/          ← Бизнес-логика, геометрия, данные
ViewModels/      ← Связь Model ↔ View, INotifyPropertyChanged, ICommand
Views/           ← XAML-разметка, code-behind для отрисовки
```

### Компоненты

| Файл | Строки | Назначение |
|---|---|---|
| `Models/LedStarModel.cs` | 137 | Геометрия звезды, управление цветом, кэширование |
| `ViewModels/RelayCommand.cs` | 28 | Реализация `ICommand` для MVVM |
| `ViewModels/LedStarViewModel.cs` | 193 | Свойства R/G/B/HEX, команды, валидация |
| `MainWindow.xaml` | 240 | UI-разметка с Binding, стили |
| `MainWindow.xaml.cs` | 182 | Отрисовка звезды, обновление цветов |

---

## Функциональные возможности

### 1. Управление цветом

#### RGB-слайдеры
- Три слайдера (Red, Green, Blue) с диапазоном 0–255
- Синхронизация с текстовыми полями ввода
- Блокировка циклических обновлений через флаги `_updatingFromSlider` / `_updatingFromText`

#### Текстовые поля ввода
- Ручной ввод числовых значений (0–255)
- Автоматический сброс при невалидном вводе
- Clamp значений к диапазону 0–255

#### HEX-ввод
- Поле ввода цвета в формате `#RRGGBB`
- Маска ввода (`PreviewTextInput`) — блокирует не-Hex символы
- Валидация при вставке (`PreviewMouseUp`)
- Максимальная длина 7 символов (`#` + 6 hex)
- Автоматический сброс при невалидном вводе

#### Быстрые цвета
- 8 кнопок: Красный, Зелёный, Синий, Белый, Чёрный, Жёлтый, Циан, Розовый
- Реализованы через `ICommand` (`RelayCommand`)
- Fallback: извлечение цвета из `Background` → `Tag` атрибута

### 2. Визуализация звезды

#### Геометрия
- **21 LED**: 1 центральный + 20 по периметру (5 лучей × 4 элемента)
- Каждый луч: внутренний кончик → ребро → внешний кончик → ребро
- Нумерация: 0 (центр) → 1–20 (по часовой стрелке, начиная с нижнего внутреннего кончика)
- Внешний радиус: 150px, внутренний: `150 × 0.4 = 60px`
- Радиус LED: 14px

#### Отрисовка
- Canvas 500×500, центрирование звезды
- Каждый LED: эллипс (ядро) + эллипс (glow) + текстовая метка (индекс)
- Линии периметра: соединяют последовательные LED
- Glow-эффект: единый `SolidColorBrush` с динамической opacity

#### Обновление цветов
- Кэширование `SolidColorBrush` по ключу `R,G,B`
- Stroke-кисть кэшируется отдельно (alpha = 200)
- Glow-кисть мутируется напрямую (Color + Opacity)
- При перетаскивании слайдера: 0 новых объектов в GC

### 3. Кэширование

#### В модели (`LedStarModel`)
- `Positions` — кэшируется `IReadOnlyList<Point>`, инвалидация при необходимости
- `Colors` — кэшируется `IReadOnlyList<Color>`, инвалидация при `UpdateColors()`

#### В представлении (`MainWindow`)
- `_brushCache` — кэш fill-кистей по `R,G,B`
- `_strokeBrushCache` — кэш stroke-кистей по `200,R,G,B`
- `_glowBrush` — единый объект, мутируется при изменении цвета

#### В ViewModel (`LedStarViewModel`)
- `_colorPreviewBrush` — кэш превью-кисти с проверкой по байтам R/G/B

---

## Технические детали

### MVVM-паттерн

#### Model (`LedStarModel`)
- Событие `Changed` генерируется при изменении цвета
- `UpdateColors()` проверяет, изменился ли цвет (сравнение с `_prevR/G/B`)
- `Clamp()` ограничивает значения 0–255

#### ViewModel (`LedStarViewModel`)
- Реализует `INotifyPropertyChanged`
- `SetProperty<T>()` — вспомогательный метод с проверкой на равенство
- `OnPropertyChanged()` — уведомление View об изменении
- `ColorPreviewBrush` — свойство с кэшированием

#### View (`MainWindow`)
- `DataContext` устанавливается в XAML
- Binding с `Mode=TwoWay`, `UpdateSourceTrigger=PropertyChanged`
- Команды привязаны к кнопкам через `Command="{Binding ...}"`
- Code-behind (182 строки): отрисовка и обновление UI

### RelayCommand

```csharp
public class RelayCommand : ICommand
{
    private readonly Action<object> _execute;
    private readonly Func<object, bool>? _canExecute;
    
    // Подписка на CommandManager.RequerySuggested
    // Обработка null-параметров
}
```

### Производительность

| Оптимизация | Эффект |
|---|---|
| Кэш кистей | Создание Brush только при новом цвете |
| Единая glow-кисть | 0 новых объектов при обновлении |
| Кэш позиций/цветов в модели | `ToList()` вызывается один раз |
| Сравнение по байтам в `ColorPreviewBrush` | Избежание создания `Color` при каждом геттере |

---

## Структура файлов

```
LedStarSimulator/
├── Models/
│   └── LedStarModel.cs      # Бизнес-логика, геометрия
├── ViewModels/
│   ├── RelayCommand.cs      # ICommand реализация
│   └── LedStarViewModel.cs  # Связь Model ↔ View
├── MainWindow.xaml           # UI-разметка
├── MainWindow.xaml.cs        # Отрисовка, обновление
├── App.xaml                  # Точка входа
├── App.xaml.cs
└── LedStarSimulator.csproj   # Проектный файл (.NET 10)
```

---

## Зависимости

- **.NET 10.0** (net10.0-windows)
- **WPF** (Windows Presentation Foundation)
- Внешних зависимостей нет

---

## Сборка и запуск

```bash
# Сборка
dotnet build

# Запуск
dotnet run
```

---

## История изменений

### Переход на MVVM
- **До**: 326 строк в `MainWindow.xaml.cs` (code-behind)
- **После**: 182 строки в `MainWindow.xaml.cs` + 193 строки в `LedStarViewModel.cs`
- Code-behind только для отрисовки UI (работа с Canvas, Ellipse)
- ViewModel отвечает за данные, команды, валидацию
- View отвечает за визуальное представление

### Ключевые оптимизации
1. Кэширование кистей (fill, stroke, glow)
2. Единая glow-кисть с мутацией вместо создания новых объектов
3. Кэш позиций и цветов в модели
4. Сравнение по байтам в `ColorPreviewBrush`
5. Удаление мёртвого кода

---

## Примечания

- Звезда центрируется в Canvas 500×500
- Glow-эффект выходит за пределы LED (радиус 1.4×)
- Линии периметра: 20 линий между последовательными LED
- Нумерация LED: 0 (центр), 1–20 (периметр по часовой стрелке)
- HEX-поле: `MaxLength="7"`, валидация через `PreviewTextInput` и `PreviewMouseUp`
