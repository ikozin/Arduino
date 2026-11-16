---
## Goal

Migrate the LedStarSimulator WPF application to MVVM architecture while fixing critical bugs, implementing LED selection features, and resolving a click-to-select bug where clicking an LED does not update the ComboBox or apply individual color changes.

## Instructions

- Follow MVVM pattern with proper separation of concerns
- Use `INotifyPropertyChanged` for data binding
- Implement `ICommand` via `RelayCommand` class
- Remove glow effects entirely per user request
- Handle 4 data types for file parsing including `BackgroundWithIndices` (Type 3)
- Stop parsing on `0xFF` end marker
- Support individual LED selection (0-20) and "All LEDs" mode
- Fix click-to-select functionality where `PreviewMouseLeftButtonDown` on ellipse is not triggering (no MessageBox appears, no errors thrown)

## Discoveries

- WPF hit-testing ignores elements with `Opacity = 0.001` — even invisible elements cannot receive hit-test events
- `IsHitTestVisible = false` successfully prevents `Line` elements from interfering with ellipse hit-testing
- The `PreviewMouseLeftButtonDown` routed event on `ellipse` is not firing at all — debugging with `MessageBox.Show` confirmed no event capture
- `LedStarViewModel.cs` file was truncated during write operation, causing `ArgumentOutOfRangeException` and build failure
- Star geometry consists of 21 LEDs (1 center + 5 rays × 4 elements)
- Code-behind was successfully reduced from 182 to ~60 lines in `MainWindow.xaml.cs`
- `StarRenderer` was successfully extracted from code-behind

## Accomplished

**Completed:**
- Fixed critical issues: default initialization of `_prev*` fields, HEX string validation, number field validation
- Removed dead code (`GetColorBrush`, `StarViewbox`)
- Optimized brush caching (`_positionsCache`, `_colorsCache`) and simplified `Dispose`
- Created MVVM infrastructure: `RelayCommand.cs`, `LedStarViewModel.cs` (truncated/incomplete)
- Updated `MainWindow.xaml` with `DataContext` and command bindings
- Refactored architecture: `StarConfig`, `LedStarModelProvider`, `SequenceItemFactory`
- Split `FileParser` into partial classes
- Implemented 4th data type (`BackgroundWithIndices`) and end marker (`0xFF`)
- Added ComboBox (0-20) and "All LEDs" checkbox UI
- Removed glow effect entirely
- Applied `IsHitTestVisible = false` to `Line` and `indexText` elements
- Removed debug MessageBox.Show from StarRenderer and MainWindow
- Added direct click handler on each Ellipse for reliable LED selection
- Added Cursor.Hand to LED ellipses
- Removed debug MessageBox.Show from StarRenderer.cs (Canvas_PreviewMouseLeftButtonDown)
- Removed debug MessageBox.Show from MainWindow.xaml.cs (OnLedSelected handler)
- Added direct PreviewMouseLeftButtonDown handler on each Ellipse element for reliable click detection
- Added Cursor.Hand to LED ellipses for better UX
- Click-to-select now works: clicking an LED updates ComboBox and applies individual color
- Added SelectedLedIndexChanged event to LedStarModel for ComboBox → star sync
- Added OnSelectedLedIndexChanged handler in MainWindow.xaml.cs
- Added resizable panels with GridSplitter (left and right panels)

**Fixed:**
- Removed debug MessageBox.Show from StarRenderer.cs (Canvas_PreviewMouseLeftButtonDown)
- Removed debug MessageBox.Show from MainWindow.xaml.cs (OnLedSelected handler)
- Added direct PreviewMouseLeftButtonDown handler on each Ellipse element for reliable click detection
- Added Cursor.Hand to LED ellipses for better UX
- Click-to-select now works: clicking an LED updates ComboBox and applies individual color
- Added SelectedLedIndexChanged event to LedStarModel for ComboBox → star sync
- Added OnSelectedLedIndexChanged handler in MainWindow.xaml.cs

**Fixed (2026-11-16):**
- Removed duplicate DataContext (was set in both XAML and code-behind)
- Frozen SolidColorBrush in ColorPreviewBrush (thread-safety, memory leak prevention)
- Removed double initialization of _allLedsMode (field + constructor)
- Added UpdateSourceTrigger=PropertyChanged to ComboBox SelectedIndex binding
- Added PropertyChangedEventHandler to LedStarModel for AllLedsMode sync
- Added error handling in SequenceItemFactory.FromTypeCode for unknown type codes (throws InvalidOperationException)
- Removed `using static ErrorMessages` from all FileParser files; use full `ErrorMessages.xxx` paths
- Removed `using static HexValidator` from MainWindow.xaml.cs; use `HexValidator.xxx` paths
- Removed dead `Colors.Length == 0` check in FullArrayItem.DataDescription
- Expanded inline setters in LedStarModel for readability
- Translated remaining Russian comments to English (StarRenderer.cs, SequenceData.cs, LedStarModel.cs)
- Unified UI language: all Russian strings translated to English
- Grouped `using` directives: standard libraries first (alphabetical), then user code
- Added `nameof(AllLedsMode)` to OnPropertyChanged() for type safety
- Refactored Red/Green/Blue into common SetColorComponent method
- Removed unused IndividualColorMode property
- Generated ComboBox via ItemsSource + ItemStringFormat (removed 21 ComboBoxItem elements)
- Changed `Time` field from `byte` (1 byte) to `short` (2 bytes, int16); parser reads little-endian
- Added File Format description panel showing all 4 data types with byte layouts
- Added animation commands (ExecuteCommand, ExecuteAllCommand) with delay from Time field
- Added `_isAnimating` flag to block commands during animation execution
- Replaced LINQ `Min`/`Max` with loop in `StarRenderer.GetBounds` (no allocations)
- Moved size constants from FileParser to `SequenceItemTypeExtensions.GetFixedSize()` extension method

**Fixed (2026-11-16 v2):**
- `ColorPreviewBrush` — инициализация в конструкторе, `InvalidateColorBrush()` вместо null-инвалидации
- `async void` анимации — добавлен try/catch с MessageBox при ошибке, проверка `Time > 0` перед Delay
- `LedStarModel.Red/Green/Blue` — вынесено в общий метод `SetColorComponent()`
- Убран неиспользуемый `PropertyChanged` event из `LedStarModel`

**Not Started:**
- Add unit tests

## Relevant files / directories

- `ViewModels/RelayCommand.cs` — ICommand implementation
- `ViewModels/LedStarViewModel.cs` — INotifyPropertyChanged ViewModel (truncated, needs fix)
- `MainWindow.xaml` — View with DataContext and command bindings
- `MainWindow.xaml.cs` — Simplified code-behind (~60 lines)
- `StarRenderer.cs` — Extracted rendering logic
- `FileParser.SingleColor.cs` — Partial class for single color parsing
- `FileParser.BackgroundWithIndices.cs` — Partial class for type 3 parsing
- `StarConfig.cs` — Configuration constants
- `LedStarModelProvider.cs` — Geometry provider
- `SequenceItemFactory.cs` — Factory with `FromTypeCode` method
