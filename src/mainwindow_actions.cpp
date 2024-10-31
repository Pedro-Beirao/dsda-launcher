#include "mainwindow.h"

// Main

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    // msgBox.setOption(QMessageBox::Option::DontUseNativeDialog);
    msgBox.setText(APP_NAME " " + version);
    msgBox.setInformativeText("<a href='" + LAUNCHER_REPO + "'>" + LAUNCHER_REPO + "</a>");
    msgBox.addButton(tr("Ok"), QMessageBox::NoRole);
    msgBox.exec();
}

void MainWindow::on_actionLoadState_triggered()
{
    QString fileNames = QFileDialog::getOpenFileName(this, tr("Load State"), settings->value("statefile").toString(), tr("state files (*.state)"));
    if (!fileNames.isEmpty())
    {
        settings->setValue("statefile", fileNames);
        states::loadStateFromFile(fileNames);
    }
}

void MainWindow::on_actionSaveState_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save State"), settings->value("statefile").toString(), tr("state files (*.state)"));
    if (!fileName.isEmpty())
    {
        settings->setValue("statefile", fileName);
        states::saveStateToFile(fileName);
    }
}

void MainWindow::on_actionGithubDsdalauncher_triggered() { QDesktopServices::openUrl(QUrl(LAUNCHER_REPO)); }

void MainWindow::on_actionGithubDsdadoom_triggered() { QDesktopServices::openUrl(QUrl(GAME_REPO)); }

void MainWindow::on_actionCheckForUpdatesDsdalauncher_triggered()
{
    if (!QSslSocket::supportsSsl())
    {
        showSSLDialog();
        return;
    }

    CheckForUpdates(true);
}

void MainWindow::on_actionCheckForUpdatesDsdadoom_triggered()
{
    if (!QSslSocket::supportsSsl())
    {
        showSSLDialog();
        return;
    }

    QString portversion;

    QString path = getGamePath();

    QFile port = QFile(path);
    if (port.exists())
    {
        QProcess *process = new QProcess;
        process->setWorkingDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        process->start(path, {"-v"});
        process->waitForFinished();

        QList output = process->readAll().split(' ');

        if (output.size() >= 2) portversion = output[1];
    }

    QNetworkRequest req0((QUrl(GAME_API)));
    req0.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json0;
    QNetworkAccessManager nam0;
    QNetworkReply *reply0 = nam0.get(req0);
    while (!reply0->isFinished())
    {
        qApp->processEvents();
    }
    QByteArray response_data = reply0->readAll();
    QJsonDocument jsondoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonobj = jsondoc.object();
    foreach (const QString &key, jsonobj.keys())
    {
        QJsonValue value = jsonobj.value(key);
        if (key == "name")
        {
            if (portversion != value.toString())
            {
                QMessageBox msgBox;
                msgBox.setText("DSDA-Doom " + portversion);
                msgBox.setInformativeText("Available: " + value.toString());
                QPushButton *pButtonYes;
                pButtonYes = msgBox.addButton(tr("Update"), QMessageBox::YesRole);
                msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                msgBox.setDefaultButton(pButtonYes);
                msgBox.exec();
                if (msgBox.clickedButton() == pButtonYes)
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
#endif
                }
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("DSDA-Doom " + portversion);
                msgBox.setInformativeText("Up to Date");
                msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                msgBox.exec();
            }
        }
    }

    reply0->deleteLater();
}

void MainWindow::on_actionOpenSettings_triggered()
{
    settingsWindow->show();
    settingsWindow->activateWindow();
    settingsWindow->raise();
}

void MainWindow::on_actionTips_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("A few tips you should know (Some features require dsda-doom v0.26):");
    msgBox.setInformativeText("- Drag .wad / .deh files on top of the launcher to add them to the loaded files"
                              "\n\n"
                              "- Drag .lmp files on top of the launcher to play the demo and autoselect the correct IWAD, PWADs and complevel"
                              "\n\n"
                              "- For the mentioned autoselect to work correctly, go to the settings and set the PWADs folders");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
void MainWindow::on_actionWhatIsThisState_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("State files");
    msgBox.setInformativeText("These .state files save all the parameters selected on the launcher, and lets you load them again whenever you need");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_actionExportCommand_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export command line"), settings->value("batfile").toString(), tr("batch files (*.bat *.sh *.zsh *.command)"));
    if (!fileName.isEmpty())
    {
        settings->setValue("batfile", fileName);
        on_launchGame_pushButton_clicked(true, fileName);
    }
}

void MainWindow::on_actionOpenIWADsFolder_triggered() { openIWADsFolder(); }

void MainWindow::on_actionOpenConsole_triggered() { on_console_pushButton_clicked(); }

void MainWindow::on_actionOpenHistory_triggered()
{
    if (historyListWindow->isHidden())
    {
        historyListWindow->getHistory();
    }
    historyListWindow->show();
    historyListWindow->activateWindow();
    historyListWindow->raise();
}
