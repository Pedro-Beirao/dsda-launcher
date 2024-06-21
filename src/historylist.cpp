#include "historylist.h"
#include "mainwindow.h"
#include "states.h"
#include "ui_historylist.h"

historyList::historyList(QWidget *parent) : QWidget(parent), ui(new Ui::historyList)
{
    ui->setupUi(this);

    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);

    init_historyPath();
}

historyList::~historyList() { delete ui; }

void historyList::init_historyPath()
{
#if defined Q_OS_WIN
    historyPath = QCoreApplication::applicationDirPath() + "\\history.states";
#else
    historyPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.dsda-doom/history.states";
#endif
}

void historyList::getHistory()
{
    ui->history_listWidget->clear();

    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;

    QTextStream stream(&file);
    QString buffer;

    stream.readLineInto(&buffer);
    if (buffer != HISTORY_HEADER)
    {
        file.close();
        return;
    }

    while (buffer != "-" && !stream.atEnd())
    {
        stream.readLineInto(&buffer);
    }

    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);
        QString iwad;
        QString warp_1;
        QString warp_2;
        QString pwads;
        QString recordDemo;
        QString playbackDemo;
        QString playbackDemoType;
        while (buffer != "-" && !stream.atEnd())
        {
            buffer = buffer.trimmed();

            QString buffer_name;
            QString buffer_value;

            int pos = buffer.indexOf(' ');
            if (pos != -1)
            {
                buffer_name = buffer.mid(0, pos).trimmed();
                buffer_value = buffer.mid(pos + 1).trimmed();
            }

            if (buffer_name == "iwad") iwad = buffer_value;
            else if (buffer_name == "warp1") warp_1 = buffer_value;
            else if (buffer_name == "warp2") warp_2 = buffer_value;
            else if (buffer_name == "pwad") pwads += getFileName(buffer_value) + " ";
            else if (buffer_name == "record") recordDemo = buffer_value;
            else if (buffer_name == "playback") playbackDemo = buffer_value;
            else if (buffer_name == "demodropdown")
            {
                if (buffer_value == '0') playbackDemoType = "Playdemo ";
                else if (buffer_value == '1') playbackDemoType = "Timedemo ";
                else if (buffer_value == '2') playbackDemoType = "Fastdemo ";
            }

            stream.readLineInto(&buffer);
        }

        QString title = iwad;

        QString level = createLevelString(warp_1, warp_2);

        if (!level.isEmpty()) title += " - " + level;
        if (!pwads.isEmpty()) title += "\n" + pwads;
        if (!recordDemo.isEmpty()) title += "\nRecord " + getFileName(recordDemo);
        if (!playbackDemo.isEmpty()) title += "\n" + playbackDemoType + getFileName(playbackDemo);

        ui->history_listWidget->insertItem(0, title);
    }

    file.close();

    ui->history_listWidget->setCurrentRow(0);
}

