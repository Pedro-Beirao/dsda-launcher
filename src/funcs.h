#ifndef FUNCS_H
#define FUNCS_H

#include "constants.h"
#include <QCommandLineParser>
#include <QDir>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QSettings>

extern QSettings *settings;

void openIWADsFolder();
QString getFileName(QString filePath);
QString getFilePath(QString fileName);
QStringList parseStringIntoArguments(QString line);
QString removeExtension(QString fileName);
QString getExtension(QString fileName);
QFileInfoList findIwads();

#endif // FUNCS_H
