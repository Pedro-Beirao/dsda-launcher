#include "mainwindow.h"

// Show the console
void MainWindow::on_console_pushButton_clicked()
{
    consoleWindow->show();
    consoleWindow->activateWindow();
    consoleWindow->raise();
}

void MainWindow::on_additionalArguments_pushButton_clicked()
{
    if (!canLaunch) return;

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
#ifdef __APPLE__
        QProcess *process = new QProcess;
        process->startDetached("sh", {"-c", "echo \"" + path + " --help ; rm /tmp/dsda-doom-params.sh\" > /tmp/dsda-doom-params.sh ; chmod +x /tmp/dsda-doom-params.sh ; open -a Terminal /tmp/dsda-doom-params.sh"});
        process->deleteLater();
#elif _WIN32
        system(("start cmd.exe /k \"" + path.toStdString() + "\" --help").c_str());
#else
        // xterm is the most reliable terminal to use, but it seems a few distros do not have it
        system(("xterm -e 'bash -c \"" + path.toStdString() + " --help ;bash\"'").c_str());
#endif
    }

    canLaunch = false;
    QTimer::singleShot(2000, this, SLOT(delayLaunch()));
}
