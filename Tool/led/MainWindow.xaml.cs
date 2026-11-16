using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using LedStarSimulator.ViewModels;
using LedStarSimulator.Views;

namespace LedStarSimulator;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    private readonly LedStarViewModel _viewModel;
    private readonly StarRenderer _starRenderer;

    public MainWindow()
    {
        InitializeComponent();
        _viewModel = new LedStarViewModel();
        DataContext = _viewModel;

        // Initialize star renderer
        _starRenderer = new StarRenderer(StarCanvas, _viewModel.Star.Count);
        _starRenderer.LedSelected += OnLedSelected;
        _viewModel.Star.Changed += OnStarChanged;
        _viewModel.Star.SelectedLedIndexChanged += OnSelectedLedIndexChanged;
    }

    private void OnLedSelected(int index)
    {
        _viewModel.SelectedLedIndex = index;
    }

    private void OnSelectedLedIndexChanged(object? sender, int index)
    {
        _starRenderer.UpdateColors(_viewModel.Star.LedColors, index);
    }

    private void OnStarChanged(object? sender, EventArgs e)
    {
        _starRenderer.UpdateColors(_viewModel.Star.LedColors, _viewModel.SelectedLedIndex);
    }

    // ===== HEX Input Validation =====

    private void HexValue_PreviewTextInput(object sender, TextCompositionEventArgs e)
    {
        var tb = (TextBox)sender;
        e.Handled = !HexValidator.CanAcceptInput(tb.Text, e.Text[0]);
    }

    private void HexValue_PreviewMouseUp(object sender, MouseButtonEventArgs e)
    {
        var tb = (TextBox)sender;
        var text = tb.Text.Trim();

        if (!HexValidator.IsValid(text))
        {
            _viewModel.HexValue = HexValidator.FormatHex((byte)_viewModel.Star.Red, (byte)_viewModel.Star.Green, (byte)_viewModel.Star.Blue);
        }
    }

    protected override void OnClosed(EventArgs e)
    {
        _starRenderer.ClearCache();
        base.OnClosed(e);
    }
}
