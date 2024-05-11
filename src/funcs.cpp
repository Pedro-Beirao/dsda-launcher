#include "funcs.h"

void openIWADsFolder() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
#ifdef __APPLE__
    QProcess::startDetached("open", {dotfolder});
#elif __linux__
    QProcess::startDetached("xdg-open", {dotfolder});
#else
    QProcess::startDetached("explorer.exe", {execPath});
#endif
}

QString getFileName(QString filePath)
{
#ifdef _WIN32
    return filePath.section(FOLDER_SEPARATOR, -1, -1);
#else
    return filePath.section(FOLDER_SEPARATOR, -1, -1);
#endif
}

QString getFilePath(QString fileName)
{
    // Find file in dsda folder
    QString dsda_folder;
#ifdef _WIN32
    dsda_folder = execPath;
#else
    dsda_folder = dotfolder;
#endif
    QDir dsda_folder_path(dsda_folder);
    QStringList dsda_folder_files_list = dsda_folder_path.entryList(QDir::Files);

    foreach (QString file_in_dsda_folder, dsda_folder_files_list)
    {
        if (fileName == file_in_dsda_folder.toLower())
        {
            return (dsda_folder + FOLDER_SEPARATOR + file_in_dsda_folder);
        }
    }

    // Find file in DOOMWADPATH
    QString doomwadpath = QString(qgetenv("DOOMWADPATH"));
#ifdef _WIN32
    QChar token = ';';
#else
    QChar token = ':';
#endif

    QStringList doomwadpath_folders_list = doomwadpath.split(token);
    foreach (QString doomwadpath_folder, doomwadpath_folders_list)
    {
        QStringList doomwadpath_folder_files_list = QDir(doomwadpath_folder).entryList(QDir::Files);
        foreach (QString file_in_doomwadpath_folder, doomwadpath_folder_files_list)
        {
            if (fileName == file_in_doomwadpath_folder.toLower())
            {
                return (doomwadpath_folder + FOLDER_SEPARATOR + file_in_doomwadpath_folder);
            }
        }
    }

    // Find file in the pwadfolders
    int size = settings->beginReadArray("pwadfolders");
    for (int j = 0; j < size; j++)
    {
        settings->setArrayIndex(j);
        QString folder = settings->value("folder").toString();
        if (folder != "")
        {
            QDir folder_path(folder);
            QStringList folder_files_list = folder_path.entryList(QDir::Files);
            foreach (QString file_in_folder, folder_files_list)
            {
                if (fileName == file_in_folder.toLower())
                {
                    settings->endArray();
                    return (folder + FOLDER_SEPARATOR + file_in_folder);
                }
            }
        }
    }
    settings->endArray();

    return "";
}
