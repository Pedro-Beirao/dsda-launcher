#include "updateFuncs.h"
#include <mainwindow.h>

void updateLauncherDialog(bool manualReq)
{
    QSimpleUpdater::getInstance()->setModuleVersion(LAUNCHER_UPDATER, version);
    QSimpleUpdater::getInstance()->setNotifyOnUpdate(LAUNCHER_UPDATER, true);
    QSimpleUpdater::getInstance()->setNotifyOnFinish(LAUNCHER_UPDATER, manualReq);
    QSimpleUpdater::getInstance()->checkForUpdates(LAUNCHER_UPDATER);
}

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
    request.setTransferTimeout(10000);
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

void updateGameDialog(bool manualReq)
{
    QString current = getGameVersion();
    QString latest = getLatestGameVersion();

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
    else if (latest == "" && manualReq)
    {
        msgBox.setInformativeText("Failed to get information about the latest dsda-doom version. Try again later.");
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.exec();
    }
    else if (current != latest && latest != "")
    {
        msgBox.setInformativeText("Available: " + latest);
        QPushButton *buttonYes = msgBox.addButton("Update", QMessageBox::YesRole);
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.setDefaultButton(buttonYes);
        msgBox.exec();
        if (msgBox.clickedButton() == buttonYes) updateGame();
    }
    else if (manualReq)
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
                                        "open -na Terminal --args /tmp/dsda-updater-macos.sh"});
    // clang-format on
    process->deleteLater();
#elif defined(Q_OS_WIN)
    QDesktopServices::openUrl(QUrl(GAME_REPO));
#elif defined(Q_OS_LINUX)
    QDesktopServices::openUrl(QUrl(GAME_REPO));
#endif
}
