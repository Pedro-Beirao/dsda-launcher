#include "constants.h"

QString gameName = "";
QString datafolder = "";
QString launcherfolder = "";

void findDataFolder()
{
#if defined(Q_OS_WIN)
    datafolder = launcherfolder;
#else
    QString dotfolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.dsda-doom";
    if (QDir(dotfolder).exists())
    {
        datafolder = dotfolder;
    }
    else
    {
#if defined(Q_OS_MACOS)
        datafolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Library/Application Support/dsda-doom";
#elif defined(Q_OS_LINUX)

        QString xdg_data_home = QString(qgetenv("XDG_DATA_HOME"));
        if (!xdg_data_home.isEmpty())
        {
            datafolder = xdg_data_home;
        }
        else
        {
            datafolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.local/share/dsda-doom";
        }
#endif
    }

    if (!QDir(datafolder).exists()) QDir().mkdir(datafolder);

#endif
}
