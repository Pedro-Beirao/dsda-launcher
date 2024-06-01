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

    QString header;
    stream.readLineInto(&header);

    if (header == "dsdalauncherstatev1.4") loadStateNew(stream);
    else loadStateOld(stream);

    file.close();
}

void states::loadStateFromString(QString string)
{
    QTextStream stream(&string);
    loadStateOld(stream);
}

void states::loadStateOld(QTextStream &stream)
{
    MainWindow::pMainWindow->wads_listWidget()->clear();

    while (!stream.atEnd())
    {
        QString buffer;
        stream.readLineInto(&buffer);

        QString buffer_name;
        QString buffer_value;

        int pos = buffer.indexOf('=');
        buffer_name = buffer.mid(0, pos).trimmed();
        buffer_value = buffer.mid(pos + 1).trimmed();

        if (buffer_name == "iwad") // iwad
        {
            for (int i = 0; i < MainWindow::pMainWindow->iwad_comboBox()->count(); i++)
            {
                if (MainWindow::pMainWindow->iwad_comboBox()->itemText(i) == buffer_value)
                {
                    MainWindow::pMainWindow->iwad_comboBox()->setCurrentIndex(i);
                }
            }
        }
        if (buffer_name == "complevel") // complevel
        {
            if (buffer_value == "Default")
            {
                MainWindow::pMainWindow->complevel_comboBox()->setCurrentIndex(0);
            }
            else
            {
                for (int i = 0; i < MainWindow::pMainWindow->complevel_comboBox()->count(); i++)
                {
                    QString content = MainWindow::pMainWindow->complevel_comboBox()->itemText(i).mid(0, 2);
                    if (content == buffer_value)
                    {
                        MainWindow::pMainWindow->complevel_comboBox()->setCurrentIndex(i);
                    }
                }
            }
        }
        if (buffer_name == "warp1") // warp 1
        {
            MainWindow::pMainWindow->episode_lineEdit()->setText(buffer_value);
        }
        if (buffer_name == "warp2") // warp 2
        {
            MainWindow::pMainWindow->level_lineEdit()->setText(buffer_value);
        }
        if (buffer_name == "skill") // skill
        {
            if (buffer_value.length() > 0)
            {
                MainWindow::pMainWindow->difficulty_comboBox()->setCurrentIndex((buffer_value.toInt()));
            }
            else
            {
                MainWindow::pMainWindow->difficulty_comboBox()->setCurrentIndex(0);
            }
        }
        if (buffer_name == "box1") // box1
        {
            if (buffer_value == "true") MainWindow::pMainWindow->toggle1_checkBox()->setChecked(true);
            else MainWindow::pMainWindow->toggle1_checkBox()->setChecked(false);
        }
        if (buffer_name == "box2") // box2
        {
            if (buffer_value == "true") MainWindow::pMainWindow->toggle2_checkBox()->setChecked(true);
            else MainWindow::pMainWindow->toggle2_checkBox()->setChecked(false);
        }
        if (buffer_name == "box3") // box3
        {
            if (buffer_value == "true") MainWindow::pMainWindow->toggle3_checkBox()->setChecked(true);
            else MainWindow::pMainWindow->toggle3_checkBox()->setChecked(false);
        }
        if (buffer_name == "box4") // box4
        {
            if (buffer_value == "true") MainWindow::pMainWindow->toggle4_checkBox()->setChecked(true);
            else MainWindow::pMainWindow->toggle4_checkBox()->setChecked(false);
        }
        if (buffer_name == "resolution") // resolution
        {
            MainWindow::pMainWindow->resolution_comboBox()->setCurrentIndex(MainWindow::pMainWindow->resolution_comboBox()->findText(buffer_value));
        }
        if (buffer_name == "fullscreen") // fullscreen
        {
            if (buffer_value == "true") MainWindow::pMainWindow->fullscreen_checkBox()->setChecked(true);
            else MainWindow::pMainWindow->fullscreen_checkBox()->setChecked(false);
        }
        if (buffer_name == "hud") // hud
        {
            MainWindow::pMainWindow->hud_lineEdit()->setText(buffer_value);
        }
        if (buffer_name == "config") // config
        {
            MainWindow::pMainWindow->config_lineEdit()->setText(buffer_value);
        }
        if (buffer_name == "track") // track
        {
            if (buffer_value.length() > 0)
            {
                MainWindow::pMainWindow->track_comboBox()->setCurrentIndex(buffer_value.toInt());
            }
            else
            {
                MainWindow::pMainWindow->track_comboBox()->setCurrentIndex(0);
            }
        }
        if (buffer_name == "time") // time
        {
            if (buffer_value.length() > 0)
            {
                MainWindow::pMainWindow->time_comboBox()->setCurrentIndex(buffer_value.toInt());
            }
            else
            {
                MainWindow::pMainWindow->time_comboBox()->setCurrentIndex(0);
            }
        }
        if (buffer_name == "pwad")
        {
            while (stream.readLineInto(&buffer))
            {
                if (buffer.mid(0, 7) == "endpwad") break;

                MainWindow::pMainWindow->wads_listWidget()->addItem(getFileName(buffer));
                MainWindow::pMainWindow->wads_listWidget()->item(MainWindow::pMainWindow->wads_listWidget()->count() - 1)->setToolTip(buffer);
            }
        }
        if (buffer_name == "record") // record demo
        {
            MainWindow::pMainWindow->record_lineEdit()->setText(buffer_value);
        }
        if (buffer_name == "playback") // playback demo
        {
            MainWindow::pMainWindow->playback_lineEdit()->setText(buffer_value);
        }
        if (buffer_name == "demodropdown") // demo drop down
        {
            if (buffer_value.length() > 0)
            {
                MainWindow::pMainWindow->playback_comboBox()->setCurrentIndex(buffer_value.toInt());
            }
            else
            {
                MainWindow::pMainWindow->playback_comboBox()->setCurrentIndex(0);
            }
        }
        if (buffer_name == "viddump") // demo drop down
        {
            MainWindow::pMainWindow->viddump_lineEdit()->setText(buffer_value);
        }
        if (buffer_name == "additional") // additional arguments
        {
            MainWindow::pMainWindow->additionalArguments_textEdit()->setText(buffer_value);
        }
    }
}

