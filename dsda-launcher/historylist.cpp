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
    ui->listWidget->clear();

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
                level = ("MAP0"+l1+" - ").c_str();
            }
            else
            {
                level = ("MAP"+l1+" - ").c_str();
            }
        }
        else if (l1!="")
        {
            level = ("E"+l1+"M"+l2+" - ").c_str();
        }
        if(buffer.substr(0,6)=="skill=") // skill
                {
                    if (0 < stoi(buffer.substr(6)) && stoi(buffer.substr(6)) <= 5)
                    {
                        skill = skillT.at(stoi(buffer.substr(6)))+" - ";
                    }
                    else if (0 < stoi(buffer.substr(6)))
                    {
                        skill = ("skill="+buffer.substr(6)+" - ").c_str();
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
        if (params.size()>2)
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
        QListWidgetItem item;
        ui->listWidget->insertItem(0,iwad+"\n"+skill+level+params+pwads+demo);
    }

    file.close();
}

void historyList::fooo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
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
        std::getline(file, buffer);
        if (buffer == "-")
        {
            c++;
            std::getline(file, buffer);
        }
        if (c == ui->listWidget->count()-1-ui->listWidget->currentRow())
        {
            text += (buffer+"\n").c_str();
        }
        else if (c > ui->listWidget->count()-1-ui->listWidget->currentRow())
        {
            break;
        }
    }

    file.close();
    hmainWindow->LoadState(text, 1);
}







