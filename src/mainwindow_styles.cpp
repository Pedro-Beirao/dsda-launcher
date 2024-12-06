#include "mainwindow.h"

void MainWindow::setStyles()
{
    // Top
    enable_disable_skill_comboBox();

    // Options
    if (ui->hud_lineEdit->text().isEmpty()) ui->hud_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->hud_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    if (ui->config_lineEdit->text().isEmpty()) ui->config_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->config_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    // Demos
    if (ui->viddump_lineEdit->text().isEmpty()) ui->viddump_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->viddump_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    if (ui->playback_comboBox->currentIndex() != 1)
    {
        ui->viddump_lineEdit->setHidden(true);
        ui->viddump_pushButton->setHidden(true);
    }

    if (settings->value("theme") == "light") setLightStyle();
    else setDarkStyle();

#if defined Q_OS_WIN
    // From DoomRunner
    QWindow *focusWindow = qApp->focusWindow();
    QWindowList topLevelWindows = qApp->topLevelWindows();
    for (const QWindow *window : topLevelWindows)
    {
        HWND hWnd = reinterpret_cast<HWND>(window->winId());
        DWORD DWMWA_USE_IMMERSIVE_DARK_MODE = 20; // until Windows SDK 10.0.22000.0 (first Windows 11 SDK) this value is not defined
        BOOL useDarkMode = BOOL(settings->value("theme") == "dark");
        DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDarkMode, sizeof(useDarkMode));
        SetFocus(hWnd);
        ShowWindow(hwnd, SW_MINIMIZE);
        ShowWindow(hwnd, SW_RESTORE);
    }
    if (focusWindow)
    {
        HWND hWnd = reinterpret_cast<HWND>(focusWindow->winId());
        SetFocus(hWnd);
        ShowWindow(hwnd, SW_MINIMIZE);
        ShowWindow(hwnd, SW_RESTORE);
    }
#endif
}

void MainWindow::setLightStyle()
{
#if defined Q_OS_MACOS
    ui->showCommandLine_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
    ui->tooltip_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
    ui->additionalArguments_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
    ui->nextPage_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
    ui->previousPage_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
#endif
}

void MainWindow::setDarkStyle()
{
#if defined Q_OS_MACOS
    ui->showCommandLine_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
    ui->tooltip_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
    ui->additionalArguments_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
    ui->nextPage_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
    ui->previousPage_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
#endif
}