void states::loadStateNew(QTextStream &stream)
{
    MainWindow::pMainWindow->wads_listWidget()->clear();

    while (!stream.atEnd())
    {
        QString buffer;
        stream.readLineInto(&buffer);
        buffer = buffer.trimmed();

        QString buffer_name;
        QString buffer_value;

        int pos = buffer.indexOf(' ');
        buffer_name = buffer.mid(0, pos).trimmed();
        buffer_value = buffer.mid(pos + 1).trimmed();

        if (buffer_name == "iwad") // iwad
        {
            MainWindow::pMainWindow->iwad_comboBox()->setCurrentIndex(MainWindow::pMainWindow->iwad_comboBox()->findText(buffer_value));
        }
        else if (buffer_name == "complevel") // complevel
        {
            if (buffer_value.isEmpty()) continue;

            int index = MainWindow::pMainWindow->complevel_comboBox()->findText(buffer_value);
            if (index != -1)
            {
                MainWindow::pMainWindow->complevel_comboBox()->setCurrentIndex(index);
            }
            else
            {
                MainWindow::pMainWindow->complevel_comboBox()->addItem(buffer_value);
                MainWindow::pMainWindow->complevel_comboBox()->setCurrentIndex(MainWindow::pMainWindow->complevel_comboBox()->count() - 1);
            }
        }
        else if (buffer_name == "warp1") // warp 1
        {
            MainWindow::pMainWindow->episode_lineEdit()->setText(buffer_value);
        }
        else if (buffer_name == "warp2") // warp 2
        {
            MainWindow::pMainWindow->level_lineEdit()->setText(buffer_value);
        }
        else if (buffer_name == "skill") // skill
        {
            MainWindow::pMainWindow->difficulty_comboBox()->setCurrentIndex(buffer_value.toInt());
        }
        else if (buffer_name == "box1") // box1
        {
            MainWindow::pMainWindow->toggle1_checkBox()->setChecked(string_to_bool(buffer_value));
        }
        else if (buffer_name == "box2") // box2
        {
            MainWindow::pMainWindow->toggle2_checkBox()->setChecked(string_to_bool(buffer_value));
        }
        else if (buffer_name == "box3") // box3
        {
            MainWindow::pMainWindow->toggle3_checkBox()->setChecked(string_to_bool(buffer_value));
        }
        else if (buffer_name == "box4") // box4
        {
            MainWindow::pMainWindow->toggle4_checkBox()->setChecked(string_to_bool(buffer_value));
        }
        else if (buffer_name == "resolution") // resolution
        {
            MainWindow::pMainWindow->resolution_comboBox()->setCurrentIndex(MainWindow::pMainWindow->resolution_comboBox()->findText(buffer_value));
        }
        else if (buffer_name == "fullscreen") // fullscreen
        {
            MainWindow::pMainWindow->fullscreen_checkBox()->setChecked(string_to_bool(buffer_value));
        }
        else if (buffer_name == "hud") // hud
        {
            MainWindow::pMainWindow->hud_lineEdit()->setText(buffer_value);
        }
        else if (buffer_name == "config") // config
        {
            MainWindow::pMainWindow->config_lineEdit()->setText(buffer_value);
        }
        else if (buffer_name == "track") // track
        {
            MainWindow::pMainWindow->track_comboBox()->setCurrentIndex(buffer_value.toInt());
        }
        else if (buffer_name == "time") // time
        {
            MainWindow::pMainWindow->time_comboBox()->setCurrentIndex(buffer_value.toInt());
        }
        else if (buffer_name == "pwad") // pwad
        {
            MainWindow::pMainWindow->wads_listWidget()->addItem(getFileName(buffer_value));
            MainWindow::pMainWindow->wads_listWidget()->item(MainWindow::pMainWindow->wads_listWidget()->count() - 1)->setToolTip(buffer_value);
        }
        else if (buffer_name == "record") // record demo
        {
            MainWindow::pMainWindow->record_lineEdit()->setText(buffer_value);
        }
        else if (buffer_name == "playback") // playback demo
        {
            MainWindow::pMainWindow->playback_lineEdit()->setText(buffer_value);
        }
        else if (buffer_name == "demodropdown") // demo drop down
        {
            MainWindow::pMainWindow->playback_comboBox()->setCurrentIndex(buffer_value.toInt());
        }
        else if (buffer_name == "viddump") // demo drop down
        {
            MainWindow::pMainWindow->viddump_lineEdit()->setText(buffer_value);
        }
        else if (buffer_name == "additional") // additional arguments
        {
            MainWindow::pMainWindow->additionalArguments_textEdit()->setText(buffer_value);
        }
        else if (buffer_name == "-")
        {
            return;
        }
    }
}

