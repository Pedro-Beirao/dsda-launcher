#include "mainwindow.h"

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

void MainWindow::on_actionGithubDsdalauncher_triggered() { QDesktopServices::openUrl(QUrl(DSDALAUNCHER_URL)); }

void MainWindow::on_actionGithubDsdadoom_triggered() { QDesktopServices::openUrl(QUrl(DSDADOOM_URL)); }

void MainWindow::on_actionCheckForUpdatesDsdalauncher_triggered()
{
    if (!QSslSocket::supportsSsl())
    {
        showSSLDialog();
        return;
    }

    QNetworkRequest req((QUrl(DSDALAUNCHER_API_URL)));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.get(req);
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    QByteArray response_data = reply->readAll();
    QJsonDocument jsondoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonobj = jsondoc.object();
    foreach (const QString &key, jsonobj.keys())
    {
        QJsonValue value = jsonobj.value(key);
        if (key == "name")
        {
            if (version != value.toString())
            {
                QMessageBox msgBox;
                msgBox.setText("DSDA-Launcher " + version);
                msgBox.setInformativeText("Available: " + value.toString());
                QPushButton *pButtonYes = msgBox.addButton(tr("Update"), QMessageBox::YesRole);
                msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                msgBox.setDefaultButton(pButtonYes);
                msgBox.exec();
                if (msgBox.clickedButton() == pButtonYes)
                {
                    QDesktopServices::openUrl(QUrl(DSDALAUNCHER_DOWNLOAD_URL));
                }
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("DSDA-Launcher " + version);
                msgBox.setInformativeText("Up to Date");
                msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                msgBox.exec();
            }
        }
    }

    reply->deleteLater();
}

void MainWindow::on_actionCheckForUpdatesDsdadoom_triggered()
{
    if (!QSslSocket::supportsSsl())
    {
        showSSLDialog();
        return;
    }

    QString portversion;

    QString path;

#ifdef __APPLE__
    path = execPath + "/../Resources/" + exeName;
#elif __linux__
    path = execPath + "/" + exeName;
#else
    path = execPath + "/" + exeName + ".exe";
#endif
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

    QNetworkRequest req0((QUrl(DSDADOOM_API_URL)));
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
                    QDesktopServices::openUrl(QUrl(DSDADOOM_DOWNLOAD_URL));
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
    msgBox.setText("A few tips you should know:");
    msgBox.setInformativeText("- Drag .wad / .deh files on top of the launcher to add them to the loaded files\n\n- Drag .lmp files on top of the launcher to play the demo and autoselect the correct IWAD, PWADs and complevel\n\n- For the mentioned autoselect to work correctly, go to the settings and set the PWADs folders");
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
    if (fileName != "")
    {
        settings->setValue("batfile", fileName);
        on_launchGame_pushButton_clicked(false, true, fileName);
    }
}

void MainWindow::on_actionOpenIWADsFolder_triggered() { foo(); }

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
