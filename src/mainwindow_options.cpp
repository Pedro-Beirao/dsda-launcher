#include "mainwindow.h"

void MainWindow::on_nextPage_pushButton_clicked()
{
    ui->nextPage_pushButton->setText("-");
    nextStackedWidget();
}

void MainWindow::on_previousPage_pushButton_clicked()
{
    ui->previousPage_pushButton->setText("-");
    previousStackedWidget();
}

void MainWindow::nextStackedWidget()
{
    ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 1)->show();

    QPropertyAnimation *anim1 = new QPropertyAnimation(ui->stackedWidget->currentWidget(), "pos");
    anim1->setDuration(350);
    anim1->setEasingCurve(QEasingCurve::OutQuart);
    anim1->setStartValue(QPoint(0, 0));
    anim1->setEndValue(QPoint(-265, 0));

    QPropertyAnimation *anim2 = new QPropertyAnimation(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() + 1), "pos");
    anim2->setDuration(350);
    anim2->setEasingCurve(QEasingCurve::OutQuart);
    anim2->setStartValue(QPoint(265, 0));
    anim2->setEndValue(QPoint(0, 0));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(anim1);
    animgroup->addAnimation(anim2);

    animgroup->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animgroup, SIGNAL(finished()), this, SLOT(whenAnimationFinishNext()));
}

void MainWindow::previousStackedWidget()
{
    ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 1)->show();

    QPropertyAnimation *anim1 = new QPropertyAnimation(ui->stackedWidget->currentWidget(), "pos");
    anim1->setDuration(350);
    anim1->setEasingCurve(QEasingCurve::OutQuart);
    anim1->setStartValue(QPoint(0, 0));
    anim1->setEndValue(QPoint(265, 0));

    QPropertyAnimation *anim2 = new QPropertyAnimation(ui->stackedWidget->widget(ui->stackedWidget->currentIndex() - 1), "pos");
    anim2->setDuration(350);
    anim2->setEasingCurve(QEasingCurve::OutQuart);
    anim2->setStartValue(QPoint(-265, 0));
    anim2->setEndValue(QPoint(0, 0));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(anim1);
    animgroup->addAnimation(anim2);

    animgroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::whenAnimationFinishNext()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    ui->nextPage_pushButton->setText(">");
}

void MainWindow::whenAnimationFinishPrevious()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
    ui->previousPage_pushButton->setText("<");
}

void MainWindow::setToggles(QString t1, QString a1, QString t2, QString a2, QString t3, QString a3, QString t4, QString a4)
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

void MainWindow::setResolutionsList(QListWidget *list)
{
    ui->resolution_comboBox->clear();
    ui->resolution_comboBox->addItem(" ");
    for (int i = 0; i < list->count(); i++)
    {
        ui->resolution_comboBox->addItem(list->item(i)->text());
    }
}

void MainWindow::on_hud_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->hud_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    }
    else
    {
        ui->hud_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);
    }
}

void MainWindow::on_config_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        ui->config_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    }
    else
    {
        ui->config_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);
    }
}

void MainWindow::on_hud_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("DSDAHUD.lmp"), settings->value("hudfolder").toString(), tr("DSDAHUD file (*.lmp *.txt *)"));
    if (!fileName.isEmpty())
    {
        settings->setValue("hudfolder", fileName);
        ui->hud_lineEdit->setText(fileName);
    }
}

void MainWindow::on_config_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("dsda-doom.cfg"), settings->value("configfolder").toString(), tr("Config file (*.cfg *.txt *)"));
    if (!fileName.isEmpty())
    {
        settings->setValue("configfolder", fileName);
        ui->config_lineEdit->setText(fileName);
    }
}
