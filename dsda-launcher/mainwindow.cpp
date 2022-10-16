#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#elif __APPLE__
#include "Mac.h"
#endif
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QStandardPaths>
#include <QShortcut>
#include <fstream>
#include <iostream>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <vector>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QRegularExpression>
#include <QDesktopServices>
#include <QtConcurrent>
#include <QMessageBox>
#include "settings.h"
#include <string>
#include "console.h"
#include <QClipboard>
#include <sstream>
#include <qgraphicseffect.h>
#include "historylist.h"

// If dsda-doom is running
bool running = false;

QString exeName = "dsda-doom";

#if defined(__APPLE__) || defined(__linux__)
QString dotfolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom";
QString historyPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/history.states";
#else
QString historyPath;
#endif

QString execPath;

// Settings to be stored
QSettings settings("pedrobeirao","dsda-launcher");

// These are the parameters with toggles you can customise
// These names come from the defaults I created
// -fast
QString fastParam = "-fast";

// -nomonsters
QString nomoParam = "-nomonsters";

// -respawn
QString respawnParam = "-respawn";

// -solonet
QString solonetParam = "-solo-net";

// Prevents launching the game twice if the button "Launch" is pressed twice quickly
bool canLaunch = true;

QStringList iwadsPaths;

// Create an instance of the settings window
Settings *settingsWindow;
Console *consoleWindow;
historyList *historyListWindow;

MainWindow * MainWindow::pMainWindow = nullptr;

QStringList doom1IWADs = {
    "doom",
    "doom1",
    "doomu",
    "freedoom",
    "freedoom1",
    "bfgdoom",
    "bfgdoom1",
    "heretic",
    "heretic1",
    "chex",
    "hacx",
    "rekkrsa"
};

MainWindow *MainWindow::getMainWin()
{
    return pMainWindow;
}

void MainWindow::changeExeName(QString newName)
{
    exeName = newName;
}

void MainWindow::changeMaxSkillLevel(int max)
{
    ui->diffBox->clear();
    for(int i=0; i<=max;i++)
    {
        if(i!=0)
            ui->diffBox->addItem(std::to_string(i).c_str());
        else
            ui->diffBox->addItem(" ");
    }
    ui->diffBox->setCurrentIndex(settings.value("skill").toInt());
}

void MainWindow::changeToggles(QString t1, QString a1, QString t2, QString a2, QString t3, QString a3, QString t4, QString a4)
{
    ui->fastCheck->setText(t1);
    ui->fastCheck->setToolTip(a1);
    ui->noCheck->setText(t2);
    ui->noCheck->setToolTip(a2);
    ui->noCheck_4->setText(t3);
    ui->noCheck_4->setToolTip(a3);
    ui->soloNetCheck->setText(t4);
    ui->soloNetCheck->setToolTip(a4);
    fastParam = a1;
    nomoParam = a2;
    respawnParam = a3;
    solonetParam = a4;
}

void MainWindow::changeResolutions(QListWidget *list)
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem(" ");
    for(int i=0;i<list->count();i++)
    {
        ui->comboBox_2->addItem(list->item(i)->text());
    }
}

void MainWindow::changeComplevelsList(int i)
{
    if(i==0)
    {
        ui->compLevelSelect->clear();
        ui->compLevelSelect->addItems({"Default","2 - Doom / Doom 2","3 - Ultimate Doom","4 - Final Doom","9 - Boom","11 - MBF","21 - MBF 21"});
    }
    else if(i==1)
    {
        ui->compLevelSelect->clear();
        ui->compLevelSelect->addItems({"Default","0 - Doom v1.2","1 - Doom v1.666","2 - Doom / Doom 2","3 - Ultimate Doom","4 - Final Doom","5 - DOSDoom","6 - TASDoom","7 - Boom's comp mode","8 - Boom v2.01","9 - Boom","10 - LxDoom","11 - MBF","12 - PrBoom v2.03beta","13 - PrBoom v2.1.0","14 - PrBoom v2.1.1 - 2.2.6","15 - PrBoom v2.3.x","16 - PrBoom v2.4.0","17 - Current PrBoom","21 - MBF 21"});
    }
}

void MainWindow::changeButtonColor(bool isDark)
{

    if(isDark)
    {
        ui->toolButton_4->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); text-align:center; border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                      "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); text-align:center; border-radius:5px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->toolButton_6->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); text-align:center; border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                      "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); text-align:center; border-radius:5px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
    }
    else
    {
        ui->toolButton_4->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); text-align:center; border-radius:5px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                      "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); text-align:center; border-radius:5px; background-color: rgb(223,223,223); color: rgb(13, 13, 13)}");
        ui->toolButton_6->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); text-align:center; border-radius:5px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                      "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); text-align:center; border-radius:5px; background-color: rgb(223,223,223); color: rgb(13, 13, 13)}");
    }
#ifdef __APPLE__
    if(isDark)
    {
        ui->pushButton_5->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                        "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->toolButton->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                      "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->toolButton_3->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                      "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");

        ui->widget->setStyleSheet("color: rgb(200, 200, 200);background-color: rgb(100, 100, 100);");
    }
    else
    {
        ui->pushButton_5->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                        "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(223,223,223); color: rgb(13,13,13)}");
        ui->toolButton->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                      "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(223,223,223); color: rgb(13,13,13)}");
        ui->toolButton_3->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                      "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(223,223,223); color: rgb(13, 13, 13)}");

        ui->widget->setStyleSheet("color: rgb(200, 200, 200);background-color: rgb(175, 175, 175);");
    }
#else
    if(isDark)
    {
        ui->widget->setStyleSheet("color: rgb(200, 200, 200);background-color: rgb(125, 125, 125);");
    }
    else
    {
        ui->widget->setStyleSheet("color: rgb(200, 200, 200);background-color: rgb(200, 200, 200);");
    }
#endif
}

// Lower case all letters of a string
QString lowerCase(std::string word)
{
    for(size_t i=0;i<word.length();i++)
    {
        word[i]=tolower(word[i]);
    }
    return word.c_str();
}

// Prevents launching the game twice if the button "Launch" is pressed twice quickly
void MainWindow::delayLaunch()
{
    canLaunch=true;
}

int tilDOOMWADDIR = 0;

QString doomwaddirstr = QString(qgetenv("DOOMWADDIR"));

