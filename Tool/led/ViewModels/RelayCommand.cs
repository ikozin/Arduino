using System.Windows.Input;

namespace LedStarSimulator.ViewModels;

/// <summary>
/// Простая реализация ICommand для MVVM.
/// </summary>
public class RelayCommand : ICommand
{
    private readonly Action<object> _execute;
    private readonly Func<object, bool>? _canExecute;

    public RelayCommand(Action<object> execute, Func<object, bool>? canExecute = null)
    {
        _execute = execute ?? throw new ArgumentNullException(nameof(execute));
        _canExecute = canExecute;
    }

    public event EventHandler? CanExecuteChanged
    {
        add => CommandManager.RequerySuggested += value;
        remove => CommandManager.RequerySuggested -= value;
    }

    public bool CanExecute(object? parameter) => _canExecute?.Invoke(parameter ?? new()) ?? true;

    public void Execute(object? parameter) => _execute(parameter ?? new());
}
