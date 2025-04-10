#include "mainwindow.h"

void MainWindow::on_record_pushButton_clicked() // Record demo
{
    QString demoName = QFileDialog::getSaveFileName(this, tr("Demo file"), settings->value("demofolder").toString(), tr("Demo files (*.lmp);;All files(*)"));
    settings->setValue("demofolder", demoName);
    ui->record_lineEdit->setText(demoName);
}

void MainWindow::on_playback_pushButton_clicked() // Play demo
{
    QString demoName = QFileDialog::getOpenFileName(this, tr("Demo file"), settings->value("demofolder").toString(), tr("Demo files (*.lmp);;All files(*)"));
    settings->setValue("demofolder", demoName);
    ui->playback_lineEdit->setText(demoName);
}

void MainWindow::on_viddump_pushButton_clicked()
{
    QString vidName = QFileDialog::getSaveFileName(this, tr("mp4 / mkv"), settings->value("viddumpfolder").toString(), tr("Video files(*.mp4 *.mkv);;All files(*)"));
    settings->setValue("viddumpfolder", vidName);
    ui->viddump_lineEdit->setText(vidName);
}

void MainWindow::on_playback_comboBox_currentIndexChanged(int index)
{
    if (index == 1) // if -timedemo
    {
        ui->viddump_lineEdit->setHidden(false);
        ui->viddump_pushButton->setHidden(false);
    }
    else
    {
        ui->viddump_lineEdit->setHidden(true);
        ui->viddump_pushButton->setHidden(true);
    }
}

void MainWindow::on_playback_lineEdit_textChanged(const QString &arg1)
{
    enable_disable_skill_comboBox();
    enable_disable_complevel_comboBox();
}

void MainWindow::on_viddump_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->viddump_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    }
    else
    {
        ui->viddump_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);
    }
}