void MainWindow::findIwads(int type)
{
    QFileInfoList imagesInfo;
    QStringList images;
    QStringList imagesLower;
    // Find the IWADs in the correct folder depending on the OS
#ifdef __APPLE__
        if(!QDir(dotfolder).exists())
            QDir().mkdir(dotfolder);

        if(!QFileInfo::exists(dotfolder+"/"+exeName+".wad"))
            QProcess::startDetached("cp", {execPath+"/../Resources/"+exeName+".wad",dotfolder});

        QDir directory(dotfolder);
        imagesInfo = directory.entryInfoList(QStringList() << "*.WAD",QDir::Files);
#elif __linux__
        if(!QDir(dotfolder).exists())
            QDir().mkdir(dotfolder);

        QDir directory(dotfolder);
        imagesInfo = directory.entryInfoList(QStringList() << "*.WAD",QDir::Files);
#else
        QDir directory = execPath;
        imagesInfo = directory.entryInfoList(QStringList() << "*.WAD",QDir::Files);
#endif

    tilDOOMWADDIR = imagesInfo.size();
    QDir doomwaddir(doomwaddirstr);
    imagesInfo += doomwaddir.entryInfoList(QStringList() << "*.WAD",QDir::Files);

    foreach(QFileInfo imageInfo, imagesInfo)
    {
        images += imageInfo.absoluteFilePath();
        imagesLower += imageInfo.baseName().toLower();
    }

    QStringList DOOMWADDIRiwads;

    // This makes sure that a logical order to display the IWADs is followed
    // I think doing this is better than having random orders like: Doom 2 -> TNT -> Doom
    QStringList doomIWADs = {
        "doom",
        "doom1",
        "doomu",
        "freedoom",
        "freedoom1",
        "bfgdoom",
        "bfgdoom1",

        "doom2",
        "doom2f",
        "freedoom2",
        "bfgdoom2",

        "tnt",
        "plutonia",


        "heretic",
        "heretic1",
        "hexen",

        "chex",
        "hacx",
        "rekkrsa"
    };

    for(int i = 0; i< doomIWADs.size(); i++)
    {
        for(int j = 0; j < images.size(); j++)
        {
            if(doomIWADs.at(i) == imagesLower[j])
            {
                if(j < tilDOOMWADDIR)
                    ui->iwadSelect->addItem(imagesLower[j]);
                else
                    DOOMWADDIRiwads.append(imagesLower[j]);
                doomIWADs.replace(i, " ");
                iwadsPaths.append(images[j]);
            }
        }
    }


    tilDOOMWADDIR = ui->iwadSelect->count();
    ui->iwadSelect->addItems(DOOMWADDIRiwads);


    // Other wads with the IWAD tag
    // This might make the launcher slower if you have too many wads on the same folder as the launcher
    if(type==1)
    {
        foreach(QString filename, images) {
            if(!doomIWADs.contains(filename))
            {
                    std::ifstream file;
#if defined(__APPLE__) || defined(__linux__)
                        file.open(QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom/"+filename.toStdString()+".wad");
                        std::string buffer;
                        while (std::getline(file, buffer))
                        {
                            if(buffer[0]=='I'&&buffer[1]=='W')
                            {
                                ui->iwadSelect->addItems({filename});
                            }
                            break;
                        }
#else
                        file.open(filename.toStdString()+".wad");
                        std::string buffer;
                        while (std::getline(file, buffer))
                        {
                            if(buffer[0]=='I'&&buffer[1]=='W')
                            {
                                ui->iwadSelect->addItems({filename});
                            }
                            break;
                        }
#endif
            }
        }
    }
}

// MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pMainWindow = this;

    execPath = QCoreApplication::applicationDirPath();
#ifdef _WIN32
historyPath = QCoreApplication::applicationDirPath()+"\\history.states";
#endif

    // Allow files to be droped in the launcher (*.wad *.lmp *.deh *.bex)
    setAcceptDrops(true);

    // Hide the reload Leaderboard button
    ui->ReloadLead->hide();

    // Add event filter to the "additional arguments" box
    ui->argumentText->installEventFilter(this);

    // Add event filter to the Launch button. This will allow you to see the current parameters when you hover your mouse
    ui->LaunchGameButton->installEventFilter(this);

    // set the settings and console windows
    settingsWindow = new Settings;
    consoleWindow = new Console;
    historyListWindow = new historyList;

    // The "episode" and "level" boxes can only take 2 numbers
    // This approach also prevents a problem where Qt tried to add spaces to those boxes if no numbers were added
    QRegularExpression rgx("[0-9]{2}");
    QValidator *comValidator = new QRegularExpressionValidator (rgx, this);
    ui->episodeBox->setValidator(comValidator);
    ui->levelBox->setValidator(comValidator);

    // Keyboard shortcut
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS

    // Closes the active window
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(foo3()));
    shortcut3->setAutoRepeat(false);

    // Set the parameters text correctly
    if(settings.value("toggle1a").toString()!="")
    {
        fastParam = settings.value("toggle1a").toString();
        nomoParam = settings.value("toggle2a").toString();
        respawnParam = settings.value("toggle3a").toString();
        solonetParam = settings.value("toggle4a").toString();
        ui->fastCheck->setText(settings.value("toggle1t").toString());
        ui->fastCheck->setToolTip(fastParam);
        ui->noCheck->setText(settings.value("toggle2t").toString());
        ui->noCheck->setToolTip(nomoParam);
        ui->noCheck_4->setText(settings.value("toggle3t").toString());
        ui->noCheck_4->setToolTip(respawnParam);
        ui->soloNetCheck->setText(settings.value("toggle4t").toString());
        ui->soloNetCheck->setToolTip(solonetParam);
    }


    findIwads(0);


    // If no IWAD found, show a tool tip
    if(ui->iwadSelect->count()==0)
    {
        ui->toolTip->show();
    }
    else
    {
        ui->toolTip->hide();
    }

    // Load settings and apply them
    ui->compLevelSelect->setCurrentIndex(settings.value("complevel").toInt());
    ui->diffBox->setCurrentIndex(settings.value("skill").toInt());
    ui->episodeBox->setText(settings.value("warp1").toString());
    ui->levelBox->setText(settings.value("warp2").toString());
    int pwadCount = settings.value("pwadCount").toInt();
    for(int i=0; i<pwadCount;i++)
    {
        ui->wadsOnFolder->addItem(settings.value(("pwad"+std::to_string(i)).c_str()).toString());

    }
    ui->fastCheck->setChecked(settings.value("fast").toBool());
    ui->noCheck->setChecked(settings.value("nomo").toBool());
    ui->noCheck_4->setChecked(settings.value("respawn").toBool());
    ui->noCheck_3->setChecked(settings.value("fullscreen").toBool());
    ui->comboBox_2->setCurrentIndex(settings.value("geom").toInt());
    if(ui->iwadSelect->count()>=settings.value("iwad").toInt())
    {
        ui->iwadSelect->setCurrentIndex(settings.value("iwad").toInt());
    }
    ui->soloNetCheck->setChecked(settings.value("solonet").toBool());
    ui->argumentText->append(settings.value("argumentText").toString());

    ui->recordDemo->setText(settings.value("recorddemo").toString());
    ui->recordDemo_2->setText(settings.value("playdemo").toString());
    ui->recordDemo_3->setText(settings.value("viddump").toString());
    ui->recordDemo_4->setText(settings.value("hud").toString());
    ui->recordDemo_5->setText(settings.value("config").toString());

    ui->demoPlayOptions->setCurrentIndex(settings.value("demoplaybox").toInt());

    if(ui->demoPlayOptions->currentIndex()!=1)
    {
        ui->recordDemo_3->setHidden(true);
        ui->pushButton_4->setHidden(true);
    }

    if(ui->recordDemo_3->text()=="")
        ui->recordDemo_3->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    else
        ui->recordDemo_3->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");

    if(ui->recordDemo_4->text()=="")
        ui->recordDemo_4->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    else
        ui->recordDemo_4->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");

    if(ui->recordDemo_5->text()=="")
        ui->recordDemo_5->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    else
        ui->recordDemo_5->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");



    if(settings.value("maxskilllevel").toString()!="")
        changeMaxSkillLevel(settings.value("maxskilllevel").toInt());

    if(ui->iwadSelect->currentIndex()==-1 && ui->iwadSelect->count()!=0)
        ui->iwadSelect->setCurrentIndex(0);

    if(ui->episodeBox->text()=="")
    {
        ui->diffBox->setEnabled(false);
        ui->label_5->setEnabled(false);
    }

    QStringList arguments = qApp->arguments();
        if(arguments.count() > 1)
        {
             for(int i=1; i<arguments.count(); i++)
             {
                    QString absPath = arguments.at(i);
                    dropFile(absPath);
             }
        }
}

// Drag Event for *.wad *.lmp *.state *.deh *.bex
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::LoadState(QString fileName, bool isString)
{
    std::stringstream file;

    if (isString)
    {
        file << fileName.toStdString();
    }
    else
    {
        std::ifstream filef(fileName.toStdString());
        if (!filef.is_open())
        {
            return;
        }

        file << filef.rdbuf();
        filef.close();
    }

    std::string buffer;
    std::getline(file, buffer);
    std::getline(file, buffer);
    std::getline(file, buffer);
    if(buffer.substr(0,5)=="iwad=") // iwad
    {
        for(int i=0; i<ui->iwadSelect->count();i++)
        {
            if(ui->iwadSelect->itemText(i).toStdString()==buffer.substr(5))
            {
                ui->iwadSelect->setCurrentIndex(i);
            }
        }
        std::getline(file, buffer);
    }
    if(buffer.substr(0,10)=="complevel=") // complevel
            {
                if(buffer.substr(10)[0]=='D')
                {
                    ui->compLevelSelect->setCurrentIndex(0);
                }
                else
                {
                    for(int i=0; i<ui->compLevelSelect->count();i++)
                    {
                        std::string content=ui->compLevelSelect->itemText(i).toStdString().substr(0,2);
                        if(content==buffer.substr(10))
                        {
                            ui->compLevelSelect->setCurrentIndex(i);
                        }
                    }
                }
                std::getline(file, buffer);
            }
    if(buffer.substr(0,6)=="warp1=") // warp 1
            {
                    ui->episodeBox->setText(buffer.substr(6).c_str());
                    std::getline(file, buffer);
            }
    if(buffer.substr(0,6)=="warp2=") //warp 2
            {
                    ui->levelBox->setText(buffer.substr(6).c_str());
                    std::getline(file, buffer);
            }
    if(buffer.substr(0,6)=="skill=") // skill
            {
                  if (buffer.substr(6).length()>0)
                  {
                     ui->diffBox->setCurrentIndex(stoi(buffer.substr(6)));
                  }
                  else
                  {
                      ui->diffBox->setCurrentIndex(0);
                  }
                  std::getline(file, buffer);
            }
    if(buffer.substr(0,5)=="box1=") // box1
            {
                if(buffer.substr(5,4)=="true")
                     ui->fastCheck->setChecked(true);
                else
                    ui->fastCheck->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,5)=="box2=") // box2
            {
                if(buffer.substr(5,4)=="true")
                     ui->noCheck->setChecked(true);
                else
                    ui->noCheck->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,5)=="box3=") // box3
            {
                if(buffer.substr(5,4)=="true")
                     ui->noCheck_4->setChecked(true);
                else
                    ui->noCheck_4->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,5)=="box4=") //box4
            {
                if(buffer.substr(5,4)=="true")
                     ui->soloNetCheck->setChecked(true);
                else
                    ui->soloNetCheck->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,11)=="resolution=") // resolution
            {
                ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(buffer.substr(11).c_str()));
                std::getline(file, buffer);
            }
    if(buffer.substr(0,11)=="fullscreen=") // fullscreen
            {
                if(buffer.substr(11,4)=="true")
                     ui->noCheck_3->setChecked(true);
                else
                    ui->noCheck_3->setChecked(false);
                std::getline(file, buffer);
            }
    if(buffer.substr(0,4)=="hud=") // hud
            {
                ui->recordDemo_4->setText(buffer.substr(4).c_str());
                std::getline(file, buffer);
            }
    if(buffer.substr(0,7)=="config=") // config
            {
                ui->recordDemo_5->setText(buffer.substr(7).c_str());
                std::getline(file, buffer);
            }
    if(buffer.substr(0,6)=="track=") // track
            {
                if (buffer.substr(6).length()>0)
                {
                    ui->comboBox_3->setCurrentIndex(stoi(buffer.substr(6)));
                }
                else
                {
                    ui->comboBox_3->setCurrentIndex(0);
                }
                std::getline(file, buffer);
            }
     if(buffer.substr(0,5)=="time=") // time
             {
                 if (buffer.substr(5).length()>0)
                 {
                     ui->comboBox_4->setCurrentIndex(stoi(buffer.substr(5)));
                 }
                 else
                 {
                     ui->comboBox_4->setCurrentIndex(0);
                 }
                 std::getline(file, buffer);
             }
    ui->wadsOnFolder->clear();
    if(buffer.substr(0,4)=="pwad")
    {
         while (std::getline(file, buffer))
         {
            if(buffer.substr(0,7)=="endpwad")
                break;
            ui->wadsOnFolder->addItem(buffer.c_str());
         }
         std::getline(file, buffer);
    }
    if(buffer.substr(0,7)=="record=") // record demo
            {
                    ui->recordDemo->setText(buffer.substr(7).c_str());
                    std::getline(file, buffer);
            }
    if(buffer.substr(0,9)=="playback=") // playback demo
            {
                    ui->recordDemo_2->setText(buffer.substr(9).c_str());
                    std::getline(file, buffer);
            }
    if(buffer.substr(0,13)=="demodropdown=") // demo drop down
            {
                if (buffer.substr(13).length()>0)
                {
                    ui->demoPlayOptions->setCurrentIndex(stoi(buffer.substr(13)));
                }
                else
                {
                    ui->demoPlayOptions->setCurrentIndex(0);
                }
                std::getline(file, buffer);
            }
    if(buffer.substr(0,8)=="viddump=") // demo drop down
            {
                ui->recordDemo_3->setText(buffer.substr(8).c_str());
                std::getline(file, buffer);
            }
    if(buffer.substr(0,11)=="additional=") // additional arguments
            {
                ui->argumentText->setText((buffer.substr(11)).c_str());
            }

}