void states::saveStateToFile(QString filePath)
{
    MainWindow *ui = MainWindow::pMainWindow;

    QFile file(filePath);
    QTextStream out(&file);
    if (getExtension(filePath) == "states_tmp")
    {
        if (!file.open(QFile::ReadWrite | QFile::Text | QIODevice::Append)) return;
        out << "-\n";
    }
    else
    {
        if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Truncate)) return;
        out << STATE_HEADER + "\n\n";
    }

    out << "iwad " + ui->iwad_comboBox()->currentText() + "\n";
    out << "complevel " + ui->complevel_comboBox()->currentText() + "\n";
    out << "warp1 " + ui->episode_lineEdit()->text() + "\n";
    out << "warp2 " + ui->level_lineEdit()->text() + "\n";
    out << "skill " + QString::number(ui->difficulty_comboBox()->currentIndex()) + "\n";
    out << "box1 " + bool_to_string(ui->toggle1_checkBox()->isChecked()) + "\n";
    out << "box2 " + bool_to_string(ui->toggle2_checkBox()->isChecked()) + "\n";
    out << "box3 " + bool_to_string(ui->toggle3_checkBox()->isChecked()) + "\n";
    out << "box4 " + bool_to_string(ui->toggle4_checkBox()->isChecked()) + "\n";
    out << "resolution " + ui->resolution_comboBox()->currentText() + "\n";
    out << "fullscreen " + bool_to_string(ui->fullscreen_checkBox()->isChecked()) + "\n";
    out << "hud " + ui->hud_lineEdit()->text() + "\n";
    out << "config " + ui->config_lineEdit()->text() + "\n";
    out << "track " + QString::number(ui->track_comboBox()->currentIndex()) + "\n";
    out << "time " + QString::number(ui->time_comboBox()->currentIndex()) + "\n";
    for (int i = 0; i < ui->wads_listWidget()->count(); i++)
    {
        out << "pwad " + ui->wads_listWidget()->item(i)->toolTip() + "\n";
    }
    out << "record " + ui->record_lineEdit()->text() + "\n";
    out << "playback " + ui->playback_lineEdit()->text() + "\n";
    out << "demodropdown " + QString::number(ui->playback_comboBox()->currentIndex()) + "\n";
    out << "viddump " + ui->viddump_lineEdit()->text() + "\n";
    out << "additional " + ui->additionalArguments_textEdit()->toPlainText() + "\n";
    out << "timestamp " + QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") + "\n";

    file.close();
}
