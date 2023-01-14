#include "historylist.h"
#include "ui_historylist.h"
#include "fstream"
#include <QStandardPaths>
#include <QSettings>
#include <mainwindow.h>
#include <QShortcut>

MainWindow * hmainWindow;

#if defined(__APPLE__) || defined(__linux__)
QString filePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/history.states";
#else
QString filePath;
#endif

historyList::historyList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::historyList)
{
    ui->setupUi(this);

    hmainWindow = MainWindow::getMainWin();

    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);

#ifdef _WIN32
    filePath = QCoreApplication::applicationDirPath()+"\\history.states";
#endif
}

historyList::~historyList()
{
    delete ui;
}

QStringList skillT =
{
    "",
    "ITYTD",
    "HNTR",
    "HMP",
    "UV",
    "Nightmare!"
};

void historyList::getHistory()
{
    ui->history_listWidget->clear();

    std::ifstream file;
    file.open(filePath.toStdString());

    if (!file.is_open())
    {
        return;
    }

    QString box1 = settings.value("toggle1t").toString();
    QString box2 = settings.value("toggle2t").toString();
    QString box3 = settings.value("toggle3t").toString();
    QString box4 = settings.value("toggle4t").toString();

    std::string buffer;
    while (buffer.substr(0,1) != "-" && !file.eof())
    {
        std::getline(file, buffer);
    }

    while (!file.eof())
    {
        std::getline(file, buffer);
        QString iwad;
        QString level;
        std::string l1="";
        std::string l2="";
        QString skill;
        QString params="";
        QString pwads="";
        QString demo="";
        if(buffer.substr(0,5)=="iwad=") // iwad
        {
            iwad = buffer.substr(5).c_str();
            std::getline(file, buffer);
        }
        std::getline(file, buffer);

        if(buffer.substr(0,6)=="warp1=") // warp 1
                {
                        l1=buffer.substr(6);
                        std::getline(file, buffer);
                }
        if(buffer.substr(0,6)=="warp2=") //warp 2
                {
                        l2=buffer.substr(6);
                        std::getline(file, buffer);
                }
        if (l2=="" && l1!="")
        {
            if (l1.size()==1)
            {
                level = ("MAP0"+l1).c_str();
            }
            else
            {
                level = ("MAP"+l1).c_str();
            }
        }
        else if (l1!="")
        {
            level = ("E"+l1+"M"+l2).c_str();
        }
        if (level!="")
        {
            level += " - ";
        }
        if(buffer.substr(0,6)=="skill=") // skill
                {
                    if (buffer.substr(6).length()>0)
                    {
                        int si = atoi(buffer.substr(6).c_str());
                        qDebug() << si;
                        if (0 < si && si <= 5)
                        {
                            skill = skillT.at(si);
                        }
                        else
                        {
                            skill = ("skill="+buffer.substr(6)).c_str();
                        }
                        if (skill!="")
                        {
                            skill += " - ";
                        }
                    }
                    std::getline(file, buffer);
                }
        if(buffer.substr(0,5)=="box1=") // box1
                {
                    if(buffer.substr(5,4)=="true")
                         params+=box1+", ";
                    std::getline(file, buffer);
                }
        if(buffer.substr(0,5)=="box2=") // box2
                {
                    if(buffer.substr(5,4)=="true")
                         params+=box2+", ";
                    std::getline(file, buffer);
                }
        if(buffer.substr(0,5)=="box3=") // box3
                {
                    if(buffer.substr(5,4)=="true")
                         params+=box3+", ";
                    std::getline(file, buffer);
                }
        if(buffer.substr(0,5)=="box4=") //box4
                {
                    if(buffer.substr(5,4)=="true")
                         params+=box4+", ";
                    std::getline(file, buffer);
                }

        while (buffer.substr(0,4)!="pwad" && !file.eof())
        {
            std::getline(file, buffer);
        }

        if(buffer.substr(0,4)=="pwad")
        {
             while (std::getline(file, buffer) && !file.eof())
             {
                if(buffer.substr(0,7)=="endpwad")
                    break;
                int lastBar = 0;
                for( size_t i=0; i<buffer.length(); i++)
                {
                    if(buffer[i]=='/' || buffer[i]=='\\')
                    {
                        lastBar=i+1;
                    }
                }
                buffer = buffer.substr(lastBar);
                pwads+=(buffer+", ").c_str();
             }
             if (pwads!="")
             {
                 pwads.resize(pwads.size()-2);
                 pwads = "\n"+pwads;
             }
             std::getline(file, buffer);
        }
        if(buffer.substr(7).length()>0) // record demo
                {
                        int lastBar = 0;
                        for( size_t i=0; i<buffer.length(); i++)
                        {
                            if(buffer[i]=='/' || buffer[i]=='\\')
                            {
                                lastBar=i+1;
                            }
                        }
                        demo = buffer.substr(lastBar).c_str();
                }
        if (demo!="")
        {
            demo="\n"+demo;
        }
        while (buffer.substr(0,1)!="-" && !file.eof())
        {
            std::getline(file, buffer);
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
    std::ifstream file;
    file.open(filePath.toStdString());
    QString text = "#lol\n\n";

    if (!file.is_open())
    {
        return;
    }

    int c = -1;
    std::string buffer;
    while (!file.eof())
    {
        std::getline(file, buffer);
        if (buffer == "-")
        {
            c++;
            std::getline(file, buffer);
        }
        if (c == ui->history_listWidget->count()-1-ui->history_listWidget->currentRow())
        {
            text += (buffer+"\n").c_str();
        }
        else if (c > ui->history_listWidget->count()-1-ui->history_listWidget->currentRow())
        {
            break;
        }
    }

    file.close();
    hmainWindow->LoadState(text, 1);
}








void historyList::on_launch_pushButton_clicked()
{
    QStringList argList;
    QString iwadName;

    std::ifstream file;
    file.open(filePath.toStdString());

    if (!file.is_open())
    {
        return;
    }

    int c = -1;
    std::string buffer;
    while (!file.eof())
    {
        std::getline(file, buffer);
        if (buffer == "-")
        {
            c++;
            std::getline(file, buffer);
        }
        if (c == ui->history_listWidget->count()-1-ui->history_listWidget->currentRow())
        {
            if(buffer.substr(0,5)=="iwad=") // iwad
            {
                iwadName = buffer.substr(5).c_str();
                std::getline(file, buffer);
            }
            if(buffer.substr(0,10)=="complevel=") // complevel
                    {
                        if(buffer.substr(10)[0]!='D')
                        {
                            argList.append("-complevel");
                            argList.append(buffer.substr(10).c_str());
                        }
                        std::getline(file, buffer);
                    }
            if(buffer.substr(0,6)=="warp1=") // warp 1
                    {
                            if (!buffer.substr(6).empty())
                            {
                                argList.append("-warp");
                                argList.append(buffer.substr(6).c_str());
                            }
                            std::getline(file, buffer);
                    }
            if(buffer.substr(0,6)=="warp2=") //warp 2
                    {
                            if (!buffer.substr(6).empty())
                            {
                                argList.append(buffer.substr(6).c_str());
                            }
                            std::getline(file, buffer);
                    }
            if(buffer.substr(0,6)=="skill=") // skill
                    {
                            if (buffer.substr(6).length()>0 && buffer.substr(6)!="0")
                            {
                                 argList.append("-skill");
                                 argList.append(buffer.substr(6).c_str());
                            }
                             std::getline(file, buffer);
                    }
            if(buffer.substr(0,5)=="box1=") // box1
                    {
                        if(buffer.substr(5)=="true")
                             argList.append(settings.value("toggle1a").toString());
                        std::getline(file, buffer);
                    }
            if(buffer.substr(0,5)=="box2=") // box2
                    {
                        if(buffer.substr(5)=="true")
                             argList.append(settings.value("toggle2a").toString());
                        std::getline(file, buffer);
                    }
            if(buffer.substr(0,5)=="box3=") // box3
                    {
                        if(buffer.substr(5)=="true")
                             argList.append(settings.value("toggle3a").toString());
                        std::getline(file, buffer);
                    }
            if(buffer.substr(0,5)=="box4=") //box4
                    {
                        if(buffer.substr(5)=="true")
                             argList.append(settings.value("toggle4a").toString());
                        std::getline(file, buffer);
                    }
            std::string fullscreen = "w";
            std::string resBox = "0";
            if(buffer.substr(0,11)=="resolution=") // resolution
                    {
                        resBox = buffer.substr(11);
                        std::getline(file, buffer);
                    }
            if(buffer.substr(0,11)=="fullscreen=") // fullscreen
                    {
                        if(buffer.substr(11)=="true")
                             fullscreen = "f";
                        std::getline(file, buffer);
                    }
            if(resBox.size() < 2)
            {
                if(fullscreen=="w")
                {
                    argList.append("-window");
                }
                else
                {
                    argList.append("-nowindow");
                }
            }
            else
            {
                argList.append("-geom");
                argList.append((resBox+fullscreen).c_str());
            }

            if(buffer.substr(0,4)=="hud=") // hud
                    {
                        if (!buffer.substr(4).empty())
                        {
                             argList.append("-hud");
                             argList.append(buffer.substr(4).c_str());
                        }
                        std::getline(file, buffer);
                    }
            if(buffer.substr(0,7)=="config=") // config
                    {
                        if (!buffer.substr(7).empty())
                        {
                             argList.append("-config");
                             argList.append(buffer.substr(7).c_str());
                        }
                        std::getline(file, buffer);
                    }
            if(buffer.substr(0,6)=="track=") // track
                    {
                        QString tmp = buffer.substr(6).c_str();
                        if (tmp=="1")
                            argList.append("-track_pacifist");
                        else if(tmp=="2")
                            argList.append("-track_100k");
                        std::getline(file, buffer);
                    }
             if(buffer.substr(0,5)=="time=") // time
                     {
                         QString tmp = buffer.substr(5).c_str();
                         if (tmp=="1")
                             argList.append("-time_use");
                         else if(tmp=="2")
                             argList.append("-time_keys");
                         else if(tmp=="3")
                             argList.append("-time_secrets");
                         else if(tmp=="4")
                             argList.append("-time_all");
                         std::getline(file, buffer);
                     }
             QStringList files;
            if(buffer.substr(0,4)=="pwad")
            {
                 while (std::getline(file, buffer))
                 {
                    if(buffer.substr(0,7)=="endpwad")
                        break;
                    files.append(buffer.c_str());
                 }
                 std::getline(file, buffer);
            }
            if (files.size()>0)
            {
                argList.append("-file");
                argList.append(files);
            }
            if(buffer.substr(0,7)=="record=") // record demo
                    {
                            if (!buffer.substr(7).empty())
                            {
                                 argList.append("-record");
                                 argList.append(buffer.substr(7).c_str());
                            }
                            std::getline(file, buffer);
                    }
            QString demo="";
            if(buffer.substr(0,9)=="playback=") // playback demo
                    {
                            if (!buffer.substr(9).empty())
                            {
                                 demo = buffer.substr(9).c_str();
                            }
                            std::getline(file, buffer);
                    }
            if(buffer.substr(0,13)=="demodropdown=") // demo drop down
                    {
                        if (buffer.substr(13)=="1")
                        {
                             argList.append("-playdemo");
                             argList.append(demo);
                        }
                        else if (buffer.substr(13)=="2")
                        {
                             argList.append("-timedemo");
                             argList.append(demo);
                        }
                        else if (buffer.substr(13)=="3")
                        {
                             argList.append("-fastdemo");
                             argList.append(demo);
                        }
                        std::getline(file, buffer);
                    }
            if(buffer.substr(0,8)=="viddump=") // record demo
                    {
                            if (!buffer.substr(8).empty())
                            {
                                 argList.append("-viddump");
                                 argList.append(buffer.substr(8).c_str());
                            }
                            std::getline(file, buffer);
                    }
            if(buffer.substr(0,11)=="additional=") // additional arguments
                    {
                        if (buffer.substr(11) != "")
                        {
                            std::string str = buffer.substr(11)+" ";

                            std::string strToAdd="";
                            for( size_t i=0; i<str.length(); i++){

                                char c = str[i];
                                if( c == ' '){
                                    if (strToAdd != "")
                                    {
                                        argList.append(strToAdd.c_str());
                                        strToAdd="";
                                    }
                                }else if(c == '\"' ){
                                    i++;
                                    while( str[i] != '\"' ){ strToAdd.push_back(str[i]); i++; }
                                }else{
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

    hmainWindow->Launch(iwadName, argList);
}