const char* bool_cast(const bool b) {
    return b ? "true" : "false";
}
void MainWindow::SaveState(QString fileName)
{
    std::ofstream file_;
    std::string pwads;
    for(int i=0; i<ui->wadsOnFolder->count();i++)
    {
        pwads += ui->wadsOnFolder->item(i)->text().toStdString()+"\n";
    }
    QString levelbox = "";
    if (!ui->levelBox->isHidden())
    {
        levelbox = ui->levelBox->text();
    }
    QString skillbox = "";
    if (ui->diffBox->isEnabled())
    {
        skillbox = ui->diffBox->currentText();
    }
    if (fileName.at(fileName.size()-1)=='s')
    {
        file_.open(fileName.toStdString(),std::ios_base::app);
        if(file_.is_open())
        {
            file_ << "-\niwad="+ui->iwadSelect->currentText().toStdString()+"\ncomplevel="+ui->compLevelSelect->currentText().toStdString().substr(0,2)+"\nwarp1="+ui->episodeBox->text().toStdString()+"\nwarp2="+levelbox.toStdString()+"\nskill="+skillbox.toStdString()+"\nbox1="+bool_cast(ui->fastCheck->isChecked())+"\nbox2="+bool_cast(ui->noCheck->isChecked())+"\nbox3="+bool_cast(ui->noCheck_4->isChecked())+"\nbox4="+bool_cast(ui->soloNetCheck->isChecked())+"\nresolution="+ui->comboBox_2->currentText().toStdString()+"\nfullscreen="+bool_cast(ui->noCheck_3->isChecked())+"\nhud="+ui->recordDemo_4->text().toStdString()+"\nconfig="+ui->recordDemo_5->text().toStdString()+"\ntrack="+std::to_string(ui->comboBox_3->currentIndex())+"\ntime="+std::to_string(ui->comboBox_4->currentIndex())+"\npwad\n"+pwads+"endpwad\nrecord="+ui->recordDemo->text().toStdString()+"\nplayback="+ui->recordDemo_2->text().toStdString()+"\ndemodropdown="+std::to_string(ui->demoPlayOptions->currentIndex())+"\nviddump="+ui->recordDemo_3->text().toStdString()+"\nadditional="+ui->argumentText->toPlainText().toStdString();
        }

    }
    else
    {
        file_.open(fileName.toStdString());
        if(file_.is_open())
        {
            file_ << "# Do not edit this file manually\n\niwad="+ui->iwadSelect->currentText().toStdString()+"\ncomplevel="+ui->compLevelSelect->currentText().toStdString().substr(0,2)+"\nwarp1="+ui->episodeBox->text().toStdString()+"\nwarp2="+levelbox.toStdString()+"\nskill="+skillbox.toStdString()+"\nbox1="+bool_cast(ui->fastCheck->isChecked())+"\nbox2="+bool_cast(ui->noCheck->isChecked())+"\nbox3="+bool_cast(ui->noCheck_4->isChecked())+"\nbox4="+bool_cast(ui->soloNetCheck->isChecked())+"\nresolution="+ui->comboBox_2->currentText().toStdString()+"\nfullscreen="+bool_cast(ui->noCheck_3->isChecked())+"\nhud="+ui->recordDemo_4->text().toStdString()+"\nconfig="+ui->recordDemo_5->text().toStdString()+"\ntrack="+std::to_string(ui->comboBox_3->currentIndex())+"\ntime="+std::to_string(ui->comboBox_4->currentIndex())+"\npwad\n"+pwads+"endpwad\nrecord="+ui->recordDemo->text().toStdString()+"\nplayback="+ui->recordDemo_2->text().toStdString()+"\ndemodropdown="+std::to_string(ui->demoPlayOptions->currentIndex())+"\nviddump="+ui->recordDemo_3->text().toStdString()+"\nadditional="+ui->argumentText->toPlainText().toStdString();
        }
    }

    file_.close();
    // QProcess::startDetached("chmod", {"a-w", fileName}); windows does have chmod :(

}

