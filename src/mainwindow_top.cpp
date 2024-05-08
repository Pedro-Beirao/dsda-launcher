#include "mainwindow.h"

QFileInfoList MainWindow::findIwads_possibleFiles()
{
    QFileInfoList possible_files;
    QString doomwaddirstr = QString(qgetenv("DOOMWADDIR"));

// Find the IWADs in the correct folder depending on the OS
#if defined Q_OS_MAC || defined Q_OS_LINUX
    if (!QDir(dotfolder).exists()) QDir().mkdir(dotfolder);

// Copies dsda-doom.wad to the dotfolder
#ifdef Q_OS_MAC
    QProcess::startDetached("cp", {execPath + "/../Resources/" + exeName + ".wad", dotfolder});
#endif

    QDir directory(dotfolder);
    possible_files = directory.entryInfoList(QStringList() << "*.WAD", QDir::Files);

    doomwaddirstr = doomwaddirstr.split(":")[0];
#elif Q_OS_WIN
    QDir directory = execPath;
    imagesInfo = directory.entryInfoList(QStringList() << "*.WAD", QDir::Files);

    doomwaddirstr = doomwaddirstr.split(";")[0];
#endif

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

void MainWindow::findIwads()
{
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
                ui->iwad_comboBox->addItem(file_name);
                ui->iwad_comboBox->setItemData(ui->iwad_comboBox->count() - 1, fileInfo.absoluteFilePath(), Qt::ToolTipRole);
                break;
            }
        }
    }
}
