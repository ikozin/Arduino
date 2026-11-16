# Skills for LedStarSimulator

## 1. mvvm-architecture

### Описание
Навык работы с архитектурой MVVM в проекте LedStarSimulator. Проект строго следует паттерну Model-View-ViewModel.

### Структура
```
LedStarSimulator/
├── Models/                    # Модель данных (чистая логика)
├── ViewModels/                # Логика представления (MVVM)
├── Views/                     # Представление (рендеринг)
└── MainWindow.xaml            # Разметка UI (view)
```

### Правила
- **Модель (`Models/`)** — только данные и бизнес-логика, без UI-зависимостей
- **ViewModel (`ViewModels/`)** — `INotifyPropertyChanged`, `ICommand`, привязки к UI
- **View (`Views/`)** — `StarRenderer.cs` только рендеринг на Canvas, без бизнес-логики
- **Code-behind** — максимум 70 строк, только event-хендлеры и инициализация

### Паттерны
- `RelayCommand` для `ICommand`
- `SetProperty<T>` для `INotifyPropertyChanged`
- `using static ErrorMessages` только для констант в парсере
- `internal` для доступа к модели из code-behind

### Ограничения
- Не добавлять логику в XAML или code-behind
- Не менять архитектуру Model/ViewModel/View
- Все новые команды должны использовать `RelayCommand`

---

## 2. binary-file-parser

### Описание
Навык работы с парсером бинарных файлов `.bin` для последовательностей LED-данных.

### Формат файла
- **Конец данных:** `0xFF` — парсер останавливается
- **Байт типа:** старший бит `0x80` — наличие поля времени, младшие 7 бит — код типа
- **Время:** `int16` (2 байта, little-endian), опционально

### Типы данных
| Код | Название | Описание |
|-----|----------|----------|
| 0 | `SingleColor` | R(1B) + G(1B) + B(1B) = 3 байта |
| 1 | `ColorWithIndices` | R(1B) + G(1B) + B(1B) + count(1B) + count×индексы |
| 2 | `FullArray` | 21 × (R+G+B) = 63 байта |
| 3 | `BackgroundWithIndices` | BG_R,G,B(3B) + LED_R,G,B(3B) + count(1B) + count×индексы |

### Правила
- Использовать частичные классы для каждого типа (`FileParser.TypeName.cs`)
- Константы размеров в `FileParser.cs`
- `SequenceItemFactory.FromTypeCode` для создания объектов
- Все ошибки форматирования бросают `InvalidOperationException` с сообщением из `ErrorMessages`
- Тип данных указывается через `SequenceItemType` enum

### Ограничения
- Не менять формат файла
- Не удалять обработку `0xFF`
- Для неизвестных типов бросать исключение, не возвращать заглушку

---

## 3. animation-system

### Описание
Навык работы с системой анимации LED-звезды.

### Компоненты
- `LedStarViewModel.ExecuteCommand` — анимация выбранного элемента из DataGrid
- `LedStarViewModel.ExecuteAllCommand` — последовательная анимация всех элементов
- `Task.Delay(item.Time)` — задержка между элементами из поля `Time`

### Правила
- Использовать `_isAnimating` флаг для блокировки команд во время анимации
- Блокировка: `_isAnimating = true` в try, сброс в finally
- `CanExecute` проверять флаг: `!_isAnimating`
- После завершения анимации флаг сбрасывается в finally-блоке

### Заглушки анимации
- `ExecuteSingleColor` — устанавливает R/G/B
- `ExecuteColorWithIndices` — устанавливает цвет для индексов
- `ExecuteFullArray` — устанавливает цвета для всех 21 LED
- `ExecuteBackgroundWithIndices` — сначала фон, затем цвет для индексов

### Ограничения
- Не вызывать анимацию повторно во время выполнения
- Не блокировать UI-поток при анимации
- Всегда сбрасывать `_isAnimating` в finally

---

## 4. star-renderer

### Описание
Навык работы с рендерингом LED-звезды на Canvas.

### Компоненты
- `StarRenderer` — создание и обновление визуальных элементов
- `LedStarModelProvider` — вычисление позиций LED (21 элемент: 1 центр + 5 лучей × 4)
- `StarConfig` — константы: размеры, цвета, прозрачность

### Правила
- Все кисти замораживать: `brush.Freeze()` для потокобезопасности
- Кэшировать кисти в `Dictionary<string, SolidColorBrush>`
- `IsHitTestVisible = false` для `Line` и `TextBlock` (индексы)
- Клик на эллипс через `PreviewMouseLeftButtonDown` — не на Canvas, а на каждом эллипсе
- Обновление цветов через `UpdateColors(colors, selectedLedIndex)`
- Выбранный LED подсвечивается жёлтой обводкой

### Оптимизация
- `GetBounds` — использовать цикл, не LINQ (избегать аллокаций)
- Кэшировать кисти по ключу `r,g,b`
- Обновлять только цвета, не перестраивать Canvas

### Ограничения
- Не менять геометрию звезды (21 элемент)
- Не убирать `IsHitTestVisible = false`
- Не удалять кэширование кистей

---

## 5. code-standards

### Описание
Навык соответствия стандартам кода проекта.

### Язык комментариев
- XML-документация (`/// <summary>`) — на русском языке
- Inline-комментарии (`//`) — на русском языке
- Имена классов, методов, свойств — на английском
- UI-строки в XAML — на русском

### using директивы
- Стандартные библиотеки первыми (alphabetical): `System.*`, `Microsoft.*`
- Пользовательские после: `LedStarSimulator.*`
- `using static ErrorMessages` — только в `FileParser.cs`

### Константы ошибок
- Хранить в `ErrorMessages.cs`
- Использовать через `using static` в парсере
- Формат: `MessageFormat` — `string.Format` для параметров

###命名规则
- Классы: `PascalCase` (`LedStarViewModel`)
- Методы: `PascalCase` (`ExecuteSelected`)
- Приватные поля: `_camelCase` (`_colorPreviewBrush`)
- Свойства: `PascalCase` (`ColorPreviewBrush`)
- Константы: `PascalCase` (`FileEndMarker`)

### Ограничения
- Не менять язык комментариев
- Не менять порядок `using`
- Не добавлять новые типы ошибок без обновления `ErrorMessages`
- Не удалять существующие константы
