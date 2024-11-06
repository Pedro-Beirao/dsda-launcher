#ifndef UPDATER_H
#define UPDATER_H

#include "constants.h"
#include "funcs.h"
#include <QCommandLineParser>
#include <QDir>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QSettings>
#include <QtNetwork>

QString getLatestLauncherVersion();
bool updateLauncherDialog(bool manualReq);
void updateLauncher();

QString getGameVersion();
QString getLatestGameVersion();
bool updateGameDialog(bool ManualReq);
void updateGame();

#endif // UPDATER_H
