#include "historylist.h"
#include "ui_historylist.h"
#include "fstream"
#include <QStandardPaths>
#include <QSettings>
#include <mainwindow.h>

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
    ui->listWidget->clear();

    std::ifstream file;
    file.open(filePath.toStdString());

    if (!file.is_open())
    {
        return;
    }

    std::string buffer;
    std::getline(file, buffer);
    std::getline(file, buffer);
    std::getline(file, buffer);

    QString box1 = settings.value("toggle1t").toString();
    QString box2 = settings.value("toggle2t").toString();
    QString box3 = settings.value("toggle3t").toString();
    QString box4 = settings.value("toggle4t").toString();

    int count = std::stoi(buffer.substr(6));
    std::getline(file, buffer);
    std::getline(file, buffer);

    for (int c = 0; c < count; c++)
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
        if(buffer.substr(4).length()>1) // iwad
        {
            iwad = buffer.substr(5).c_str();
        }
        std::getline(file, buffer);
        std::getline(file, buffer);

        if(buffer.substr(5).length()>0) // warp 1
                {
                        l1=buffer.substr(6);
                }
        std::getline(file, buffer);
        if(buffer.substr(5).length()>0) //warp 2
                {
                        l2=buffer.substr(6);
                }
        if (l2=="" && l1!="")
        {
            if (l1.size()==1)
            {
                level = ("MAP0"+l1+" - ").c_str();
            }
            else
            {
                level = ("MAP0"+l1+" - ").c_str();
            }
        }
        else if (l1!="")
        {
            level = ("E"+l1+"M"+l2+" - ").c_str();
        }
        std::getline(file, buffer);
        if(buffer.substr(5).length()>1) // skill
                {
                    if (0 < stoi(buffer.substr(6)) && stoi(buffer.substr(6)) <= 5)
                    {
                        skill = skillT.at(stoi(buffer.substr(6)))+" - ";
                    }
                    else if (0 < stoi(buffer.substr(6)))
                    {
                        skill = ("skill="+buffer.substr(6)+" - ").c_str();
                    }
                }
        std::getline(file, buffer);
        if(buffer.substr(4).length()>1) // box1
                {
                    if(buffer.substr(5,4)=="true")
                         params+=box1+", ";
                }
        std::getline(file, buffer);
        if(buffer.substr(4).length()>1) // box2
                {
                    if(buffer.substr(5,4)=="true")
                         params+=box2+", ";
                }
        std::getline(file, buffer);
        if(buffer.substr(4).length()>1) // box3
                {
                    if(buffer.substr(5,4)=="true")
                         params+=box3+", ";
                }
        std::getline(file, buffer);
        if(buffer.substr(4).length()>1) //box4
                {
                    if(buffer.substr(5,4)=="true")
                         params+=box4+", ";
                }
        if (params!="")
        {
            params.resize(params.size()-2);
        }
        if (skill!=""&&level==""&&params=="")
        {
            skill.resize(skill.size()-3);
        }
        if (level!=""&&params=="")
        {
            level.resize(level.size()-3);
        }

        std::getline(file, buffer);
        std::getline(file, buffer);
        std::getline(file, buffer);
        std::getline(file, buffer);
        std::getline(file, buffer);
        std::getline(file, buffer);
        std::getline(file, buffer);
        if(buffer.substr(0,4)=="pwad")
        {
             while (std::getline(file, buffer))
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
        }
        std::getline(file, buffer);
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
        std::getline(file, buffer);
        std::getline(file, buffer);
        std::getline(file, buffer);
        std::getline(file, buffer);
        QListWidgetItem item;
        ui->listWidget->addItem(iwad+"\n"+skill+level+params+pwads+demo);
    }

    file.close();
}

void historyList::on_pushButton_2_clicked()
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
        getline(file, buffer);
        if (buffer == "-")
        {
            c++;
            getline(file, buffer);
        }
        if (c == ui->listWidget->currentRow())
        {
            text += (buffer+"\n").c_str();
        }
        else if (c > ui->listWidget->currentRow())
        {
            break;
        }
    }

    file.close();
    qDebug() << text;
    hmainWindow->LoadState(text, 1);
}







