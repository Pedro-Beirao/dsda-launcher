#include "mainwindow.h"

void MainWindow::setStyles()
{
    // Top
    enable_disable_skill_comboBox();

    // Options
    if (ui->hud_lineEdit->text().isEmpty()) ui->hud_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->hud_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    if (ui->config_lineEdit->text().isEmpty()) ui->config_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->config_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    // Demos
    if (ui->viddump_lineEdit->text().isEmpty()) ui->viddump_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    else ui->viddump_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);

    if (ui->playback_comboBox->currentIndex() != 1)
    {
        ui->viddump_lineEdit->setHidden(true);
        ui->viddump_pushButton->setHidden(true);
    }

    if (settings->value("theme") == "light") setLightStyle();
    else setDarkStyle();
}

void MainWindow::setLightStyle()
{
#if defined Q_OS_MACOS
    ui->showCommandLine_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
    ui->tooltip_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
    ui->additionalArguments_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
    ui->nextPage_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
    ui->previousPage_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
#endif
}

void MainWindow::setDarkStyle()
{
#if defined Q_OS_MACOS
    ui->showCommandLine_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
    ui->tooltip_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
    ui->additionalArguments_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
    ui->nextPage_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
    ui->previousPage_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
#endif
}
