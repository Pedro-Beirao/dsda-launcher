#ifndef FUNCS_H
#define FUNCS_H

#include "constants.h"
#include <QDir>
#include <QProcess>
#include <QSettings>

extern QSettings *settings;

void openIWADsFolder();
QString getFileName(QString filePath);
QString getFilePath(QString fileName);

#endif // FUNCS_H
