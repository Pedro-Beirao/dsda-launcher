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

    QString path = getGamePath();

    QFile port(path);
    if (port.exists())
    {
#if defined Q_OS_MACOS
        QProcess process;
        process.startDetached("sh", {"-c", "rm /tmp/dsda-doom-params.sh; echo \"" + path + " --help\" > /tmp/dsda-doom-params.sh ; chmod +x /tmp/dsda-doom-params.sh ; open -a Terminal /tmp/dsda-doom-params.sh"});
#elif defined Q_OS_WIN
        system(("start cmd.exe /k \"" + path.toStdString() + "\" --help").c_str());
#else
        // xterm is the most reliable terminal to use, but it seems a few distros do not have it
        system(("xterm -e 'bash -c \"" + path.toStdString() + " --help ;bash\"'").c_str());
#endif
    }

    canLaunch = false;
    QTimer::singleShot(2000, this, SLOT(delayLaunch()));
}

void MainWindow::initializeIndicators()
{
    // ui->wadsSelected_indicator->setPixmap(QPixmap(":/pngs/pngs/wadsSelected_indicator.png").scaled(20, 20, Qt::KeepAspectRatio));
    connect(ui->wads_listWidget->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(show_hide_wadsSelected_indicator()));
    connect(ui->wads_listWidget->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(show_hide_wadsSelected_indicator()));
    connect(ui->wads_listWidget->model(), SIGNAL(modelReset()), this, SLOT(show_hide_wadsSelected_indicator()));
    show_hide_wadsSelected_indicator();

    connect(ui->record_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(show_hide_recordingDemo_indicator()));
    show_hide_recordingDemo_indicator();

    connect(ui->playback_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(show_hide_playingDemo_indicator()));
    show_hide_playingDemo_indicator();
}

void MainWindow::show_hide_wadsSelected_indicator()
{
    ui->wadsSelected_indicator->setVisible(ui->wads_listWidget->count() != 0);
    ui->wadsSelected_indicator->setText(QString::number(ui->wads_listWidget->count()));
    QString tooltip;
    for (int i = 0; i < ui->wads_listWidget->count(); i++)
    {
        tooltip.append(ui->wads_listWidget->item(i)->text());
        if (i != ui->wads_listWidget->count() - 1) tooltip.append("\n");
    }
    ui->wadsSelected_indicator->setToolTip(tooltip);
}

void MainWindow::show_hide_recordingDemo_indicator()
{
    ui->recordingDemo_indicator->setVisible(!ui->record_lineEdit->text().isEmpty());
    ui->recordingDemo_indicator->setToolTip("Recording " + getFileName(ui->record_lineEdit->text()));
}

void MainWindow::show_hide_playingDemo_indicator()
{
    ui->playingDemo_indicator->setVisible(!ui->playback_lineEdit->text().isEmpty());
    ui->playingDemo_indicator->setToolTip("Playing  " + getFileName(ui->playback_lineEdit->text()));
}
