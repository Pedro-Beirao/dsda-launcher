#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QStandardPaths>
#include <QStringList>

const QString dsdalauncher_url = "https://github.com/Pedro-Beirao/dsda-launcher";
const QString dsdadoom_url = "https://github.com/kraflab/dsda-doom";

#ifdef Q_OS_WIN
const QChar folder_separator = '\\';
#else
const QChar folder_separator = '/';
#endif

#if defined Q_OS_MAC || defined Q_OS_LINUX
const QString dotfolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.dsda-doom";
#endif

const QStringList exmxIWADS = {"doom",    "doom1",    "doomu", "freedoom", "freedoom1", "bfgdoom", "bfgdoom1",

                               "heretic", "heretic1",

                               "chex",    "rekkrsa"};

const QStringList mapxxIWADS = {"doom2", "doom2f",   "freedoom2", "bfgdoom2",

                                "tnt",   "plutonia",

                                "hexen",

                                "hacx"};

const QStringList minimal_complevels = {"Default", "2 - Doom / Doom 2", "3 - Ultimate Doom", "4 - Final Doom", "9 - Boom", "11 - MBF", "21 - MBF 21"};
const QStringList full_complevels = {"Default", "0 - Doom v1.2", "1 - Doom v1.666", "2 - Doom / Doom 2", "3 - Ultimate Doom", "4 - Final Doom", "5 - DOSDoom", "6 - TASDoom", "7 - Boom's comp mode", "8 - Boom v2.01", "9 - Boom", "10 - LxDoom", "11 - MBF", "12 - PrBoom v2.03beta", "13 - PrBoom v2.1.0", "14 - PrBoom v2.1.1 - 2.2.6", "15 - PrBoom v2.3.x", "16 - PrBoom v2.4.0", "17 - Current PrBoom", "21 - MBF 21"};

const QStringList skills_list = {"", "ITYTD", "HNTR", "HMP", "UV", "Nightmare!"};

#endif // CONSTANTS_H
