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

// If the IWAD selected changes
void MainWindow::on_iwad_comboBox_currentIndexChanged(int index)
{
    QString selection = ui->iwad_comboBox->currentText();

    // These are episode/mission based. They need both warp boxes
    if (exmxIWADS.contains(selection))
    {
        ui->level_label->show();
        ui->level_lineEdit->show();
        ui->episode_label->setText("Episode");
    }
    else // These are map based. They need 1 warp box
    {
        ui->level_label->hide();
        ui->level_lineEdit->hide();
        ui->episode_label->setText("Level");
    }
}

void MainWindow::on_tooltip_pushButton_clicked()
{
    if (ui->tooltip_textBrowser->isHidden()) ui->tooltip_textBrowser->show();
    else ui->tooltip_textBrowser->hide();
}

void MainWindow::on_episode_lineEdit_textChanged(const QString &arg1) { enable_disable_skill_comboBox(); }

void MainWindow::setComplevelsList(QStringList list)
{
    ui->complevel_comboBox->clear();
    ui->complevel_comboBox->addItems(list);
}

void MainWindow::setMaxSkillLevel(int max)
{
    ui->difficulty_comboBox->clear();
    for (int i = 0; i <= max; i++)
    {
        if (i != 0) ui->difficulty_comboBox->addItem(QString::number(i));
        else ui->difficulty_comboBox->addItem(" ");
    }
    ui->difficulty_comboBox->setCurrentIndex(settings->value("skill").toInt());
}

void MainWindow::enable_disable_skill_comboBox()
{
    if (ui->episode_lineEdit->text().isEmpty())
    {
        ui->difficulty_comboBox->setEnabled(false);
        ui->difficulty_label->setEnabled(false);
        ui->difficulty_comboBox->setToolTip("Cannot select a Skill level\n"
                                            "without choosing a Map");
    }
    else if (!ui->playback_lineEdit->text().isEmpty())
    {
        ui->difficulty_comboBox->setEnabled(false);
        ui->difficulty_label->setEnabled(false);
        ui->difficulty_comboBox->setToolTip("Cannot select a Skill level\n"
                                            "during Demo playback");
    }
    else
    {
        ui->difficulty_comboBox->setEnabled(true);
        ui->difficulty_label->setEnabled(true);
        ui->difficulty_comboBox->setToolTip("");
    }
}