void MainWindow::dropFile(QString fileName)
{
    QString tmp = lowerCase(fileName.toStdString().substr(fileName.length() - 4));
    if(tmp==".lmp") // *.lmp file
    {
            ui->tabs->setCurrentIndex(2);
            ui->recordDemo_2->setText(fileName);
            std::ifstream file;
            file.open(fileName.toStdString());
            std::list<std::string> list;
            std::string buffer;
            while (std::getline(file, buffer)) {
                list.push_front(buffer);
            }
            file.close();
            foreach(std::string line, list)
            {
                if(line.substr(0,5)=="-iwad")
                {
                    std::string strToAdd="";
                    QStringList argList;
                    for( size_t i=0; i<line.length(); i++)
                    {
                        char c = line[i];
                        if( c == ' '){
                             argList.append(strToAdd.c_str());
                             strToAdd="";
                        }else if(c == '\"' ){
                            i++;
                            while( line[i] != '\"' ){ strToAdd.push_back(line[i]); i++; }
                        }else{
                            strToAdd.push_back(c);
                        }
                    }
                    for(int i=0;i<argList.count()-1;i++)
                    {
                        if(argList[i]=="-iwad" && argList[i+1]!='-')
                        {
                            ui->iwadSelect->setCurrentIndex(ui->iwadSelect->findText(lowerCase(argList[i+1].toStdString().substr(0,argList[i+1].length()-4))));
                        }
                        else if(argList[i]=="-complevel" && argList[i+1]!='-')
                        {
                            if(argList[i+1].length()==1)
                            {
                                argList[i+1]+=" ";
                            }
                            for(int ii=0;ii<ui->compLevelSelect->count();ii++)
                            {
                                if(ui->compLevelSelect->itemText(ii).startsWith(argList[i+1]))
                                {
                                    ui->compLevelSelect->setCurrentIndex(ii);
                                }
                            }
                        }
                        else if(argList[i]=="-file" && argList[i+1]!='-')
                        {
                            // bool isRecursive = settings.value("pwadrecursive").toBool();

                            QStringList files;
                            for(int ii=1;ii<argList.count()-i;i++)
                            {
                                if(argList[i+ii][0]=='-')
                                {
                                    break;
                                }
                                files.append(argList[i+ii]);
                            }

                            ui->wadsOnFolder->clear();
                            int size = settings.beginReadArray("pwadfolders");
                            if(size!=0)
                            {
                                for (int i = 0; i < size; i++) {
                                    settings.setArrayIndex(i);
                                    QString folder = settings.value("folder").toString();
                                    if(folder!="")
                                    {
                                        QDir path(folder);
                                        QStringList files0 = path.entryList(QDir::Files);
                                        foreach(QString file0, files0)
                                        {
                                            for(int i=0; i<files.count(); i++)
                                            {
                                                if(lowerCase(files[i].toStdString())==lowerCase(file0.toStdString()))
                                                {
                                                    ui->wadsOnFolder->addItem(folder+"/"+file0);
                                                    files.remove(i);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            settings.endArray();



                            if(files.count()!=0)
                            {
                                QString folder;
#ifdef _WIN32
                                folder = execPath;
#else
                                folder = dotfolder;
#endif
                                QDir path(folder);
                                QStringList files0 = path.entryList(QDir::Files);
                                QString f = QString(qgetenv("DOOMWADPATH"));
                                int prev = 0;
                                int tilDOOMWADPATH = files0.size();
                                for(int j = 0; j<f.length(); j++)
                                {
                                    if (f.at(j) == ':' || f.at(j) == ';' || j+1 == f.length())
                                    {
                                        files0.append(QDir(f.mid(prev, j-prev)).entryList(QDir::Files));
                                        prev = j+1;
                                    }
                                }

                                for(int j=0; j<files0.count(); j++)
                                {
                                    for(int i=0; i<files.count(); i++)
                                    {
                                        if(lowerCase(files[i].toStdString())==lowerCase(files0.at(j).toStdString()))
                                        {
                                            if(j < tilDOOMWADPATH)
                                                ui->wadsOnFolder->addItem(folder+"/"+files0.at(j));
                                            else
                                            {
#ifdef _WIN32
                                                ui->wadsOnFolder->addItem("%DOOMWADPATH%/"+files0.at(j));
#else
                                                ui->wadsOnFolder->addItem("$DOOMWADPATH/"+files0.at(j));
#endif
                                            }
                                            files.remove(i);
                                            break;
                                        }
                                    }
                                }
                            }


                        }
                    }
                }
            }
    }
    else if(tmp==".wad" || tmp==".bex" || tmp==".deh")
    {
        QStringList wadsToAdd;
        wadsToAdd.append(fileName);
        addWads(wadsToAdd);
        ui->tabs->setCurrentIndex(1);
    }
    else if(tmp=="tate")
    {
           LoadState(fileName, 0);
    }
}

// Drop Event for *.wad *.lmp *gfd
void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        dropFile(fileName);
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Load State"),settings.value("statefile").toString(),tr("state files (*.state)"));
    if(fileNames.length()>0)
    {
        settings.setValue("statefile", fileNames[0]);
        LoadState(fileNames[0], 0);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save State"),settings.value("statefile").toString(),tr("state files (*.state)"));
    if(fileName != "")
    {
        settings.setValue("statefile", fileName);
        SaveState(fileName);
    }
}

void MainWindow::on_actionGithub_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Pedro-Beirao/dsda-launcher"));
}

void MainWindow::on_actionGithub_2_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/kraflab/dsda-doom"));
}

void MainWindow::on_actionCheck_for_updates_triggered()
{
            QString launcherV;

            QNetworkRequest req(QUrl("https://api.github.com/repos/Pedro-Beirao/dsda-launcher/releases/latest"));
            req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            QJsonObject json;
            QNetworkAccessManager nam;
            QNetworkReply *reply = nam.get(req);
            while (!reply->isFinished())
            {
                qApp->processEvents();
            }
            QByteArray response_data = reply->readAll();
            QJsonDocument jsondoc = QJsonDocument::fromJson(response_data);
            QJsonObject jsonobj = jsondoc.object();
                foreach(const QString& key, jsonobj.keys()) {
                    QJsonValue value = jsonobj.value(key);
                    if(key=="name")
                    {
                        if(version!=value.toString())
                        {
                            QMessageBox msgBox;
                            msgBox.setText("DSDA-Launcher "+version);
                            msgBox.setInformativeText("Available: "+value.toString());
                            QPushButton* pButtonYes = msgBox.addButton(tr("Update"), QMessageBox::YesRole);
                            msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                            msgBox.setDefaultButton(pButtonYes);
                            msgBox.exec();
                            if (msgBox.clickedButton()==pButtonYes)
                            {
                                QDesktopServices::openUrl(QUrl("https://github.com/Pedro-Beirao/dsda-launcher/releases/tag/"+launcherV));
                            }
                        }
                        else
                        {
                            QMessageBox msgBox;
                            msgBox.setText("DSDA-Launcher "+version);
                            msgBox.setInformativeText("Up to Date");
                            msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                            msgBox.exec();
                        }
                    }
                }

            reply->deleteLater();
}

void MainWindow::on_actionCheck_for_Updates_triggered()
{
    QString portversion;

    QString path;

#ifdef __APPLE__
        path = execPath+"/../Resources/"+exeName;
#elif __linux__
        path = execPath+"/"+exeName;
#else
        path = execPath+"/"+exeName+".exe";
#endif
    QFile port = QFile(path);
    if(port.exists())
    {
        QProcess *process = new QProcess;
        process->setWorkingDirectory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        process->start(path, {"-v"});
        process->waitForStarted();
        std::string data;

        while(process->waitForReadyRead())
            data.append(process->readAll());

        std::stringstream  stream(data);
        stream >> data >> data;
        portversion = data.c_str();
    }

    QNetworkRequest req0(QUrl("https://api.github.com/repos/kraflab/dsda-doom/releases/latest"));
    req0.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json0;
    QNetworkAccessManager nam0;
    QNetworkReply *reply0 = nam0.get(req0);
    while (!reply0->isFinished())
    {
        qApp->processEvents();
    }
    QByteArray response_data = reply0->readAll();
    QJsonDocument jsondoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonobj = jsondoc.object();
        foreach(const QString& key, jsonobj.keys()) {
            QJsonValue value = jsonobj.value(key);
            if(key=="name")
            {
                if(portversion!=value.toString())
                {
                    QMessageBox msgBox;
                    msgBox.setText("DSDA-Doom "+portversion);
                    msgBox.setInformativeText("Available: "+value.toString());
                    QPushButton* pButtonYes;
                    pButtonYes = msgBox.addButton(tr("Update"), QMessageBox::YesRole);
                    msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                    msgBox.setDefaultButton(pButtonYes);
                    msgBox.exec();
                    if (msgBox.clickedButton()==pButtonYes)
                    {
                        QDesktopServices::openUrl(QUrl("https://www.doomworld.com/forum/topic/118074-dsda-doom-source-port-v0225/"));
                    }
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setText("DSDA-Doom "+portversion);
                    msgBox.setInformativeText("Up to Date");
                    msgBox.addButton(tr("Ignore"), QMessageBox::NoRole);
                    msgBox.exec();
                }
            }
        }

    reply0->deleteLater();
}

void MainWindow::on_actionSet_triggered()
{
    settingsWindow->show();
    settingsWindow->activateWindow();
    settingsWindow->raise();
}

void MainWindow::on_actionTips_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("A few tips you should know:");
    msgBox.setInformativeText("- Drag .wad / .deh files on top of the launcher to add them to the loaded files\n\n- Drag .lmp files on top of the launcher to play the demo and autoselect the correct IWAD, PWADs and complevel\n\n- For the mentioned autoselect to work correctly, go to the settings and set the PWADs folders");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
void MainWindow::on_actionWhat_is_this_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("State files");
    msgBox.setInformativeText("These .state files save all the parameters selected on the launcher, and lets you load them again whenever you need");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_actionCommand_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export command line"),settings.value("batfile").toString(),tr("batch files (*.bat *.sh *.zsh *.command)"));
    if(fileName != "")
    {
        settings.setValue("batfile", fileName);
        on_LaunchGameButton_clicked(false,true,fileName.toStdString());
    }
}

void MainWindow::on_actionOpen_IWAD_folder_triggered()
{
    foo();
}

void MainWindow::on_actionOpen_Console_triggered()
{
    on_pushButton_clicked();
}

void MainWindow::on_actionHistory_triggered()
{
    if (historyListWindow->isHidden())
    {
        historyListWindow->getHistory();
    }
    historyListWindow->show();
    historyListWindow->activateWindow();
    historyListWindow->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::foo() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
#ifdef __APPLE__
        QProcess::startDetached("open", {dotfolder});
#elif __linux__
        QProcess::startDetached("xdg-open", {dotfolder});
#else
        QProcess::startDetached("explorer.exe", {execPath});
#endif
}


void MainWindow::foo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

void MainWindow::addWads(QStringList fileNames) // Click the + button to add a wad
{
    ui->wadsOnFolder->addItems(fileNames);
}


std::string arguments = " ";

void MainWindow::addToArguments(QString string)
{
    if(ui->argumentText->toPlainText().length()>1 && ui->argumentText->toPlainText().back()!=' ')
        ui->argumentText->setText(ui->argumentText->toPlainText()+" "+string);
    else
        ui->argumentText->setText(ui->argumentText->toPlainText()+string);
}

bool isFast=false;
bool noMo =false;
bool isRespawn=false;
bool isSoloNet = false;
std::string isFulscreen="w";

void MainWindow::error(QProcess::ProcessError error)
{
  qDebug() << "Error: " << error;
}

void MainWindow::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess *p = (QProcess *)sender();
    delete p;
    running = false;
}

void MainWindow::readyReadStandardError()
{

    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardError();

    consoleWindow->changeText(buf.toStdString());
}

void MainWindow::readyReadStandardOutput()
{
  QProcess *p = (QProcess *)sender();
  QByteArray buf = p->readAllStandardOutput();

  consoleWindow->changeText(buf.toStdString());
}

void MainWindow::started()
{
    running = true;
}

void gameIsRunning()
{
    QMessageBox msgBox;
    msgBox.setText(exeName+" is still running.");
    msgBox.addButton("Ok", QMessageBox::YesRole);
    msgBox.exec();
}

void MainWindow::on_LaunchGameButton_clicked(bool onExit, bool returnTooltip, std::string exportCmd) // Runs when you click the launch button or when you close the launcher (When closing, it will not run the game, but actually just save the settings)
{
    if(!canLaunch) // Dont allow 2 launchs in the time of 2 sec
        return;

    if(running && !returnTooltip)
    {
        gameIsRunning();
        return;
    }

    int complevelIndex = ui->compLevelSelect->currentIndex();
    int diffIndex = ui->diffBox->currentIndex();

    if(onExit)
        {
            settings.setValue("iwad",ui->iwadSelect->currentIndex());

            // Again, we need to remove the setting if the additional parameters box is empty so that it does not appear when we open the launcher again
            if(ui->argumentText->toPlainText().toStdString()!="")
            {
                settings.setValue("argumentText",ui->argumentText->toPlainText().toStdString().c_str());
            }
            else
            {
                settings.remove("argumentText");
            }
            settings.setValue("fullscreen", ui->noCheck_3->isChecked());
            settings.setValue("geom",ui->comboBox_2->currentIndex());

            settings.setValue("solonet",isSoloNet);
            settings.setValue("respawn",isRespawn);
            settings.setValue("nomo",noMo);
            settings.setValue("fast",isFast);

            settings.setValue("complevel",complevelIndex);
            settings.setValue("skill",diffIndex);

            settings.setValue("warp1",ui->episodeBox->text().toStdString().c_str());
            settings.setValue("warp2",ui->levelBox->text().toStdString().c_str());

            // We need to remove the setting if the warp number is deleted so that it does not appear when we open the launcher again
            // gzdoom does not do this for the arguments box (at the time of writing, at least) and it drives me nuts
            if(ui->episodeBox->text().toStdString()=="")
            {
                settings.remove("warp1");
            }
            if(ui->levelBox->text().toStdString()=="")
            {
                settings.remove("warp2");
            }

            if(ui->recordDemo->text().toStdString()!="")
            {
                settings.setValue("recorddemo",ui->recordDemo->text());
            }
            else
            {
                settings.remove("recorddemo");
            }

            if(ui->recordDemo_2->text().toStdString()!="")
            {
                settings.setValue("playdemo",ui->recordDemo_2->text());
            }
            else
            {
                settings.remove("playdemo");
            }

            if(ui->recordDemo_3->text().toStdString()!="")
            {
                settings.setValue("viddump",ui->recordDemo_3->text());
            }
            else
            {
                settings.remove("viddump");
            }

            if(ui->recordDemo_4->text().toStdString()!="")
            {
                settings.setValue("hud",ui->recordDemo_4->text());
            }
            else
            {
                settings.remove("hud");
            }

            if(ui->recordDemo_5->text().toStdString()!="")
            {
                settings.setValue("config",ui->recordDemo_5->text());
            }
            else
            {
                settings.remove("config");
            }

            settings.setValue("demoplaybox", ui->demoPlayOptions->currentIndex());

            settings.setValue("pwadCount", ui->wadsOnFolder->count());
            for(int i=0; i<ui->wadsOnFolder->count();i++)
            {
                settings.setValue(("pwad"+std::to_string(i)).c_str(),ui->wadsOnFolder->item(i)->text());
            }

            settings.setValue("exeName", exeName);

            settings.setValue("version", version);

            return;
        }

    QStringList argList;

    /* Complevels:
        Default
        1 - Doom v1.666
        2 - Doom v1.9
        3 - Ultimate Doom & Doom95
        4 - Final Doom
        5 - DOSDoom
        6 - TASDOOM
        7 - Boom's inaccurate vanilla compatibility mode
        8 - Boom v2.01
        9 - Boom v2.02
        10 - LxDoom
        11 - MBF
     12—16 - PrBoom (old versions)
        17 - Current PrBoom
        21 - MBF 21

        If the complevel starts with 'D', then dont use the "-complevel" parameter
        Otherwise, run "-complevel *First+Second char of the string*"
    */
    std::string complevelString = ui->compLevelSelect->currentText().toStdString();
    if(complevelString[0]!='D')
    {
        argList.append("-complevel");
        QString complevelNum;
        complevelNum.push_back(complevelString[0]);
        complevelNum.push_back(complevelString[1]);
        argList.append(complevelNum);
    }

    // Difficulty or Skill
    if(ui->episodeBox->text().length()>0 && ui->diffBox->currentIndex()!=0)
    {
        argList.append("-skill");
        argList.append((std::to_string(diffIndex)).c_str());
    }

    // Warping in Doom takes 2 boxes. 1 for the episode, 1 for the mission
    // Warping in Doom 2 takes 1 box, for the map
    if(ui->levelBox->text().toStdString()!= "" && !ui->levelBox->isHidden())
    {
        argList.append("-warp");
        argList.append(ui->episodeBox->text());
        argList.append(ui->levelBox->text());
    }
    else if(ui->episodeBox->text().toStdString()!= "" && ui->levelBox->isHidden())
    {
        argList.append("-warp");
        argList.append(ui->episodeBox->text());
    }

    /* You can load 3 types of files.
        *.wad -file
        *.deh -deh
        *.bex -deh
    */
    if(ui->wadsOnFolder->count()>0)
    {
        argList.append("-file");
        for(int item=0;item < ui->wadsOnFolder->count(); item++)
        {
            std::string fileToAdd = ui->wadsOnFolder->item(item)->text().toStdString();
#ifdef _WIN32
                for(int i=0; i<fileToAdd.length();i++)
                {
                    if(fileToAdd[i]=='/')
                        fileToAdd[i]='\\';
                }
#endif
            if(fileToAdd.substr(0,5) == "$DOOM")
                fileToAdd = fileToAdd.substr(13);
            else if (fileToAdd.substr(0,5) == "%DOOM")
                fileToAdd = fileToAdd.substr(14);

            if(returnTooltip)
                argList.append(("\""+fileToAdd+"\"").c_str());
            else
                argList.append((fileToAdd).c_str());
        }
    }


    // Again, these are the parameters available on toggles
    if(isFast)
    {
        QString tmp = "";
        for (int i = 0; i < fastParam.length(); i++)
        {
            if (fastParam.at(i) == ';')
            {
                argList.append(tmp);
                tmp = "";
                continue;
            }
            tmp += fastParam.at(i);
        }
        argList.append(tmp);
    }
    if(noMo)
    {
        QString tmp = "";
        for (int i = 0; i < nomoParam.length(); i++)
        {
            if (nomoParam.at(i) == ';')
            {
                argList.append(tmp);
                tmp = "";
                continue;
            }
            tmp += nomoParam.at(i);
        }
        argList.append(tmp);
    }
    if(isRespawn)
    {
        QString tmp = "";
        for (int i = 0; i < respawnParam.length(); i++)
        {
            if (respawnParam.at(i) == ';')
            {
                argList.append(tmp);
                tmp = "";
                continue;
            }
            tmp += respawnParam.at(i);
        }
        argList.append(tmp);
    }
    if(isSoloNet)
    {
        QString tmp = "";
        for (int i = 0; i < solonetParam.length(); i++)
        {
            if (solonetParam.at(i) == ';')
            {
                argList.append(tmp);
                tmp = "";
                continue;
            }
            tmp += solonetParam.at(i);
        }
        argList.append(tmp);
    }

    if(ui->comboBox_2->currentIndex()==0)
    {
        if(isFulscreen=="w")
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
        argList.append((ui->comboBox_2->currentText().toStdString()+isFulscreen).c_str());
    }


    if(ui->recordDemo->text()!="")
    {
        argList.append("-record");
        if(returnTooltip)
            argList.append("\""+ui->recordDemo->text()+"\"");
        else
            argList.append(ui->recordDemo->text());
    }

    if(ui->recordDemo_2->text()!="")
    {
        if(ui->demoPlayOptions->currentIndex()==0)
        {
            argList.append("-playdemo"); // Plays demo at normal speed
            if(returnTooltip)
                argList.append("\""+ui->recordDemo_2->text()+"\"");
            else
                argList.append(ui->recordDemo_2->text());
        }
        else if(ui->demoPlayOptions->currentIndex()==1)
        {
            argList.append("-timedemo"); // Used for viddumping
            if(returnTooltip)
                argList.append("\""+ui->recordDemo_2->text()+"\"");
            else
                argList.append(ui->recordDemo_2->text());
            if(ui->recordDemo_3->text().length()>2)
            {
                argList.append("-viddump");
                if(returnTooltip)
                    argList.append("\""+ui->recordDemo_3->text()+"\"");
                else
                    argList.append(ui->recordDemo_3->text());
            }
        }
        else if(ui->demoPlayOptions->currentIndex()==2)
        {
            argList.append("-fastdemo"); // Used for benchmarks
            if(returnTooltip)
                argList.append("\""+ui->recordDemo_2->text()+"\"");
            else
                argList.append(ui->recordDemo_2->text());
        }
    }

    if(ui->recordDemo_4->text()!="")
    {
        argList.append("-hud");
        if(returnTooltip)
            argList.append("\""+ui->recordDemo_4->text()+"\"");
        else
            argList.append(ui->recordDemo_4->text());
    }

    if(ui->recordDemo_5->text()!="")
    {
        argList.append("-config");
        if(returnTooltip)
            argList.append("\""+ui->recordDemo_5->text()+"\"");
        else
            argList.append(ui->recordDemo_5->text());
    }

    if (ui->comboBox_3->currentIndex()==1)
        argList.append("-track_pacifist");
    else if(ui->comboBox_3->currentIndex()==2)
        argList.append("-track_100k");

    if (ui->comboBox_4->currentIndex()==1)
        argList.append("-time_use");
    else if(ui->comboBox_4->currentIndex()==2)
        argList.append("-time_keys");
    else if(ui->comboBox_4->currentIndex()==3)
        argList.append("-time_secrets");
    else if(ui->comboBox_4->currentIndex()==4)
        argList.append("-time_all");


    if (ui->argumentText->toPlainText() != "")
    {
        std::string str = ui->argumentText->toPlainText().toStdString()+" ";

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


    if(returnTooltip)
    {
        std::string argStr;
        std::string argStrComplete;
        foreach(QString p, argList)
        {
            argStrComplete.append((p+" ").toStdString());

            int lastBar = 0;
            for(qsizetype i=0; i<p.length(); i++)
            {
                if(p[i]=='/' || p[i]=='\\')
                {
                    lastBar=i+1;
                }
            }
            p = p.toStdString().substr(lastBar).c_str();

            if(p.length()>1 && p[0]!='"' && p[p.length()-1]=='"')
            {
                p = p.toStdString().substr(0,p.length()-1).c_str();
            }

            argStr.append((p+" ").toStdString());
        }

        if(exportCmd!="")
        {
            std::ofstream file_;
            file_.open(exportCmd);
            std::string pwads;
#ifdef __APPLE__
                file_ << ("\""+execPath+"/../Resources/"+exeName+"\" -iwad \""+iwadsPaths.at(ui->iwadSelect->currentIndex())+"\" ").toStdString()+argStrComplete;
#elif __linux__
                file_ << ("\""+execPath+"/"+exeName+"\" -iwad \""+iwadsPaths.at(ui->iwadSelect->currentIndex())+"\" ").toStdString()+argStrComplete;
#else
                std::replace(execPath.begin(),execPath.end(),'/','\\');
                file_ << ("\""+execPath+"\\"+exeName+".exe\" -iwad \""+iwadsPaths.at(ui->iwadSelect->currentIndex())+"\" ").toStdString()+argStrComplete;
#endif
            file_.close();

            return;
        }

        QMessageBox msgBox;
        msgBox.setText("Executable: "+exeName+"\nIWAD: "+ui->iwadSelect->currentText()+"\nParameters: "+argStr.c_str());
        msgBox.addButton(tr("Copy"), QMessageBox::NoRole);
        QPushButton* pButtonYes = msgBox.addButton(tr("Ok"), QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        msgBox.exec();

        if (msgBox.clickedButton()!=pButtonYes)
        {
            QClipboard *clip = QApplication::clipboard();
#ifdef __APPLE__
                    clip->setText("\""+execPath+"/../Resources/"+exeName+"\" -iwad \""+iwadsPaths.at(ui->iwadSelect->currentIndex())+"\" "+argStrComplete.c_str());
#elif __linux__
                    clip->setText("\""+execPath+"/"+exeName+"\" -iwad \""+iwadsPaths.at(ui->iwadSelect->currentIndex())+"\" "+argStrComplete.c_str());
#else
                    std::replace(execPath.begin(),execPath.end(),'/','\\');
                    clip->setText("\""+execPath+"\\"+exeName+".exe\" -iwad \""+iwadsPaths.at(ui->iwadSelect->currentIndex())+"\" "+argStrComplete.c_str());
#endif
        }


        return;
    }

    Launch(ui->iwadSelect->currentText(), argList);

    SaveHistory(ui->iwadSelect->currentText(), argList);
}



void MainWindow::Launch(QString iwadName, QStringList argList)
{
    for (int i = 0; i < argList.count(); i++)
    {
        if (argList.at(i) == "")
        {
            argList.removeAt(i);
        }
    }

    consoleWindow->clearText();

#ifdef __APPLE__
        QFile port = QFile(execPath+"/../Resources/"+exeName+"");
        if(port.exists())
        {
            QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
            argList.push_front(iwadsPaths.at(ui->iwadSelect->findText(iwadName)));
            argList.push_front("-iwad");
            QProcess *process = new QProcess;
            process->setWorkingDirectory(homePath);
            process->start(execPath+"/../Resources/"+exeName, argList);
            connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
            connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadStandardError()));
            connect(process, SIGNAL(started()), this, SLOT(started()));
        }
        else
        {
            QMessageBox::warning(this, "dsda-launcher", exeName + " was not found in dsda-launcher.app/Contents/Resources/"+exeName);
        }
#elif __linux__
        QFile port = QFile(execPath+"/"+exeName);
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        argList.push_front(iwadsPaths.at(ui->iwadSelect->findText(iwadName)));
        //system(("cd ~/ && " + execPath+"/dsda-doom -iwad '"+homePath+"/.dsda-doom/"+ui->iwadSelect->currentText().toStdString()+".wad' "+arguments+" >> "+homePath+"/.dsda-doom/LogFile.txt &").c_str());
        // Run "which" command to check if dsda-doom exists. if it does then no need to specify a path, just run a process with exeName.
        QStringList apar; apar << exeName;
        QProcess whichProcess;
        whichProcess.start("which", apar);
        whichProcess.waitForFinished();
        QString processPath;
        // If it finds an executable in the dsda-launcher folder, it will prioritize it over the one installed in a bin folder.
        if(port.exists()) processPath = execPath + "/" + exeName;
        else processPath = exeName;
        if(whichProcess.readAllStandardOutput() != "")
        {
            QProcess *process = new QProcess;
            process->setWorkingDirectory(homePath);
            process->start(processPath, argList);
            connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
            connect(process, SIGNAL(started()), this, SLOT(started()));
        }
        else QMessageBox::warning(this, "dsda-launcher", ("Failed to launch the application executable.\nMake sure that "+ exeName+" is installed correctly through your package manager or installed with the original build instructions.\n\nIf you are sure " + exeName + " exists, symlink it to dsda-launcher's folder."));
#else
    /*
        std::string cmd = "\"" + execPath + "\\dsda-doom.exe \" -iwad \"" + execPath + "\\" + ui->iwadSelect->currentText().toStdString()+".wad\"" + arguments + " >> \""+ execPath+"\\LogFile.txt\" ";
        for(int i=0; i<cmd.length();i++)
        {
            if(cmd[i]=='/')
                cmd[i]='\\';
        }

        STARTUPINFO si={sizeof(si), NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, STARTF_USESHOWWINDOW, SW_SHOWNORMAL};
        PROCESS_INFORMATION pi={};
        std::wstring cmdline = std::wstring(cmd.begin(), cmd.end());
        if (CreateProcess(NULL, const_cast<wchar_t*>(cmdline.c_str()), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS|CREATE_UNICODE_ENVIRONMENT|CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
        } else {
                QMessageBox::warning(this, "dsda-launcher", "Failed to launch the application executable.\nMake sure that the launcher is in the same folder as dsda-doom.exe");
        }

        // system() also works fine, but leaves a cmd window in the background, so CreateProcess() is better
        // system(("cmd /c \""+gamePath+"\"").c_str());

        arguments=" ";
    */
        QFile port = QFile(execPath+"/"+exeName+".exe");
        if(port.exists())
        {
            argList.push_front(iwadsPaths.at(ui->iwadSelect->findText(iwadName)));
            argList.push_front("-iwad");
            QProcess *process = new QProcess;
            process->setWorkingDirectory(execPath);
            process->start(execPath+"/"+exeName+".exe", argList);
            connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
            connect(process, SIGNAL(started()), this, SLOT(started()));
        }
        else
        {
            QMessageBox::warning(this, "dsda-launcher", "Failed to launch the application executable.\nMake sure that the launcher is in the same folder as "+exeName+".exe");
        }
#endif

        // Again, don't allow the launch button to work twice in the space of 2 secs
        canLaunch=false;
        QTimer::singleShot(2000, this, SLOT(delayLaunch()));
}

void MainWindow::SaveHistory(QString iwad, QStringList args)
{
    int checksum = 0;
    int count = 0;
    int needToDelete = 0;

    QString t = iwad;
    for (qsizetype i = 0; i < args.size(); i++)
    {
        t += args.at(i);
    }
    QByteArray arr = t.toLatin1();
    checksum = qChecksum(arr.data(), arr.length());

    std::ostringstream stream;
    if (QFileInfo::exists(historyPath))
    {
        std::ifstream file;
        file.open(historyPath.toStdString());

        if (!file.is_open())
        {
            return;
        }

        std::string buffer;

        while (!file.eof())
        {
            std::getline(file, buffer);
            if (buffer[0]=='-')
            {
                count++;
            }
        }
        file.seekg(0);

        while (buffer.substr(0,9)!="checksum=" && !file.eof())
        {
            std::getline(file, buffer);
        }

        if (buffer.substr(0,9)=="checksum=" && buffer.substr(9).length()>0)
        {
            if (checksum==std::stoi(buffer.substr(9)))
            {
                file.close();
                return;
            }
        }

        stream << file.rdbuf();

        file.close();
    }

    int maxhistory = settings.value("maxhistory").toInt();
    if (count >= maxhistory)
    {
        needToDelete = count - maxhistory + 1;
    }

    std::string h = "# Do not edit this file manually\n\nchecksum="+std::to_string(checksum)+"\n";
    std::string streamstr = stream.str();

    std::ofstream out(historyPath.toStdString()+"s");
    if (!needToDelete)
    {
        if (streamstr!="")
        {
            h += streamstr+"\n";
        }
        out << h;
    }
    else
    {
        if (streamstr!="")
        {
            int past = 0;
            for (size_t i = 0; i < streamstr.length(); i++)
            {
                if (streamstr.substr(i,2) == "-\n")
                {
                    if (past == needToDelete)
                    {
                        streamstr = streamstr.substr(i);
                    }
                    else
                    {
                        past++;
                    }
                }
            }
            h += streamstr+"\n";
        }
        out << h;
    }
    out.close();
    SaveState((historyPath.toStdString()+"s").c_str());
    remove((historyPath.toStdString()).c_str());
    rename((historyPath.toStdString()+"s").c_str(),historyPath.toStdString().c_str());
    // QProcess::startDetached("chmod", {"a-w", historyPath}); windows doesnt have chmod :(


}

// If the IWAD selected changes
void MainWindow::on_iwadSelect_currentIndexChanged(int index)
{
    std::string sel = (ui->iwadSelect->currentText()).toStdString();
    for (int i = 0; i < int(sel.length()); i++)
        {
            sel[i] = tolower(sel[i]);
        }

    // These are episode/mission based. They need both warp boxes
    if(doom1IWADs.contains(sel.c_str()))
    {
        ui->levelBox->show();
        ui->levelText->show();
        ui->episodeText->setText("Episode");
    }
    else // These are map based. They need 1 warp box
    {
        ui->levelBox->hide();
        ui->levelText->hide();
        ui->episodeText->setText("Level");
    }

    // Reload the DSDA leaderboards
    reloadLeaderboard(true,false);
}

// Show the console
void MainWindow::on_pushButton_clicked()
{
    consoleWindow->show();
    consoleWindow->activateWindow();
    consoleWindow->raise();
}

void MainWindow::changeWadLName()
{
    std::string p = ui->wadsOnFolder->item(0)->text().toStdString();
    if(p.substr(p.length()-4)==".wad")
    {
        int lastBar=0;
        for( size_t i=0; i<p.length(); i++){
            if(p[i]=='/' || p[i]=='\\')
            {
                lastBar=i+1;
            }
        }
        p = p.substr(lastBar);
        ui->wadLName->setText(p.substr(0,p.length()-4).c_str());
    }
}

// Add pwads to be loaded
void MainWindow::on_plus_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select WAD file"),settings.value("primaryPWADFolder").toString(),tr("WAD files (*.wad *.deh *.bex)"));
    ui->wadsOnFolder->addItems(fileNames);
    if(fileNames.length()>0)
    {
        settings.setValue("primaryPWADFolder", fileNames[0]); // Make the folder you got this pwad to be the primary folder for pwads
    }
}

// Remove a pwad from the list
void MainWindow::on_minus_clicked()
{
    ui->wadsOnFolder->takeItem(ui->wadsOnFolder->currentRow());
}

// These are the parameter toggles
void MainWindow::on_fastCheck_toggled(bool checked)
{
    if(checked)
        isFast=true;
    else
        isFast=false;
}
void MainWindow::on_noCheck_toggled(bool checked)
{
    if(checked)
        noMo=true;
    else
        noMo=false;
}
void MainWindow::on_noCheck_4_toggled(bool checked)
{
    if(checked)
        isRespawn=true;
    else
        isRespawn=false;
}
void MainWindow::on_soloNetCheck_toggled(bool checked)
{
    if(checked)
        isSoloNet=true;
    else
        isSoloNet=false;
}

void MainWindow::on_noCheck_3_toggled(bool checked)
{
    if(checked)
        isFulscreen="f";
    else
        isFulscreen="w";
}
void MainWindow::on_toolButton_clicked()
{
    if(ui->toolTip->isHidden())
        ui->toolTip->show();
    else
        ui->toolTip->hide();
}

void MainWindow::on_pushButton_2_clicked() // Record demo
{
    QString demoName = QFileDialog::getSaveFileName(this, tr("Demo file"),settings.value("demofolder").toString(),tr("lmp files (*.lmp)"));
    settings.setValue("demofolder",demoName);
    ui->recordDemo->setText(demoName);
}

void MainWindow::on_pushButton_3_clicked() // Play demo
{
    QString demoName = QFileDialog::getOpenFileName(this, tr("Demo file"),settings.value("demofolder").toString(),tr("lmp files (*.lmp)"));
    settings.setValue("demofolder",demoName);
    ui->recordDemo_2->setText(demoName);
}

void MainWindow::on_toolButton_3_clicked()
{
    if (!canLaunch)
        return;

    QString path;

#ifdef __APPLE__
        path = execPath+"/../Resources/"+exeName;
#elif __linux__
        path = execPath+"/"+exeName;
#else
        path = execPath+"/"+exeName+".exe";
#endif

    QFile port = QFile(path);
    if(port.exists())
    {
#ifdef __APPLE__
            QProcess *process = new QProcess;
            process->startDetached("sh", {"-c", "echo \""+path+" --help ; rm /tmp/dsda-doom-params.sh\" > /tmp/dsda-doom-params.sh ; chmod +x /tmp/dsda-doom-params.sh ; open -a Terminal /tmp/dsda-doom-params.sh"});
#elif _WIN32
            system(("cmd /k "+path.toStdString()+" --help").c_str());
#else
            // xterm is the most reliable terminal to use, but it seems a few distros do not have it
            system(("xterm -e 'bash -c \""+path.toStdString()+" --help ;bash\"'").c_str());
#endif
    }

    canLaunch=false;
    QTimer::singleShot(2000, this, SLOT(delayLaunch()));
}

QString demoFile;
void MainWindow::get_leaderboards(std::string wad, std::string level, std::string category) // Get the WR for a run from dsdarchive.com
{
    QString player;
    QString time;
    QString engine;
    QString date;

    QNetworkRequest req(QUrl(QString(("https://dsdarchive.com/api/demos/records?wad="+wad+"&level="+level+"&category="+category).c_str())));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("player", "value1");

    QNetworkAccessManager nam;

    QNetworkReply *reply = nam.get(req);

    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    QByteArray response_data = reply->readAll();

    QJsonDocument jsondoc = QJsonDocument::fromJson(response_data);

    QJsonObject jsonobj = jsondoc.object();
        foreach(const QString& key, jsonobj.keys()) {
            QJsonValue value = jsonobj.value(key);
            if(key=="player")
            {
                player=value.toString();
            }
            else if(key=="time")
            {
                time=value.toString();
            }
            else if(key=="engine")
            {
                engine=value.toString();
            }
            else if(key=="date")
            {
                std::string dateString = value.toString().toStdString();
                dateString=dateString.substr(0,dateString.find("T"));
                date=dateString.c_str();

            }
            else if(key=="file")
            {
                demoFile=value.toString();
            }
        }
    ui->demoTime->setText(("Time: "+time));
    ui->demoPlayer->setText((player));
    ui->demoPort->setText((date));

    reply->deleteLater();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) // This is the category box (UV speed, UV max, etc)
{
    reloadLeaderboard(false,false);
}

bool reloadingLeaderboards=false;

void MainWindow::reloadLeaderboard(bool changeWad, bool callApi)
{

    reloadingLeaderboards=true;
    std::string arg1 = ui->comboBox->currentText().toStdString();
    std::string category;

    // We need to change " " with "%20"
    if(ui->iwadSelect->currentText()=="heretic")
    {
        if(arg1=="SM Speed")
        {
            category = "SM%20Speed";
        }
        else if(arg1=="SM Max")
        {
            category = "SM%20Max";
        }
        else if(arg1=="BP Speed")
        {
            category = "BP%20Speed";
        }
        else if(arg1=="BP Max")
        {
            category = "BP%20Max";
        }
        else if(arg1=="NM Speed")
        {
            category = "NM%20Speed";
        }
        else if(arg1=="NM 100S")
        {
            category = "NM%20100S";
        }
        else if(arg1=="Tyson")
        {
            category = "Tyson";
        }
        else if(arg1=="Pacifist")
        {
            category = "Pacifist";
        }
        else if(arg1=="Stroller")
        {
            category = "Stroller";
        }
        else if(arg1=="NoMo")
        {
            category = "NoMo";
        }
        else if(arg1=="NoMo 100S")
        {
            category = "NoMo%20100S";
        }
        else if(arg1=="Collector")
        {
            category = "Collector";
        }
    }
    else if(ui->iwadSelect->currentText()=="hexen")
    {
        if(arg1=="Sk4 Speed")
        {
            category = "Sk4%20Speed";
        }
        else if(arg1=="Sk4 Max")
        {
            category = "Sk4%20Max";
        }
        else if(arg1=="Sk5 Speed")
        {
            category = "Sk5%20Speed";
        }
        else if(arg1=="Sk5 Max")
        {
            category = "Sk5%20Max";
        }
        else if(arg1=="Tyson")
        {
            category = "Tyson";
        }
        else if(arg1=="Pacifist")
        {
            category = "Pacifist";
        }
        else if(arg1=="Stroller")
        {
            category = "Stroller";
        }
        else if(arg1=="NoMo")
        {
            category = "NoMo";
        }
        else if(arg1=="NoMo 100S")
        {
            category = "NoMo%20100S";
        }
        else if(arg1=="Collector")
        {
            category = "Collector";
        }
    }
    else
    {
        if(arg1=="UV Speed")
        {
            category = "UV%20Speed";
        }
        else if(arg1=="UV Max")
        {
            category = "UV%20Max";
        }
        else if(arg1=="UV Fast")
        {
            category = "UV%20Fast";
        }
        else if(arg1=="UV Respawn")
        {
            category = "UV%20Respawn";
        }
        else if(arg1=="NM Speed")
        {
            category = "NM%20Speed";
        }
        else if(arg1=="NM 100S")
        {
            category = "NM%20100S";
        }
        else if(arg1=="Tyson")
        {
            category = "Tyson";
        }
        else if(arg1=="Pacifist")
        {
            category = "Pacifist";
        }
        else if(arg1=="Stroller")
        {
            category = "Stroller";
        }
        else if(arg1=="NoMo")
        {
            category = "NoMo";
        }
        else if(arg1=="NoMo 100S")
        {
            category = "NoMo%20100S";
        }
        else if(arg1=="Collector")
        {
            category = "Collector";
        }
    }


    std::string wad;
    std::string level;



    if(changeWad)
    {
            wad = lowerCase(ui->iwadSelect->currentText().toStdString()).toStdString();
            if(wad=="doomu"||wad=="doom1")
            {
                wad="doom";
            }
    }
    else
    {
        wad=lowerCase(ui->wadLName->text().toStdString()).toStdString();
    }


    /*
    if(ui->levelBox->text().toStdString()!= "" && !ui->levelBox->isHidden())
    {
        level = "E"+ui->episodeBox->text().toStdString()+"M"+ui->levelBox->text().toStdString();
    }
    else if(ui->episodeBox->text().toStdString()!= "" && ui->levelBox->isHidden())
    {
        if(ui->episodeBox->text().toStdString().length()==1)
        {
            level = "Map0"+ui->episodeBox->text().toStdString();
        }
        else
        {
            level = "Map"+ui->episodeBox->text().toStdString();
        }

    }
    */
    if(ui->wadLName_2->text()=="" || changeWad)
    {
        if(!ui->levelBox->isHidden())
        {
            level = "E1M1";
        }
        else
        {
            level = "Map01";
        }
        ui->wadLName_2->setText(level.c_str());
    }

    level = ui->wadLName_2->text().toStdString();

    wad.erase(std::remove(wad.begin(), wad.end(), ' '), wad.end());
    level.erase(std::remove(level.begin(), level.end(), ' '), level.end());

    if(lowerCase(level.substr(0,2))=="ep")
    {
        level = "Episode%20"+level.substr(2);
    }
    else if(tolower(level[0])=='e')
    {
        level = "E"+level.substr(1,1)+"M"+level.substr(3);
    }
    else if(lowerCase(level.substr(0,3))=="map")
    {
        if(level.substr(3).length()==1)
            level = "Map%200"+level.substr(3);
        else
            level = "Map%20"+level.substr(3);
    }
    else if(lowerCase(level)=="d2all")
    {
        level = "D2All";
    }

    ui->wadLName->setText(wad.c_str());

    if(callApi)
    {
        reloadingLeaderboards=false;
        get_leaderboards(wad,level,category);
    }
    else
    {
        clearLeaderboard();
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event) // ENTER makes the game start
{
    if(event->key()==0x01000005 || event->key()==0x01000004) // Key is either ENTER or RETURN
    {
        on_LaunchGameButton_clicked(false, false,"");
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *ev) // ENTER does not work on the additional parameters box
{

      if (object == (QObject*)ui->LaunchGameButton) {
            //if (ev->type() == QEvent::Enter)
            //{
            //    on_LaunchGameButton_clicked(false, true);
            //    return QWidget::eventFilter(object, ev);
            //}
            if(ev->type() == QEvent::MouseButtonPress)
            {
                on_LaunchGameButton_clicked(false, false,"");
                return QWidget::eventFilter(object, ev);
            }
      }
      if (ev->type() == QEvent::KeyPress)
      {
           QKeyEvent* keyEvent = (QKeyEvent*)ev;

           if (keyEvent->key() == 0x01000005 || keyEvent->key() == 0x01000004) // Key is either ENTER or RETURN
           {
                on_LaunchGameButton_clicked(false, false,"");
                return true;
           }
    }
      return false;
}

void MainWindow::closeEvent(QCloseEvent *event) // When closing the launcher, save the settings
{
    if(running)
    {
        gameIsRunning();
        event->ignore();
        return;
    }
    on_LaunchGameButton_clicked(true, false,"");
    QApplication::quit();
}



void MainWindow::on_toolButton_5_clicked()
{
    std::string str = ui->comboBox->currentText().toStdString();
    std::replace(str.begin(), str.end(), ' ', '+');
    std::string lvl = ui->wadLName_2->text().toStdString();
    lvl.erase(std::remove(lvl.begin(), lvl.end(), ' '), lvl.end());
    if(tolower(lvl[0])=='e')
    {
        lvl = "E"+lvl.substr(1,1)+"M"+lvl.substr(3);
    }
    else if(lowerCase(lvl.substr(0,3))=="map")
    {
        if(lvl.substr(3).length()==1)
            lvl = "Map%200"+lvl.substr(3);
        else
            lvl = "Map%20"+lvl.substr(3);
    }
    QDesktopServices::openUrl(QUrl("https://dsdarchive.com/wads/"+ui->wadLName->text()+"/leaderboard?category="+str.c_str()+"&level="+lvl.c_str()));
}


void MainWindow::clearLeaderboard()
{
    ui->demoTime->setStyleSheet("color: rgb(150, 150, 150);");
    ui->demoPlayer->setStyleSheet("color: rgb(150, 150, 150);");
    ui->demoPort->setStyleSheet("color: rgb(150, 150, 150);");
    ui->ReloadLead->show();
}





void MainWindow::on_ReloadLead_clicked()
{
    reloadLeaderboard(false, true);
    ui->demoTime->setStyleSheet("");
    ui->demoPlayer->setStyleSheet("");
    ui->demoPort->setStyleSheet("");
    ui->ReloadLead->hide();
}


void MainWindow::on_wadLName_textChanged(const QString &arg1)
{
    clearLeaderboard();
    //reloadLeaderboard(false,false);
}

void MainWindow::on_wadLName_2_textChanged(const QString &arg1)
{
    clearLeaderboard();
    //reloadLeaderboard(false,false);
}

void MainWindow::on_recordDemo_3_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->recordDemo_3->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->recordDemo_3->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
}


void MainWindow::on_demoPlayOptions_currentIndexChanged(int index)
{
    if(index!=1)
    {
        ui->recordDemo_3->setHidden(true);
        ui->pushButton_4->setHidden(true);
    }
    else
    {
        ui->recordDemo_3->setHidden(false);
        ui->pushButton_4->setHidden(false);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QString vidName = QFileDialog::getSaveFileName(this, tr("mp4 / mkv"),QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString().c_str(),tr("video files(*.mp4 *.mkv)"));
    ui->recordDemo_3->setText(vidName);
}


void MainWindow::on_pushButton_5_clicked()
{
    on_LaunchGameButton_clicked(false,true,"");
}


void MainWindow::on_episodeBox_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->diffBox->setEnabled(false);
        ui->label_5->setEnabled(false);
    }
    else
    {
        ui->diffBox->setEnabled(true);
        ui->label_5->setEnabled(true);
    }

}

void MainWindow::on_toolButton_4_clicked()
{
   ui->toolButton_4->setText("-");
   nextStackedWidget();
}

void MainWindow::on_toolButton_6_clicked()
{
    ui->toolButton_6->setText("-");
    previousStackedWidget();
}



void MainWindow::nextStackedWidget()
{
    ui->stackedWidget->widget(ui->stackedWidget->currentIndex()+1)->show();

    QPropertyAnimation *anim = new QPropertyAnimation(ui->stackedWidget->currentWidget(), "pos");
    anim->setDuration(350);
    anim->setEasingCurve(QEasingCurve::OutQuart);
    anim->setStartValue(QPoint(0, 0));
    anim->setEndValue(QPoint(-265, 0));

    QPropertyAnimation *animn = new QPropertyAnimation(ui->stackedWidget->widget(ui->stackedWidget->currentIndex()+1), "pos");
    animn->setDuration(350);
    animn->setEasingCurve(QEasingCurve::OutQuart);
    animn->setStartValue(QPoint(265, 0));
    animn->setEndValue(QPoint(0, 0));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(anim);
    animgroup->addAnimation(animn);

    animgroup->start(QAbstractAnimation::DeleteWhenStopped);

     connect(animgroup, SIGNAL(finished()),this,SLOT(whenAnimationFinishn()));
}

void MainWindow::previousStackedWidget()
{
    ui->stackedWidget->widget(ui->stackedWidget->currentIndex()-1)->show();

    QPropertyAnimation *anim = new QPropertyAnimation(ui->stackedWidget->currentWidget(), "pos");
    anim->setDuration(350);
    anim->setEasingCurve(QEasingCurve::OutQuart);
    anim->setStartValue(QPoint(0, 0));
    anim->setEndValue(QPoint(265, 0));

    QPropertyAnimation *animn = new QPropertyAnimation(ui->stackedWidget->widget(ui->stackedWidget->currentIndex()-1), "pos");
    animn->setDuration(350);
    animn->setEasingCurve(QEasingCurve::OutQuart);
    animn->setStartValue(QPoint(-265, 0));
    animn->setEndValue(QPoint(0, 0));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;
    animgroup->addAnimation(anim);
    animgroup->addAnimation(animn);

    animgroup->start(QAbstractAnimation::DeleteWhenStopped);

     connect(animgroup, SIGNAL(finished()),this,SLOT(whenAnimationFinishp()));
}

void MainWindow::whenAnimationFinishn()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    ui->toolButton_4->setText(">");
}

void MainWindow::whenAnimationFinishp()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    ui->toolButton_6->setText("<");
}



void MainWindow::on_recordDemo_4_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->recordDemo_4->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->recordDemo_4->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
}


void MainWindow::on_recordDemo_5_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->recordDemo_5->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->recordDemo_5->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("DSDAHUD.lmp"),settings.value("hudfolder").toString(),tr("DSDAHUD file (*.lmp)"));
    settings.setValue("hudfolder",fileName);
    ui->recordDemo_4->setText(fileName);
}


void MainWindow::on_pushButton_7_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("dsda-doom.cfg"),settings.value("configfolder").toString(),tr("Config file (*.cfg)"));
    settings.setValue("configfolder",fileName);
    ui->recordDemo_5->setText(fileName);
}


