#include "historylist.h"
#include "ui_historylist.h"
#include "states.h"
#include "mainwindow.h"

historyList::historyList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::historyList)
{
    ui->setupUi(this);

    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);

    init_historyPath();
}

historyList::~historyList() { delete ui; }

void historyList::init_historyPath()
{
#ifdef Q_OS_WIN
    historyPath = QCoreApplication::applicationDirPath() + "\\history.states";
#else
    historyPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.dsda-doom/history.states";
#endif
}

void historyList::getHistory()
{
    ui->history_listWidget->clear();

    QFile file(historyPath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QString box1 = settings->value("toggle1t").toString();
    QString box2 = settings->value("toggle2t").toString();
    QString box3 = settings->value("toggle3t").toString();
    QString box4 = settings->value("toggle4t").toString();

    QTextStream stream(&file);
    QString buffer;
    while (buffer != "-" && !stream.atEnd())
    {
        stream.readLineInto(&buffer);
    }

    while (!stream.atEnd())
    {
        stream.readLineInto(&buffer);
        QString iwad;
        QString level;
        QString warp_1 = "";
        QString warp_2 = "";
        QString skill;
        QString params="";
        QString pwads="";
        QString demo = "";

        while (buffer != "-" && !stream.atEnd())
        {
            QString buffer_name = buffer;
            QString buffer_value = "";

            int pos = buffer.indexOf('=');
            if (pos != -1)
            {
                buffer_name = buffer.mid(0, pos);
                buffer_value = buffer.mid(pos + 1);
            }

            if (buffer_name == "iwad") // iwad
            {
                iwad = buffer_value;
            }
            if (buffer_name == "warp1") // warp 1
            {
                warp_1 = buffer_value;
            }
            if (buffer_name == "warp2") // warp 2
            {
                warp_2 = buffer_value;
            }
            if (warp_2 == "" && warp_1 != "")
            {
                if (warp_1.size() == 1)
                {
                    level = "MAP0" + warp_1;
                }
                else
                {
                    level = "MAP" + warp_1;
                }
            }
            if (warp_2 != "")
            {
                level = "E" + warp_1 + "M" + warp_2;
            }
            if (level != "")
            {
                level += " - ";
            }

            if (buffer.mid(0, 6) == "skill=") // skill
            {
                if (buffer.mid(6).length() > 0)
                {
                    int si = (buffer.mid(6)).toInt();
                    if (0 < si && si <= 5)
                    {
                        skill = SKILLS_LIST.at(si);
                    }
                    else
                    {
                        skill = "skill=" + buffer.mid(6);
                    }
                    if (skill != "")
                    {
                        skill += " - ";
                    }
                }
            }
            if (buffer.mid(0, 5) == "box1=") // box1
            {
                if (buffer.mid(5, 4) == "true") params += box1 + ", ";
            }
            if (buffer.mid(0, 5) == "box2=") // box2
            {
                if (buffer.mid(5, 4) == "true") params += box2 + ", ";
            }
            if (buffer.mid(0, 5) == "box3=") // box3
            {
                if (buffer.mid(5, 4) == "true") params += box3 + ", ";
            }
            if (buffer.mid(0, 5) == "box4=") // box4
            {
                if (buffer.mid(5, 4) == "true") params += box4 + ", ";
            }

            if (buffer.mid(0, 4) == "pwad")
            {
                while (stream.readLineInto(&buffer) && !stream.atEnd())
                {
                    if (buffer.mid(0, 7) == "endpwad") break;
                    int lastBar = 0;
                    for (qsizetype i = 0; i < buffer.length(); i++)
                    {
                        if (buffer[i] == '/' || buffer[i] == '\\')
                        {
                            lastBar = i + 1;
                        }
                    }
                    buffer = buffer.mid(lastBar);
                    pwads += buffer + ", ";
                }
                if (pwads != "")
                {
                    pwads.resize(pwads.size() - 2);
                    pwads = "\n" + pwads;
                }
            }
            if (buffer_name == "record") // record demo
            {
                int lastBar = 0;
                for (qsizetype i = 0; i < buffer_value.length(); i++)
                {
                    if (buffer_value[i] == '/' || buffer_value[i] == '\\')
                    {
                        lastBar = i + 1;
                    }
                }
                demo = "\n" + buffer_value.mid(lastBar);
            }

            stream.readLineInto(&buffer);
        }

        QString slp = skill + level + params;
        if (!slp.isEmpty())
        {
            slp.resize(slp.size()-2);
            ui->history_listWidget->insertItem(0,iwad+"\n"+slp+pwads+demo);
        }
        else
        {
            ui->history_listWidget->insertItem(0,iwad+pwads+demo);
        }
    }

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
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    int c = -1;
    QString text = "#lol\n\n";

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
            text += buffer + "\n";
        }
        else if (c > ui->history_listWidget->count()-1-ui->history_listWidget->currentRow())
        {
            break;
        }
    }

    file.close();
    states::loadStateFromString(text);
}

void historyList::on_launch_pushButton_clicked()
{
    QStringList argList;
    QString iwadName;

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
                iwadName = buffer.mid(5);
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

    MainWindow::pMainWindow->Launch(iwadName, argList);
}
