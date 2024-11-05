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

QString getGameVersion();
QString getLatestGameVersion();
void updateGameDialog(bool ManualReq);
void updateGame();
void updateLauncherDialog(bool manualReq);

#endif // UPDATEFUNCS_H
