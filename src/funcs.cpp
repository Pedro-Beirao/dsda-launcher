#include "funcs.h"

void openIWADsFolder() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
#if defined Q_OS_MACOS
    QProcess::startDetached("open", {dotfolder});
#elif defined Q_OS_LINUX
    QProcess::startDetached("xdg-open", {dotfolder});
#else
    QProcess::startDetached("explorer.exe", {launcherfolder});
#endif
}

QString getFileName(QString filePath)
{
#if defined Q_OS_WIN
    return filePath.section(FOLDER_SEPARATOR, -1, -1);
#else
    return filePath.section(FOLDER_SEPARATOR, -1, -1);
#endif
}

QFileInfoList getFilePath_possibleFiles()
{
    QFileInfoList files;

    // Find file in dsda folder
#if defined Q_OS_WIN
    QDir dsda_folder(launcherfolder);
#else
    QDir dsda_folder(dotfolder);
#endif

    files.append(dsda_folder.entryInfoList(QStringList() << "*.WAD"
                                                         << "*.DEH"
                                                         << "*.BEX",
                                           QDir::Files));

    // Find file in DOOMWADPATH
    QString doomwadpath = QString(qgetenv("DOOMWADPATH"));
#if defined Q_OS_WIN
    QChar token = ';';
#else
    QChar token = ':';
#endif
    QStringList doomwadpath_folders_list = doomwadpath.split(token);
    foreach (QString doomwadpath_folder, doomwadpath_folders_list)
    {
        files.append(QDir(doomwadpath_folder)
                         .entryInfoList(QStringList() << "*.WAD"
                                                      << "*.DEH"
                                                      << "*.BEX",
                                        QDir::Files));
    }

    // Find file in the pwadfolders
    int size = settings->beginReadArray("pwadfolders");
    for (int j = 0; j < size; j++)
    {
        settings->setArrayIndex(j);
        QString folder = settings->value("folder").toString();
        if (!folder.isEmpty())
        {
            files.append(QDir(folder).entryInfoList(QStringList() << "*.WAD"
                                                                  << "*.DEH"
                                                                  << "*.BEX",
                                                    QDir::Files));
        }
    }
    settings->endArray();

    return files;
}

QString getFilePath(QString fileName)
{
    getFilePath_possibleFiles();
    fileName = fileName.toLower();

    // Find file in dsda folder
    QString dsda_folder;
#if defined Q_OS_WIN
    dsda_folder = launcherfolder;
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
#if defined Q_OS_WIN
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
        if (!folder.isEmpty())
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

QString removeExtension(QString fileName)
{
    int dot_pos = fileName.lastIndexOf('.');
    if (dot_pos == -1) return fileName;

    return fileName.left(dot_pos);
}

QString getExtension(QString fileName)
{
    int dot_pos = fileName.lastIndexOf('.');
    if (dot_pos == -1) return "";

    return fileName.mid(dot_pos + 1);
}

QFileInfoList findIwads_possibleFiles()
{
    QFileInfoList possible_files;
    QString doomwaddirstr = QString(qgetenv("DOOMWADDIR"));

// Find the IWADs in the correct folder depending on the OS
#if defined(Q_OS_MACOS) || defined(Q_OS_LINUX)
    if (!QDir(dotfolder).exists()) QDir().mkdir(dotfolder);

    QDir directory(dotfolder);

    doomwaddirstr = doomwaddirstr.split(":")[0];

#elif defined(Q_OS_WIN)
    QDir directory(launcherfolder);

    doomwaddirstr = doomwaddirstr.split(";")[0];
#endif

    possible_files = directory.entryInfoList(QStringList() << "*.WAD", QDir::Files);

    QDir doomwaddir(doomwaddirstr);
    possible_files += doomwaddir.entryInfoList(QStringList() << "*.WAD", QDir::Files);

    int size = settings->beginReadArray("iwadfolders");
    for (int i = 0; i < size; i++)
    {
        settings->setArrayIndex(i);
        QString folder = settings->value("folder").toString();
        if (!folder.isEmpty())
        {
            possible_files += QDir(folder).entryInfoList(QStringList() << "*.WAD", QDir::Files);
        }
    }
    settings->endArray();

    return possible_files;
}

QFileInfoList findIwads()
{
    QFileInfoList ret;
    QFileInfoList possible_files = findIwads_possibleFiles();

    // This makes sure that a logical order to display the IWADs is followed
    // I think doing this is better than having random orders like: Doom 2 -> TNT -> Doom
    QStringList IWADS = exmxIWADS + mapxxIWADS;

    for (int i = 0; i < IWADS.size(); i++)
    {
        for (QFileInfo &fileInfo : possible_files)
        {
            QString file_name = fileInfo.baseName().toLower();
            if (IWADS[i] == file_name)
            {
                ret.append(fileInfo);
                break;
            }
        }
    }

    return ret;
}

QStringList parseStringIntoArguments(QString line) { return QProcess::splitCommand(line); }

QString bool_to_string(bool b) { return b ? "true" : "false"; }
bool string_to_bool(QString s) { return s == "true" ? true : false; }
