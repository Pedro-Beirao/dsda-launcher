#include "mainwindow.h"

void MainWindow::changeToggles(QString t1, QString a1, QString t2, QString a2, QString t3, QString a3, QString t4, QString a4)
{
    ui->toggle1_checkBox->setText(t1);
    ui->toggle1_checkBox->setToolTip(a1);

    ui->toggle2_checkBox->setText(t2);
    ui->toggle2_checkBox->setToolTip(a2);

    ui->toggle3_checkBox->setText(t3);
    ui->toggle3_checkBox->setToolTip(a3);

    ui->toggle4_checkBox->setText(t4);
    ui->toggle4_checkBox->setToolTip(a4);
}
