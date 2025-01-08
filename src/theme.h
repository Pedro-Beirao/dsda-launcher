#ifndef THEME_H
#define THEME_H

#include <QApplication>
#include <QSettings>
#include <QWindow>

#if defined Q_OS_WIN
#include <dwmapi.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#endif

extern QSettings *settings;

void setWindowTitleBar(WId winId);
void setAllWindowsTitleBar();

#endif // THEME_H
