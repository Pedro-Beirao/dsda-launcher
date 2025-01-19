#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDir>
#include <QStandardPaths>
#include <QStringList>

const QString version = "v1.4";

const QString LAUNCHER_REPO = "https://github.com/Pedro-Beirao/dsda-launcher";
const QString LAUNCHER_API = "https://api.github.com/repos/Pedro-Beirao/dsda-launcher/releases/latest";
const QString LAUNCHER_UPDATER = "https://raw.githubusercontent.com/Pedro-Beirao/dsda-launcher/refs/heads/master/updater/updater.json";

const QString GAME_REPO = "https://github.com/kraflab/dsda-doom";
const QString GAME_API = "https://api.github.com/repos/kraflab/dsda-doom/releases/latest";
const QString GAME_UPDATER_MACOS = "https://raw.githubusercontent.com/Pedro-Beirao/dsda-launcher/refs/heads/master/updater/dsda-updater-macos.sh";
const QString GAME_UPDATER_WINDOWS = "https://raw.githubusercontent.com/Pedro-Beirao/dsda-launcher/refs/heads/master/updater/dsda-updater-windows.bat";

#if defined Q_OS_WIN
const QChar FOLDER_SEPARATOR = '\\';
#else
const QChar FOLDER_SEPARATOR = '/';
#endif

extern QString gameName;
extern QString datafolder;
extern QString launcherfolder;

const QStringList exmxIWADS = {"doom",    "doom1",    "doomu", "freedoom", "freedoom1", "bfgdoom", "bfgdoom1",

                               "heretic", "heretic1",

                               "chex",    "rekkrsa"};

const QStringList mapxxIWADS = {"doom2", "doom2f",   "freedoom2", "bfgdoom2",

                                "tnt",   "plutonia",

                                "hexen",

                                "hacx"};

const QStringList MINIMAL_COMPLEVELS = {"Default", "2 - Doom / Doom 2", "3 - Ultimate Doom", "4 - Final Doom", "9 - Boom", "11 - MBF", "21 - MBF 21"};
const QStringList FULL_COMPLEVELS = {"Default", "0 - Doom v1.2", "1 - Doom v1.666", "2 - Doom / Doom 2", "3 - Ultimate Doom", "4 - Final Doom", "5 - DOSDoom", "6 - TASDoom", "7 - Boom's comp mode", "8 - Boom v2.01", "9 - Boom", "10 - LxDoom", "11 - MBF", "12 - PrBoom v2.03beta", "13 - PrBoom v2.1.0", "14 - PrBoom v2.1.1 - 2.2.6", "15 - PrBoom v2.3.x", "16 - PrBoom v2.4.0", "17 - Current PrBoom", "21 - MBF 21"};

const QStringList SKILLS_LIST = {"", "ITYTD", "HNTR", "HMP", "UV", "Nightmare!"};

const QString DEFAULT_TOGGLE1TEXT = "Fast Monsters";
const QString DEFAULT_TOGGLE1ARG = "-fast";

const QString DEFAULT_TOGGLE2TEXT = "No Monsters";
const QString DEFAULT_TOGGLE2ARG = "-nomonsters";

const QString DEFAULT_TOGGLE3TEXT = "Respawn Monsters";
const QString DEFAULT_TOGGLE3ARG = "-respawn";

const QString DEFAULT_TOGGLE4TEXT = "Solo-Net";
const QString DEFAULT_TOGGLE4ARG = "-solo-net";

const QString STATE_HEADER = "dsdalauncherstatev2";
const QString HISTORY_HEADER = "dsdalauncherhistoryv2";

void findDataFolder();

#endif // CONSTANTS_H
