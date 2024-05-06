#include "states.h"
#include "mainwindow.h"

states::states(QObject *parent)
    : QObject{parent}
{

}

void states::loadStateFromFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream stream(&file);

    loadState(stream);

    file.close();
}

void states::loadStateFromString(QString string)
{
    QTextStream stream(&string);
    loadState(stream);
}

void states::loadState(QTextStream &stream)
{
    MainWindow *ui = MainWindow::pMainWindow;

    QString buffer;

    stream.readLineInto(&buffer);
    stream.readLineInto(&buffer);
    stream.readLineInto(&buffer);
    if (buffer.mid(0, 5) == "iwad=") // iwad
    {
        for (int i = 0; i < ui->iwad_comboBox()->count(); i++)
        {
            if (ui->iwad_comboBox()->itemText(i) == buffer.mid(5))
            {
                ui->iwad_comboBox()->setCurrentIndex(i);
            }
        }
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 10) == "complevel=") // complevel
    {
        if (buffer.mid(10)[0] == 'D')
        {
            ui->complevel_comboBox()->setCurrentIndex(0);
        }
        else
        {
            for (int i = 0; i < ui->complevel_comboBox()->count(); i++)
            {
                QString content = ui->complevel_comboBox()->itemText(i).mid(0, 2);
                if (content == buffer.mid(10))
                {
                    ui->complevel_comboBox()->setCurrentIndex(i);
                }
            }
        }
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 6) == "warp1=") // warp 1
    {
        ui->episode_lineEdit()->setText(buffer.mid(6));
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 6) == "warp2=") // warp 2
    {
        ui->level_lineEdit()->setText(buffer.mid(6));
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 6) == "skill=") // skill
    {
        if (buffer.mid(6).length() > 0)
        {
            ui->difficulty_comboBox()->setCurrentIndex((buffer.mid(6).toInt()));
        }
        else
        {
            ui->difficulty_comboBox()->setCurrentIndex(0);
        }
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 5) == "box1=") // box1
    {
        if (buffer.mid(5, 4) == "true") ui->fast_checkBox()->setChecked(true);
        else ui->fast_checkBox()->setChecked(false);
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 5) == "box2=") // box2
    {
        if (buffer.mid(5, 4) == "true") ui->nomo_checkBox()->setChecked(true);
        else ui->nomo_checkBox()->setChecked(false);
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 5) == "box3=") // box3
    {
        if (buffer.mid(5, 4) == "true") ui->respawn_checkBox()->setChecked(true);
        else ui->respawn_checkBox()->setChecked(false);
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 5) == "box4=") // box4
    {
        if (buffer.mid(5, 4) == "true") ui->solonet_checkBox()->setChecked(true);
        else ui->solonet_checkBox()->setChecked(false);
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 11) == "resolution=") // resolution
    {
        ui->resolution_comboBox()->setCurrentIndex(ui->resolution_comboBox()->findText(buffer.mid(11)));
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 11) == "fullscreen=") // fullscreen
    {
        if (buffer.mid(11, 4) == "true") ui->fullscreen_checkBox()->setChecked(true);
        else ui->fullscreen_checkBox()->setChecked(false);
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 4) == "hud=") // hud
    {
        ui->hud_lineEdit()->setText(buffer.mid(4));
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 7) == "config=") // config
    {
        ui->config_lineEdit()->setText(buffer.mid(7));
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 6) == "track=") // track
    {
        if (buffer.mid(6).length() > 0)
        {
            ui->track_comboBox()->setCurrentIndex((buffer.mid(6).toInt()));
        }
        else
        {
            ui->track_comboBox()->setCurrentIndex(0);
        }
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 5) == "time=") // time
    {
        if (buffer.mid(5).length() > 0)
        {
            ui->time_comboBox()->setCurrentIndex((buffer.mid(5).toInt()));
        }
        else
        {
            ui->time_comboBox()->setCurrentIndex(0);
        }
        stream.readLineInto(&buffer);
    }
    ui->wads_listWidget()->clear();
    if (buffer.mid(0, 4) == "pwad")
    {
        while (stream.readLineInto(&buffer))
        {
            if (buffer.mid(0, 7) == "endpwad") break;

            ui->wads_listWidget()->addItem(ui->getFileName(buffer));
            ui->wads_listWidget()->item(ui->wads_listWidget()->count() - 1)->setToolTip(buffer);
        }
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 7) == "record=") // record demo
    {
        ui->record_lineEdit()->setText(buffer.mid(7));
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 9) == "playback=") // playback demo
    {
        ui->playback_lineEdit()->setText(buffer.mid(9));
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 13) == "demodropdown=") // demo drop down
    {
        if (buffer.mid(13).length() > 0)
        {
            ui->playback_comboBox()->setCurrentIndex((buffer.mid(13).toInt()));
        }
        else
        {
            ui->playback_comboBox()->setCurrentIndex(0);
        }
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 8) == "viddump=") // demo drop down
    {
        ui->viddump_lineEdit()->setText(buffer.mid(8));
        stream.readLineInto(&buffer);
    }
    if (buffer.mid(0, 11) == "additional=") // additional arguments
    {
        ui->additionalArguments_textEdit()->setText((buffer.mid(11)));
    }
}


