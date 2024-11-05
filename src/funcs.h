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

QString getGamePath();
void openIWADsFolder();
QString getFileName(QString filePath);
QFileInfoList getFilePath_possibleFiles();
QString getFilePath(QString fileName);
QStringList parseStringIntoArguments(QString line);
QString removeExtension(QString fileName);
QString getExtension(QString fileName);
QFileInfoList findIwads_possibleFiles();
QFileInfoList findIwads();
QString bool_to_string(bool b);
bool string_to_bool(QString s);
QString createLevelString(QString warp_1, QString warp_2);
#endif // FUNCS_H
