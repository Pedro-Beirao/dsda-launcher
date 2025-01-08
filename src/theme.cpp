#include "theme.h"

void setWindowTitleBar(WId winId)
{
#if defined Q_OS_WIN
    // From DoomRunner
    // https://github.com/Youda008/DoomRunner/blob/dc423923c77d27f815b9af3a83c47d4c9161ffd8/Sources/Themes.cpp#L473
    HWND hWnd = reinterpret_cast<HWND>(winId);
    DWORD DWMWA_USE_IMMERSIVE_DARK_MODE = 20; // until Windows SDK 10.0.22000.0 (first Windows 11 SDK) this value is not defined
    BOOL useDarkMode = BOOL(settings->value("theme") == "dark");
    DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDarkMode, sizeof(useDarkMode));
    SetFocus(hWnd);
#endif
}

void setAllWindowsTitleBar()
{
#if defined Q_OS_WIN
    QWindow * focusWindow = qApp->focusWindow();
    QWindowList topLevelWindows = QApplication::topLevelWindows();
    for (const QWindow *window : topLevelWindows)
    {
        setWindowTitleBar(window->winId());
    }
    if (focusWindow)
    {
        SetFocus( reinterpret_cast< HWND >( focusWindow->winId() ) );
    }
#endif
}
