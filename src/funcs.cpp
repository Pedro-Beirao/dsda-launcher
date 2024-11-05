#include "funcs.h"
#include <mainwindow.h>

QString getGamePath()
{
#if defined(Q_OS_WIN)
    return launcherfolder + "\\" + gameName + ".exe";
#elif defined(Q_OS_LINUX)
    QProcess whichProcess;
    whichProcess.start("which", QStringList(gameName));
    whichProcess.waitForFinished();
    if (whichProcess.readAllStandardOutput() != "")
    {
        return gameName;
    }
    else
    {
        return launcherfolder + "/" + gameName;
    }
#elif defined(Q_OS_MACOS)
    return launcherfolder + "/../Resources/" + gameName;
#endif
}

void openIWADsFolder() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
#if defined Q_OS_MACOS
    QProcess::startDetached("open", {datafolder});
#elif defined Q_OS_LINUX
    QProcess::startDetached("xdg-open", {datafolder});
#else
    QProcess::startDetached("explorer.exe", {datafolder});
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

    // Find file in pwad tab
    QStringList pwads_in_tab;
    for (int i = 0; i < MainWindow::pMainWindow->wads_listWidget()->count(); i++)
    {
        files.append(QFileInfo(MainWindow::pMainWindow->wads_listWidget()->item(i)->toolTip()));
    }

    // Find file in datafolder
    QDir datafolder_dir(datafolder);
    files.append(datafolder_dir.entryInfoList(QStringList() << "*.WAD"
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

    QDir dsda_folder_path(datafolder);
    QStringList dsda_folder_files_list = dsda_folder_path.entryList(QDir::Files);

    foreach (QString file_in_dsda_folder, dsda_folder_files_list)
    {
        if (fileName == file_in_dsda_folder.toLower())
        {
            return (datafolder + FOLDER_SEPARATOR + file_in_dsda_folder);
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

    QDir directory(datafolder);
    QString doomwaddirstr = QString(qgetenv("DOOMWADDIR"));

// Find the IWADs in the correct folder depending on the OS
#if defined(Q_OS_MACOS) || defined(Q_OS_LINUX)
    doomwaddirstr = doomwaddirstr.split(":")[0];
#elif defined(Q_OS_WIN)
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

QString createLevelString(QString warp_1, QString warp_2)
{
    QString level;
    if (!warp_1.isEmpty() && !warp_2.isEmpty())
    {
        level = "E" + warp_1 + "M" + warp_2;
    }
    else if (!warp_1.isEmpty() && warp_2.isEmpty())
    {
        if (warp_1.size() == 1)
        {
            level = "MAP0" + warp_1;
        }
        else
        {
            level = "MAP" + warp_1;
        }
    }
    return level;
}

QStringList parseStringIntoArguments(QString line) { return QProcess::splitCommand(line); }

QString bool_to_string(bool b) { return b ? "true" : "false"; }
bool string_to_bool(QString s) { return s == "true" ? true : false; }

QString getGameVersion()
{
    QString path = getGamePath();

    if (QFile(path).exists())
    {
        QProcess *process = new QProcess;
        process->setWorkingDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        process->start(path, {"-v"});
        process->waitForFinished();
        process->deleteLater();

        QList output = process->readAll().split(' ');

        if (output.size() >= 2) return output[1];
        else return "";
    }
    else return "";
}

QString getLatestGameVersion()
{

    QString portversion = getGameVersion();

    QNetworkRequest request((QUrl(GAME_API)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.get(request);
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    QJsonObject jsonobj = QJsonDocument::fromJson(reply->readAll()).object();
    foreach (const QString &key, jsonobj.keys())
    {
        QJsonValue value = jsonobj.value(key);
        if (key == "name")
        {
            return value.toString();
        }
    }

    reply->deleteLater();
    return "";
}

void updateGameDialog(QString current, QString latest)
{
    QMessageBox msgBox;
    msgBox.setText("DSDA-Doom " + current);

    if (current == "")
    {
#if defined(Q_OS_WIN)
        msgBox.setInformativeText("It seems you do not have dsda-doom installed.\n"
                                  "Make sure that the Launcher and dsda-doom are in the same folder  OR  click 'Install' and dsda-doom " +
                                  latest + " will be installed in the current folder.");
#elif defined(Q_OS_MACOS)
        msgBox.setInformativeText("It seems you do not have dsda-doom installed.\n"
                                  "Click 'Install' and dsda-doom " +
                                  latest + " will be installed inside the Launcher's App Bundle");
#elif defined(Q_OS_LINUX)
        msgBox.setInformativeText("It seems you do not have dsda-doom installed.\n"
                                  "Install dsda-doom using your prefered package manager (if available)  OR  Click 'Install' and dsda-doom " +
                                  latest + " will be installed");
#endif
        QPushButton *buttonYes = msgBox.addButton("Install", QMessageBox::YesRole);
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.setDefaultButton(buttonYes);
        msgBox.exec();
        if (msgBox.clickedButton() == buttonYes) updateGame();
    }
    else if (latest == "")
    {
        msgBox.setInformativeText("Failed to get information about the latest dsda-doom version. Try again later.");
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.exec();
    }
    else if (current != latest)
    {
        msgBox.setInformativeText("Available: " + latest);
        QPushButton *buttonYes = msgBox.addButton("Update", QMessageBox::YesRole);
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.setDefaultButton(buttonYes);
        msgBox.exec();
        if (msgBox.clickedButton() == buttonYes) updateGame();
    }
    else
    {
        msgBox.setInformativeText("Up to Date");
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.exec();
    }
}

void updateGame()
{
#if defined(Q_OS_MAC)
    QProcess *process = new QProcess;
    // clang-format off
    process->startDetached("sh", {"-c", "rm /tmp/dsda-updater-macos.sh;"
                                        "curl -L -o /tmp/dsda-updater-macos.sh " + GAME_UPDATER_MACOS + ";"
                                        "p2=" + launcherfolder + "/../Resources;"
                                        "p2=${p2//\\//\\\\/};"
                                        "sed -i -e s/'$1'/$p2/g /tmp/dsda-updater-macos.sh;"
                                        "chmod +x /tmp/dsda-updater-macos.sh;"
                                        "open -a Terminal --args /tmp/dsda-updater-macos.sh"});
    // clang-format on
    process->deleteLater();
#elif defined(Q_OS_WIN)
    QDesktopServices::openUrl(QUrl(GAME_REPO));
#elif defined(Q_OS_LINUX)
    QDesktopServices::openUrl(QUrl(GAME_REPO));
#endif
}