void historyList::on_history_listWidget_currentRowChanged(int currentRow)
{
    ui->iwad_label->clear();
    ui->complevel_label->clear();
    ui->difficulty_label->clear();
    ui->level_label->clear();
    ui->pwads_label->clear();
    ui->demo_label->clear();
    ui->extra_label->clear();
    ui->timestamp_label->clear();

    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;

    QTextStream stream(&file);
    QString buffer;
    while (buffer != "-" && !stream.atEnd())
    {
        stream.readLineInto(&buffer);
    }

    int count = 0;
    QString warp1, warp2, recordDemo_s, playbackDemo_s, playbackDemo_t;

    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);

        if (buffer == "-") count++;
        if (count != ui->history_listWidget->count() - 1 - currentRow) continue;

        buffer = buffer.trimmed();

        QString buffer_name, buffer_value;

        int pos = buffer.indexOf(' ');
        if (pos != -1)
        {
            buffer_name = buffer.mid(0, pos).trimmed();
            buffer_value = buffer.mid(pos + 1).trimmed();
        }

        if (buffer_name == "iwad") ui->iwad_label->setText(buffer_value);
        else if (buffer_name == "complevel") ui->complevel_label->setText(buffer_value);
        else if (buffer_name == "warp1") warp1 = buffer_value;
        else if (buffer_name == "warp2") warp2 = buffer_value;
        else if (buffer_name == "skill") ui->difficulty_label->setText("Skill " + buffer_value);
        else if (buffer_name == "pwad") ui->pwads_label->setText(ui->pwads_label->text() + getFileName(buffer_value) + "\n");
        else if (buffer_name == "record") recordDemo_s = "Record\n" + getFileName(buffer_value) + "\n";
        else if (buffer_name == "playback") playbackDemo_s = getFileName(buffer_value) + "\n";
        else if (buffer_name == "demodropdown")
        {
            if (buffer_value == '0') playbackDemo_t = "Playdemo\n";
            else if (buffer_value == '1') playbackDemo_t = "Timedemo\n";
            else if (buffer_value == '2') playbackDemo_t = "Fastdemo\n";
        }
        else if (buffer_name == "box1" && buffer_value == "true") ui->extra_label->setText(ui->extra_label->text() + " " + MainWindow::pMainWindow->toggle1_checkBox()->toolTip());
        else if (buffer_name == "box2" && buffer_value == "true") ui->extra_label->setText(ui->extra_label->text() + " " + MainWindow::pMainWindow->toggle2_checkBox()->toolTip());
        else if (buffer_name == "box3" && buffer_value == "true") ui->extra_label->setText(ui->extra_label->text() + " " + MainWindow::pMainWindow->toggle3_checkBox()->toolTip());
        else if (buffer_name == "box4" && buffer_value == "true") ui->extra_label->setText(ui->extra_label->text() + " " + MainWindow::pMainWindow->toggle4_checkBox()->toolTip());
        else if (buffer_name == "additional") ui->extra_label->setText(ui->extra_label->text() + " " + buffer_value);
        else if (buffer_name == "timestamp") ui->timestamp_label->setText(buffer_value);
    }

    ui->level_label->setText(createLevelString(warp1, warp2));
    if (ui->level_label->text().isEmpty()) ui->difficulty_label->clear();

    if (!recordDemo_s.isEmpty()) ui->demo_label->setText(recordDemo_s);
    else if (!playbackDemo_s.isEmpty()) ui->demo_label->setText(playbackDemo_t + playbackDemo_s);

    file.close();
}

void historyList::fooo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

void historyList::on_load_pushButton_clicked()
{
    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;

    int c = -1;

    QTextStream stream(&file);
    QString buffer;
    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);
        if (buffer == "-")
        {
            c++;
        }
        if (c == ui->history_listWidget->count()-1-ui->history_listWidget->currentRow())
        {
            states::loadStateNew(stream);
            break;
        }
    }

    file.close();
}

