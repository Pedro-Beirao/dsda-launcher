#include "mainwindow.h"

// If the IWAD selected changes
void MainWindow::on_iwad_comboBox_currentIndexChanged(int index)
{
    QString selection = ui->iwad_comboBox->currentText();

    // These are episode/mission based. They need both warp boxes
    if (exmxIWADS.contains(selection))
    {
        ui->level_label->show();
        ui->level_lineEdit->show();
        ui->episode_label->setText("Episode");
    }
    else // These are map based. They need 1 warp box
    {
        ui->level_label->hide();
        ui->level_lineEdit->hide();
        ui->episode_label->setText("Level");
    }
}

void MainWindow::on_tooltip_pushButton_clicked()
{
    if (ui->tooltip_textBrowser->isHidden()) ui->tooltip_textBrowser->show();
    else ui->tooltip_textBrowser->hide();
}

void MainWindow::on_episode_lineEdit_textChanged(const QString &arg1) { enable_disable_skill_comboBox(); }

void MainWindow::setComplevelsList(QStringList list)
{
    ui->complevel_comboBox->clear();
    ui->complevel_comboBox->addItems(list);
}

void MainWindow::enable_disable_skill_comboBox()
{
    if (ui->episode_lineEdit->text().isEmpty())
    {
        ui->difficulty_comboBox->setEnabled(false);
        ui->difficulty_label->setEnabled(false);
        ui->difficulty_comboBox->setToolTip("Cannot select a Skill level\n"
                                            "without choosing a Map");
    }
    else if (!ui->playback_lineEdit->text().isEmpty())
    {
        ui->difficulty_comboBox->setEnabled(false);
        ui->difficulty_label->setEnabled(false);
        ui->difficulty_comboBox->setToolTip("Cannot select a Skill level\n"
                                            "during Demo playback");
    }
    else
    {
        ui->difficulty_comboBox->setEnabled(true);
        ui->difficulty_label->setEnabled(true);
        ui->difficulty_comboBox->setToolTip("");
    }
}

void MainWindow::enable_disable_complevel_comboBox()
{
    if (!ui->playback_lineEdit->text().isEmpty())
    {
        ui->complevel_comboBox->setEnabled(false);
        ui->complevel_label->setEnabled(false);
        ui->complevel_comboBox->setToolTip("Cannot select a complevel\n"
                                           "during demo playback");
    }
    else
    {
        ui->complevel_comboBox->setEnabled(true);
        ui->complevel_label->setEnabled(true);
        ui->complevel_comboBox->setToolTip("");
    }
}
