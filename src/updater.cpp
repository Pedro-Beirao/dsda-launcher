#include "updater.h"
#include <mainwindow.h>

QString getLatestLauncherVersion()
{
    QString portversion = getGameVersion();

    QNetworkRequest request((QUrl(LAUNCHER_API)));
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

bool updateLauncherDialog(bool manualReq)
{

    QString current = version;
    QString latest = getLatestLauncherVersion();

    QMessageBox msgBox;
    msgBox.setText("DSDA-Launcher " + current);

    if (latest == "" && manualReq)
    {
        msgBox.setInformativeText("Failed to get information about the latest dsda-launcher version. Try again later.");
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.exec();
    }
    else if (current != latest && latest != "")
    {
        msgBox.setInformativeText("Available: " + latest +
                                  "\n\n"
                                  "This will open the website where you can download the latest version.");

        QPushButton *buttonYes = msgBox.addButton("Update", QMessageBox::YesRole);
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.setDefaultButton(buttonYes);
        msgBox.exec();
        if (msgBox.clickedButton() == buttonYes)
        {
            updateLauncher();
            return true;
        }
    }
    else if (manualReq)
    {
        msgBox.setInformativeText("Up to Date");
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.exec();
    }
    return false;
}

void updateLauncher() { QDesktopServices::openUrl(QUrl(LAUNCHER_REPO + "/releases/latest")); }

QString getGameVersion()
{
    QString path = getGamePath();

    if (QFile(path).exists())
    {
        QProcess process;
        process.setWorkingDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        process.start(path, {"-v"});
        process.waitForFinished();

        QList<QByteArray> output = process.readAll().split(' ');

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

bool updateGameDialog(bool manualReq)
{
    QString current = getGameVersion();
    QString latest = getLatestGameVersion();

    QMessageBox msgBox;
    msgBox.setText("DSDA-Doom " + current);

    if (current == "")
    {
#if defined(Q_OS_WIN)
        msgBox.setInformativeText("It seems you do not have dsda-doom installed.\n"
                                  "Make sure that the Launcher and dsda-doom are in the same folder  OR  click 'Install'"
                                  "\n\n"
                                  "This will download and extract the latest version to the current folder.\n"
                                  "A CMD window will appear to perform this action.");
#elif defined(Q_OS_MACOS)
        msgBox.setInformativeText("It seems you do not have dsda-doom installed.\n"
                                  "Click 'Install'"
                                  "\n\n"
                                  "This will download and install the latest version, inside the Launcher's App Bundle.\n"
                                  "A Terminal window will appear to perform this action.");
#elif defined(Q_OS_LINUX)
        msgBox.setInformativeText("It seems you do not have dsda-doom installed.\n"
                                  "Install dsda-doom using your prefered package manager (if available)  OR  Click 'Install'"
                                  "\n\n"
                                  "This will download and extract the latest version to the current folder.\n"
                                  "A Terminal window will appear to perform this action.");
#endif
        QPushButton *buttonYes = msgBox.addButton("Install", QMessageBox::YesRole);
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.setDefaultButton(buttonYes);
        msgBox.exec();
        if (msgBox.clickedButton() == buttonYes)
        {
            updateGame();
            return true;
        }
    }
    else if (latest == "" && manualReq)
    {
        msgBox.setInformativeText("Failed to get information about the latest dsda-doom version. Try again later.");
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.exec();
    }
    else if (current != latest && latest != "")
    {
#if defined(Q_OS_WIN)
        msgBox.setInformativeText("Available: " + latest +
                                  "\n\n"
                                  "This will download and extract the latest version to the current folder.\n"
                                  "A CMD window will appear to perform this action.");
#elif defined(Q_OS_MACOS)
        msgBox.setInformativeText("Available: " + latest +
                                  "\n\n"
                                  "This will download and install the latest version, inside the Launcher's App Bundle.\n"
                                  "A Terminal window will appear to perform this action.");
#elif defined(Q_OS_LINUX)
        msgBox.setInformativeText("Available: " + latest +
                                  "\n\n"
                                  "This will download and extract the latest version to the current folder.\n"
                                  "A Terminal window will appear to perform this action.");
#endif
        QPushButton *buttonYes = msgBox.addButton("Update", QMessageBox::YesRole);
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.setDefaultButton(buttonYes);
        msgBox.exec();
        if (msgBox.clickedButton() == buttonYes)
        {
            updateGame();
            return true;
        }
    }
    else if (manualReq)
    {
        msgBox.setInformativeText("Up to Date");
        msgBox.addButton("Close", QMessageBox::NoRole);
        msgBox.exec();
    }
    return false;
}

void updateGame()
{
#if defined(Q_OS_MAC)
    QProcess process;
    // clang-format off
    process.startDetached("sh", {"-c", "rm /tmp/dsda-updater-macos.sh;"
                                       "curl -L -o /tmp/dsda-updater-macos.sh " + GAME_UPDATER_MACOS + ";"
                                       "p2=" + launcherfolder + "/../Resources;"
                                       "p2=${p2//\\//\\\\/};"
                                       "sed -i -e s/'$1'/$p2/g /tmp/dsda-updater-macos.sh;"
                                       "chmod +x /tmp/dsda-updater-macos.sh;"
                                       "open -na Terminal --args /tmp/dsda-updater-macos.sh"});
    // clang-format on
#elif defined(Q_OS_WIN)
    QDesktopServices::openUrl(QUrl(GAME_REPO));
#elif defined(Q_OS_LINUX)
    QDesktopServices::openUrl(QUrl(GAME_REPO));
#endif
}