void historyList::on_launch_pushButton_clicked()
{
    QStringList argList;

    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    int c = -1;
    QTextStream stream(&file);
    QString buffer;
    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);
        if (buffer == "-")
        {
            c++;
            stream.readLineInto(&buffer);
        }
        if (c == ui->history_listWidget->count()-1-ui->history_listWidget->currentRow())
        {
            if (buffer.mid(0, 5) == "iwad=") // iwad
            {
                argList.append("-complevel");
                argList.append(buffer.mid(5));
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 10) == "complevel=") // complevel
            {
                if (buffer.mid(10)[0] != 'D')
                {
                    argList.append("-complevel");
                    argList.append(buffer.mid(10));
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 6) == "warp1=") // warp 1
            {
                if (!buffer.mid(6).isEmpty())
                {
                    argList.append("-warp");
                    argList.append(buffer.mid(6));
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 6) == "warp2=") // warp 2
            {
                if (!buffer.mid(6).isEmpty())
                {
                    argList.append(buffer.mid(6));
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 6) == "skill=") // skill
            {
                if (buffer.mid(6).length() > 0 && buffer.mid(6) != "0")
                {
                    argList.append("-skill");
                    argList.append(buffer.mid(6));
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 5) == "box1=") // box1
            {
                if (buffer.mid(5) == "true") argList.append(settings->value("toggle1a").toString());
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 5) == "box2=") // box2
            {
                if (buffer.mid(5) == "true") argList.append(settings->value("toggle2a").toString());
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 5) == "box3=") // box3
            {
                if (buffer.mid(5) == "true") argList.append(settings->value("toggle3a").toString());
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 5) == "box4=") // box4
            {
                if (buffer.mid(5) == "true") argList.append(settings->value("toggle4a").toString());
                stream.readLineInto(&buffer);
            }
            QString fullscreen = "w";
            QString resBox = "0";
            if (buffer.mid(0, 11) == "resolution=") // resolution
            {
                resBox = buffer.mid(11);
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 11) == "fullscreen=") // fullscreen
            {
                if (buffer.mid(11) == "true") fullscreen = "f";
                stream.readLineInto(&buffer);
            }
            if(resBox.size() < 2)
            {
                if(fullscreen=="w")
                {
                    argList.append("-window");
                }
                else
                {
                    argList.append("-fullscreen");
                }
            }
            else
            {
                argList.append("-geom");
                argList.append((resBox + fullscreen));
            }

            if (buffer.mid(0, 4) == "hud=") // hud
            {
                if (!buffer.mid(4).isEmpty())
                {
                    argList.append("-hud");
                    argList.append(buffer.mid(4));
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 7) == "config=") // config
            {
                if (!buffer.mid(7).isEmpty())
                {
                    argList.append("-config");
                    argList.append(buffer.mid(7));
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 6) == "track=") // track
            {
                QString tmp = buffer.mid(6);
                if (tmp == "1") argList.append("-track_pacifist");
                else if (tmp == "2") argList.append("-track_100k");
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 5) == "time=") // time
            {
                QString tmp = buffer.mid(5);
                if (tmp == "1") argList.append("-time_use");
                else if (tmp == "2") argList.append("-time_keys");
                else if (tmp == "3") argList.append("-time_secrets");
                else if (tmp == "4") argList.append("-time_all");
                stream.readLineInto(&buffer);
            }
             QStringList files;
             if (buffer.mid(0, 4) == "pwad")
             {
                 while (stream.readLineInto(&buffer))
                 {
                     if (buffer.mid(0, 7) == "endpwad") break;
                     files.append(buffer);
                 }
                 stream.readLineInto(&buffer);
             }
            if (files.size()>0)
            {
                argList.append("-file");
                argList.append(files);
            }
            if (buffer.mid(0, 7) == "record=") // record demo
            {
                if (!buffer.mid(7).isEmpty())
                {
                    argList.append("-record");
                    argList.append(buffer.mid(7));
                }
                stream.readLineInto(&buffer);
            }
            QString demo="";
            if (buffer.mid(0, 9) == "playback=") // playback demo
            {
                if (!buffer.mid(9).isEmpty())
                {
                    demo = buffer.mid(9);
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 13) == "demodropdown=") // demo drop down
            {
                if (buffer.mid(13) == "1")
                {
                    argList.append("-playdemo");
                    argList.append(demo);
                }
                else if (buffer.mid(13) == "2")
                {
                    argList.append("-timedemo");
                    argList.append(demo);
                }
                else if (buffer.mid(13) == "3")
                {
                    argList.append("-fastdemo");
                    argList.append(demo);
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 8) == "viddump=") // record demo
            {
                if (!buffer.mid(8).isEmpty())
                {
                    argList.append("-viddump");
                    argList.append(buffer.mid(8));
                }
                stream.readLineInto(&buffer);
            }
            if (buffer.mid(0, 11) == "additional=") // additional arguments
            {
                if (buffer.mid(11) != "")
                {
                    QString str = buffer.mid(11) + " ";

                    QString strToAdd = "";
                    for (qsizetype i = 0; i < str.length(); i++)
                    {

                        QChar c = str[i];
                        if (c == ' ')
                        {
                            if (strToAdd != "")
                            {
                                argList.append(strToAdd);
                                strToAdd = "";
                            }
                        }
                        else if (c == '\"')
                        {
                            i++;
                            while (str[i] != '\"')
                            {
                                strToAdd.push_back(str[i]);
                                i++;
                            }
                        }
                        else
                        {
                            strToAdd.push_back(c);
                        }
                    }
                }
            }

            break;
        }
        else if (c > ui->history_listWidget->count()-1-ui->history_listWidget->currentRow())
        {
            break;
        }
    }

    file.close();

    MainWindow::pMainWindow->Launch(argList);
}
