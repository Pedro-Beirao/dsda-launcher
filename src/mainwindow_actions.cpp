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

    updateLauncherDialog(true);
}

void MainWindow::on_actionCheckForUpdatesDsdadoom_triggered()
{
    if (!QSslSocket::supportsSsl())
    {
        showSSLDialog();
        return;
    }

    updateGameDialog(true);
}

void MainWindow::on_actionOpenSettings_triggered()
{
    settingsWindow->show();
    settingsWindow->activateWindow();
    settingsWindow->raise();
    setWindowTitleBar(settingsWindow->winId());
}

void MainWindow::on_actionTips_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("A few tips you should know (Some features may require the latest dsda-doom version):");
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
    setWindowTitleBar(historyListWindow->winId());
}
