#ifndef UPDATEFUNCS_H
#define UPDATEFUNCS_H

#include "constants.h"
#include "funcs.h"
#include <QCommandLineParser>
#include <QDir>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QSettings>
#include <QSimpleUpdater.h>

QString getLatestLauncherVersion();
bool updateLauncherDialog(bool manualReq);
void updateLauncher();

QString getGameVersion();
QString getLatestGameVersion();
bool updateGameDialog(bool ManualReq);
void updateGame();

#endif // UPDATEFUNCS_H