const char* bool_cast(const bool b) {
    return b ? "true" : "false";
}
void states::saveStateToFile(QString filePath)
{
    MainWindow *ui = MainWindow::pMainWindow;

    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream out(&file);

    QString pwads;
    for(int i=0; i<ui->wads_listWidget()->count();i++)
    {
        pwads += ui->wads_listWidget()->item(i)->toolTip() + "\n";
    }
    QString level_lineEdit = "";
    if (!ui->level_lineEdit()->isHidden())
    {
        level_lineEdit = ui->level_lineEdit()->text();
    }
    QString skillbox = "";
    if (ui->difficulty_comboBox()->isEnabled() && ui->difficulty_comboBox()->currentIndex() != 0)
    {
        skillbox = ui->difficulty_comboBox()->currentText();
    }
    if (filePath.at(filePath.size() - 1) == 's')
    {
        out << "-\niwad=" + ui->iwad_comboBox()->currentText() + "\ncomplevel=" + ui->complevel_comboBox()->currentText().mid(0, 2) + "\nwarp1=" + ui->episode_lineEdit()->text() + "\nwarp2=" + level_lineEdit + "\nskill=" + skillbox + "\nbox1=" + bool_cast(ui->fast_checkBox()->isChecked()) + "\nbox2=" + bool_cast(ui->nomo_checkBox()->isChecked()) + "\nbox3=" + bool_cast(ui->respawn_checkBox()->isChecked()) + "\nbox4=" + bool_cast(ui->solonet_checkBox()->isChecked()) +
                   "\nresolution=" + ui->resolution_comboBox()->currentText() + "\nfullscreen=" + bool_cast(ui->fullscreen_checkBox()->isChecked()) + "\nhud=" + ui->hud_lineEdit()->text() + "\nconfig=" + ui->config_lineEdit()->text() + "\ntrack=" + QString::number(ui->track_comboBox()->currentIndex()) + "\ntime=" + QString::number(ui->time_comboBox()->currentIndex()) + "\npwad\n" + pwads + "endpwad\nrecord=" + ui->record_lineEdit()->text() + "\nplayback=" + ui->playback_lineEdit()->text() +
                   "\ndemodropdown=" + QString::number(ui->playback_comboBox()->currentIndex()) + "\nviddump=" + ui->viddump_lineEdit()->text() + "\nadditional=" + ui->additionalArguments_textEdit()->toPlainText();
    }
    else
    {
        out << "# Do not edit this file manually\n\niwad=" + ui->iwad_comboBox()->currentText() + "\ncomplevel=" + ui->complevel_comboBox()->currentText().mid(0, 2) + "\nwarp1=" + ui->episode_lineEdit()->text() + "\nwarp2=" + level_lineEdit + "\nskill=" + skillbox + "\nbox1=" + bool_cast(ui->fast_checkBox()->isChecked()) + "\nbox2=" + bool_cast(ui->nomo_checkBox()->isChecked()) + "\nbox3=" + bool_cast(ui->respawn_checkBox()->isChecked()) +
                   "\nbox4=" + bool_cast(ui->solonet_checkBox()->isChecked()) + "\nresolution=" + ui->resolution_comboBox()->currentText() + "\nfullscreen=" + bool_cast(ui->fullscreen_checkBox()->isChecked()) + "\nhud=" + ui->hud_lineEdit()->text() + "\nconfig=" + ui->config_lineEdit()->text() + "\ntrack=" + QString::number(ui->track_comboBox()->currentIndex()) + "\ntime=" + QString::number(ui->time_comboBox()->currentIndex()) + "\npwad\n" + pwads +
                   "endpwad\nrecord=" + ui->record_lineEdit()->text() + "\nplayback=" + ui->playback_lineEdit()->text() + "\ndemodropdown=" + QString::number(ui->playback_comboBox()->currentIndex()) + "\nviddump=" + ui->viddump_lineEdit()->text() + "\nadditional=" + ui->additionalArguments_textEdit()->toPlainText();
    }

    file.close();
}
