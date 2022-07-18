#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#elif __APPLE__ || __MACH__
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

QString version = "v1.1";
QString exeName = "dsda-doom";

// Find the name of the OS
std::string getOsName()
{
    #ifdef _WIN32
    return "Windows";
    #elif _WIN64
    return "Windows";
    #elif __APPLE__ || __MACH__
    return "MacOS";
    #else
    return "Linux";
    #endif
}

std::string osName = getOsName();

// If dsda-doom is running
bool running = false;

// List of all the IWADs detected
QStringList images;
QStringList imagesDOOMWADDIR;

QString dotfolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom";
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

// Create an instance of the settings window
Settings *settingsWindow;
Console *consoleWindow;

MainWindow * MainWindow::pMainWindow = nullptr;

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
        ui->compLevelSelect->addItems({"Default","0 - Doom v1.2","1 - Doom v1.666","2 - Doom / Doom 2","3 - Ultimate Doom","4 - Final Doom","5 - DOSDoom","6 - TASDoom","9 - Boom","10 - LxDoom","11 - MBF","17 - Current PrBoom","21 - MBF 21"});
    }
    else if(i==2)
    {
        ui->compLevelSelect->clear();
        ui->compLevelSelect->addItems({"Default","0 - Doom v1.2","1 - Doom v1.666","2 - Doom / Doom 2","3 - Ultimate Doom","4 - Final Doom","5 - DOSDoom","6 - TASDoom","7 - Boom's comp mode","8 - Boom v2.01","9 - Boom","10 - LxDoom","11 - MBF","12 - PrBoom v2.03beta","13 - PrBoom v2.1.0","14 - PrBoom v2.1.1 - 2.2.6","15 - PrBoom v2.3.x","16 - PrBoom v2.4.0","17 - Current PrBoom","21 - MBF 21"});
    }
}

void MainWindow::changeButtonColor(bool isDark)
{
    if(isDark && osName=="MacOS")
    {
        ui->pushButton_5->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                        "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->toolButton->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                      "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
        ui->toolButton_3->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                      "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:5px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");

        ui->widget->setStyleSheet("color: rgb(200, 200, 200);background-color: rgb(100, 100, 100);");
    }
    else if(osName=="MacOS")
    {
        ui->pushButton_5->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                        "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(223,223,223); color: rgb(13,13,13)}");
        ui->toolButton->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                      "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(223,223,223); color: rgb(13,13,13)}");
        ui->toolButton_3->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                      "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:5px; background-color: rgb(223,223,223); color: rgb(13, 13, 13)}");

        ui->widget->setStyleSheet("color: rgb(200, 200, 200);background-color: rgb(175, 175, 175);");
    }
    else if(isDark)
    {
        ui->widget->setStyleSheet("color: rgb(200, 200, 200);background-color: rgb(125, 125, 125);");
    }
    else
    {
        ui->widget->setStyleSheet("color: rgb(200, 200, 200);background-color: rgb(200, 200, 200);");
    }
}

// Lower case all letters of a string
QString lowerCase(std::string word)
{
    for(int i=0;i<word.length();i++)
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
    // Find the IWADs in the correct folder depending on the OS
    if(osName=="MacOS")
    {
        qDebug() << QCoreApplication::applicationDirPath();
        if(!QDir(dotfolder).exists())
            QDir().mkdir(dotfolder);

        if(!QFileInfo(dotfolder+"/"+exeName+".wad").exists())
            QProcess::startDetached("cp", {execPath+"/../Resources/"+exeName+".wad",dotfolder});

        QDir directory(dotfolder);
        images = directory.entryList(QStringList() << "*.WAD",QDir::Files);
    }
    else if(osName=="Linux")
    {
        if(!QDir(dotfolder).exists())
            QDir().mkdir(dotfolder);

        QDir directory(dotfolder);
        images = directory.entryList(QStringList() << "*.WAD",QDir::Files);
    }
    else
    {
        QDir directory = execPath;
        images = directory.entryList(QStringList() << "*.WAD",QDir::Files);
    }

    tilDOOMWADDIR = images.size();
    QDir doomwaddir(doomwaddirstr);
    images += doomwaddir.entryList(QStringList() << "*.WAD",QDir::Files);
    QStringList DOOMWADDIRiwads;

    // This makes sure that a logical order to display the IWADs is followed
    // I think doing this is better than having random orders like: Doom 2 -> TNT -> Doom

    // Normal Doom
    QStringList doomIWADs = {"doom","doom1","doomu","freedoom","freedoom1","bfgdoom","bfgdoom1"};
    for(int j = 0; j < images.size(); j++)
    {
        QString filename = images[j];
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        for(int i = 0; i< doomIWADs.size(); i++)
        {
            if(doomIWADs.at(i) == filename)
            {
                if(j < tilDOOMWADDIR)
                    ui->iwadSelect->addItem(filename);
                else
                    DOOMWADDIRiwads.append(filename);
                doomIWADs.replace(i, " ");
            }
        }
    }

    // Normal Doom 2
    QStringList doom2IWADs = {"doom2","doom2f","freedoom2","bfgdoom2"};
    for(int j = 0; j < images.size(); j++)
    {
        QString filename = images[j];
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        for(int i = 0; i< doom2IWADs.size(); i++)
        {
            if(doom2IWADs.at(i) == filename)
            {
                if(j < tilDOOMWADDIR)
                    ui->iwadSelect->addItem(filename);
                else
                    DOOMWADDIRiwads.append(filename);
                doom2IWADs.replace(i, " ");
            }
        }
    }

    // Final Doom
    QStringList finaldoomIWADs = {"tnt","plutonia"};
    for(int j = 0; j < images.size(); j++)
    {
        QString filename = images[j];
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        for(int i = 0; i< finaldoomIWADs.size(); i++)
        {
            if(finaldoomIWADs.at(i) == filename)
            {
                if(j < tilDOOMWADDIR)
                    ui->iwadSelect->addItem(filename);
                else
                    DOOMWADDIRiwads.append(filename);
                finaldoomIWADs.replace(i, " ");
            }
        }
    }

    // Heretic / Hexen / Chex Quest / Hacx
    QStringList otherIWADs = {"heretic","hexen","chex","hacx"};
    for(int j = 0; j < images.size(); j++)
    {
        QString filename = images[j];
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        for(int i = 0; i< otherIWADs.size(); i++)
        {
            if(otherIWADs.at(i) == filename)
            {
                if(j < tilDOOMWADDIR)
                    ui->iwadSelect->addItem(filename);
                else
                    DOOMWADDIRiwads.append(filename);
                otherIWADs.replace(i, " ");
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
            filename.resize (filename.size () - 4);
            filename=lowerCase(filename.toStdString());
            if(filename!="doom"&&filename!="doom1"&&filename!="doomu"&&filename!="doom2"&&filename!="tnt"&&filename!="plutonia"&&filename!="freedoom1"&&filename!="freedoom"&&filename!="freedoom2"&&filename!="heretic"&&filename!="hexen"&&filename!="chex"&&filename!="hacx")
            {
                    std::ifstream file;
                    if(osName=="MacOS"||osName=="Linux")
                    {
                        file.open(QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom/"+filename.toStdString()+".wad");
                        std::string buffer;
                        while (std::getline(file, buffer)) {
                            if(buffer[0]=='I'&&buffer[1]=='W')
                            {
                                ui->iwadSelect->addItems({filename});
                            }
                            break;
                        }
                    }
                    else
                    {
                        file.open(filename.toStdString()+".wad");
                        std::string buffer;
                        while (std::getline(file, buffer)) {
                            if(buffer[0]=='I'&&buffer[1]=='W')
                            {
                                ui->iwadSelect->addItems({filename});
                            }
                            break;
                        }
                    }
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

    // Allow files to be droped in the launcher (*.wad *.lmp)
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

// Drag Event for *.wad *.lmp *.gfd
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::LoadState(QString fileName)
{
    bool searchingPwads = false;
    std::ifstream file;
    file.open(fileName.toStdString());
    std::string buffer;
    while (std::getline(file, buffer)) {
        if(buffer.substr(0,4)=="iwad" && buffer.substr(4).length()>1)
        {
            for(int i=0; i<ui->iwadSelect->count();i++)
            {
                if(ui->iwadSelect->itemText(i).toStdString()==buffer.substr(5))
                {
                    ui->iwadSelect->setCurrentIndex(i);
                }
            }
        }
        else if(buffer.substr(0,9)=="complevel" && buffer.substr(9).length()>1)
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
        }
        else if(buffer.substr(0,5)=="warp1" && buffer.substr(5).length()>0)
        {
                ui->episodeBox->setText(buffer.substr(6).c_str());
        }
        else if(buffer.substr(0,5)=="warp2" && buffer.substr(5).length()>0)
        {
                ui->levelBox->setText(buffer.substr(6).c_str());
        }
        else if(buffer.substr(0,5)=="skill" && buffer.substr(5).length()>1)
        {
                 ui->diffBox->setCurrentIndex(stoi(buffer.substr(6)));
        }
        else if(buffer.substr(0,4)=="box1" && buffer.substr(4).length()>1)
        {
            if(buffer.substr(5,4)=="true")
                 ui->fastCheck->setChecked(true);
            else
                ui->fastCheck->setChecked(false);
        }
        else if(buffer.substr(0,4)=="box2" && buffer.substr(4).length()>1)
        {
            if(buffer.substr(5,4)=="true")
                 ui->noCheck->setChecked(true);
            else
                ui->noCheck->setChecked(false);
        }
        else if(buffer.substr(0,4)=="box3" && buffer.substr(4).length()>1)
        {
            if(buffer.substr(5,4)=="true")
                 ui->noCheck_4->setChecked(true);
            else
                ui->noCheck_4->setChecked(false);
        }
        else if(buffer.substr(0,4)=="box4" && buffer.substr(4).length()>1)
        {
            if(buffer.substr(5,4)=="true")
                 ui->soloNetCheck->setChecked(true);
            else
                ui->soloNetCheck->setChecked(false);
        }
        else if(buffer.substr(0,10)=="resolution" && buffer.substr(10).length()>1)
        {
            ui->comboBox_2->setCurrentIndex(stoi(buffer.substr(11)));
        }
        else if(buffer.substr(0,10)=="fullscreen" && buffer.substr(10).length()>1)
        {
            if(buffer.substr(11,4)=="true")
                 ui->noCheck_3->setChecked(true);
            else
                ui->noCheck_3->setChecked(false);
        }
        else if(buffer.substr(0,4)=="pwad")
        {
            searchingPwads=true;
        }
        else if(buffer.substr(0,7)=="endpwad")
        {
            searchingPwads=false;
        }
        else if(buffer.substr(0,6)=="record" && buffer.substr(6).length()>0)
        {
                ui->recordDemo->setText(buffer.substr(7).c_str());
        }
        else if(buffer.substr(0,8)=="playback" && buffer.substr(8).length()>0)
        {
                ui->recordDemo_2->setText(buffer.substr(9).c_str());
        }
        else if(buffer.substr(0,12)=="demodropdown" && buffer.substr(12).length()>1)
        {
            ui->demoPlayOptions->setCurrentIndex(stoi(buffer.substr(13)));
        }
        else if(buffer.substr(0,10)=="additional" && buffer.substr(10).length()>0)
        {
            ui->argumentText->setText((buffer.substr(11)).c_str());
        }
        else if(searchingPwads==true)
        {
            ui->wadsOnFolder->addItem(buffer.c_str());
        }

    }
}

const char* bool_cast(const bool b) {
    return b ? "true" : "false";
}
void MainWindow::SaveState(QString fileName)
{
    std::ofstream file_;
    file_.open(fileName.toStdString());
    std::string pwads;
    for(int i=0; i<ui->wadsOnFolder->count();i++)
    {
        pwads += ui->wadsOnFolder->item(i)->text().toStdString()+"\n";
    }
    if(file_.is_open())
        file_ << "iwad="+ui->iwadSelect->currentText().toStdString()+"\ncomplevel="+ui->compLevelSelect->currentText().toStdString().substr(0,2)+"\nwarp1="+ui->episodeBox->text().toStdString()+"\nwarp2="+ui->levelBox->text().toStdString()+"\nskill="+std::to_string(ui->diffBox->currentIndex())+"\nbox1="+bool_cast(ui->fastCheck->isChecked())+"\nbox2="+bool_cast(ui->noCheck->isChecked())+"\nbox3="+bool_cast(ui->noCheck_4->isChecked())+"\nbox4="+bool_cast(ui->soloNetCheck->isChecked())+"\nresolution="+std::to_string(ui->comboBox_2->currentIndex())+"\nfullscreen="+bool_cast(ui->noCheck_3->isChecked())+"\npwad\n"+pwads+"endpwad\nrecord="+ui->recordDemo->text().toStdString()+"\nplayback="+ui->recordDemo_2->text().toStdString()+"\ndemodropdown="+std::to_string(ui->demoPlayOptions->currentIndex())+"\nadditional="+ui->argumentText->toPlainText().toStdString();
    file_.close();

}

void MainWindow::dropFile(QString fileName)
{
    if(lowerCase(fileName.toStdString().substr(fileName.length() - 3))=="lmp") // *.lmp file
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
                                if(osName=="Windows")
                                     folder = execPath;
                                else
                                     folder = dotfolder;
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
                                qDebug() << files0;

                                for(int j=0; j<files0.count(); j++)
                                {
                                    for(int i=0; i<files.count(); i++)
                                    {
                                        if(lowerCase(files[i].toStdString())==lowerCase(files0.at(j).toStdString()))
                                        {
                                            if(j < tilDOOMWADPATH)
                                                ui->wadsOnFolder->addItem(folder+"/"+files0.at(j));
                                            else
                                                if(osName == "Windows")
                                                    ui->wadsOnFolder->addItem("%DOOMWADPATH%/"+files0.at(j));
                                                else
                                                    ui->wadsOnFolder->addItem("$DOOMWADPATH/"+files0.at(j));
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
    else if(lowerCase(fileName.toStdString().substr(fileName.length() - 3))=="wad")
    {
        QStringList wadsToAdd;
        wadsToAdd.append(fileName);
        addWads(wadsToAdd);
        ui->tabs->setCurrentIndex(1);
    }
    else if(lowerCase(fileName.toStdString().substr(fileName.length() - 5))=="state")
    {
           LoadState(fileName);
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
        LoadState(fileNames[0]);
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
            QString launcherText;
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
    QString portText;
    QString portV;

    QString portversion;

    QString path;

    if(osName=="MacOS")
        path = execPath+"/../Resources/"+exeName;
    else if(osName=="Linux")
        path = execPath+"/"+exeName;
    else
        path = execPath+"/"+exeName+".exe";

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::foo() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
    if(osName=="MacOS")
    {
        QProcess::startDetached("open", {dotfolder});
    }
    else if(osName=="Linux")
    {
        QProcess::startDetached("xdg-open", {dotfolder});
    }
    else
    {
        QProcess::startDetached("explorer.exe", {execPath});
    }
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
}

void MainWindow::readyReadStandardOutput()
{
  QProcess *p = (QProcess *)sender();
  QByteArray buf = p->readAllStandardError() + p->readAllStandardOutput();

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
    int complevelIndex = ui->compLevelSelect->currentIndex();
    if(complevelString[0]!='D')
    {
        argList.append("-complevel");
        QString complevelNum;
        complevelNum.push_back(complevelString[0]);
        complevelNum.push_back(complevelString[1]);
        argList.append(complevelNum);
    }

    // Difficulty or Skill
    int diffIndex = ui->diffBox->currentIndex();
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
            if(osName=="Windows")
            {
                for(int i=0; i<fileToAdd.length();i++)
                {
                    if(fileToAdd[i]=='/')
                        fileToAdd[i]='\\';
                }
            }
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
        argList.append(fastParam);
    }
    if(noMo)
    {
        argList.append(nomoParam);
    }
    if(isRespawn)
    {
        argList.append(respawnParam);
    }
    if(isSoloNet)
    {
        argList.append(solonetParam);
    }

    if(ui->comboBox_2->currentIndex()==0)
    {
        if(isFulscreen=="w")
        {
            argList.append("-nofullscreen");
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


    if(ui->recordDemo->text().size()>2)
    {
        argList.append("-record");
        if(returnTooltip)
            argList.append("\""+ui->recordDemo->text()+"\"");
        else
            argList.append(ui->recordDemo->text());
    }

    if(ui->recordDemo_2->text().size()>2)
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

    if (ui->argumentText->toPlainText() != "")
    {
        std::string str = ui->argumentText->toPlainText().toStdString()+" ";

        std::string strToAdd="";
        for( size_t i=0; i<str.length(); i++){

            char c = str[i];
            if( c == ' '){
                 argList.append(strToAdd.c_str());
                 strToAdd="";
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
            for( size_t i=0; i<p.length(); i++)
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
            if(osName=="MacOS")
                file_ << ("\""+execPath+"/../Resources/"+exeName+"\" -iwad \""+dotfolder+"/"+ui->iwadSelect->currentText()+".wad\" ").toStdString()+argStrComplete;
            else if(osName=="Linux")
                file_ << ("\""+execPath+"/"+exeName+"\" -iwad \""+dotfolder+"/"+ui->iwadSelect->currentText()+".wad\" ").toStdString()+argStrComplete;
            else
            {
                std::replace(execPath.begin(),execPath.end(),'/','\\');
                file_ << ("\""+execPath+"\\"+exeName+".exe\" -iwad \""+execPath+"\\"+ui->iwadSelect->currentText()+".wad\" ").toStdString()+argStrComplete;
            }
            file_.close();

            return;
        }

        QMessageBox msgBox;
        msgBox.setText(exeName+" -iwad "+ui->iwadSelect->currentText()+".wad "+argStr.c_str());
        msgBox.addButton(tr("Copy"), QMessageBox::NoRole);
        QPushButton* pButtonYes = msgBox.addButton(tr("Ok"), QMessageBox::YesRole);
        msgBox.setDefaultButton(pButtonYes);
        msgBox.exec();

        if (msgBox.clickedButton()!=pButtonYes)
        {
            QClipboard *clip;
            if(osName=="MacOS")
            {
                if(ui->iwadSelect->currentIndex() < tilDOOMWADDIR)
                    clip->setText("\""+execPath+"/../Resources/"+exeName+"\" -iwad \""+dotfolder+"/"+ui->iwadSelect->currentText()+".wad\" "+argStrComplete.c_str());
                else
                    clip->setText("\""+execPath+"/../Resources/"+exeName+"\" -iwad \""+doomwaddirstr+"/"+ui->iwadSelect->currentText()+".wad\" "+argStrComplete.c_str());
            }
            else if(osName=="Linux")
            {
                if(ui->iwadSelect->currentIndex() < tilDOOMWADDIR)
                    clip->setText("\""+execPath+"/"+exeName+"\" -iwad \""+dotfolder+"/"+ui->iwadSelect->currentText()+".wad\" "+argStrComplete.c_str());
                else
                    clip->setText("\""+execPath+"/"+exeName+"\" -iwad \""+doomwaddirstr+"/"+ui->iwadSelect->currentText()+".wad\" "+argStrComplete.c_str());
            }
            else
            {
                std::replace(execPath.begin(),execPath.end(),'/','\\');
                if(ui->iwadSelect->currentIndex() < tilDOOMWADDIR)
                    clip->setText("\""+execPath+"\\"+exeName+".exe\" -iwad \""+execPath+"\\"+ui->iwadSelect->currentText()+".wad\" "+argStrComplete.c_str());
                else
                    clip->setText("\""+execPath+"\\"+exeName+".exe\" -iwad \""+doomwaddirstr+"\\"+ui->iwadSelect->currentText()+".wad\" "+argStrComplete.c_str());
            }
        }


        return;
    }
    else if(onExit)
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

        settings.setValue("demoplaybox", ui->demoPlayOptions->currentIndex());

        settings.setValue("pwadCount", ui->wadsOnFolder->count());
        for(int i=0; i<ui->wadsOnFolder->count();i++)
        {
            settings.setValue(("pwad"+std::to_string(i)).c_str(),ui->wadsOnFolder->item(i)->text());
        }

        settings.setValue("exeName", exeName);

        return;
    }

    for (int i = 0; i < argList.count(); i++)
        if (argList.at(i) == "")
            argList.removeAt(i);

    consoleWindow->clearText();

    if(osName=="MacOS")
    {
        QFile port = QFile(execPath+"/../Resources/"+exeName+"");
        if(port.exists())
        {
            QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
            if(ui->iwadSelect->currentIndex() < tilDOOMWADDIR)
                argList.push_front(homePath+"/.dsda-doom/"+ui->iwadSelect->currentText()+".wad");
            else
                argList.push_front(doomwaddirstr+"/"+ui->iwadSelect->currentText()+".wad");
            argList.push_front("-iwad");
            QProcess *process = new QProcess(this);
            process->setWorkingDirectory(homePath);
            qDebug() << argList;
            process->start(execPath+"/../Resources/"+exeName, argList);
            connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));
            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
            connect(process, SIGNAL(started()), this, SLOT(started()));
        }
        else
        {
            QMessageBox::warning(this, "dsda-launcher", "Cannot find "+exeName);
        }
    }
    else if(osName=="Linux")
    {
        QFile port = QFile(execPath+"/"+exeName);
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        if(ui->iwadSelect->currentIndex() < tilDOOMWADDIR)
            argList.push_front(homePath+"/.dsda-doom/"+ui->iwadSelect->currentText()+".wad");
        else
            argList.push_front(doomwaddirstr+"/"+ui->iwadSelect->currentText()+".wad");
        argList.push_front("-iwad");
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
    }
    else
    {
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
            if(ui->iwadSelect->currentIndex() < tilDOOMWADDIR)
                argList.push_front(execPath+"/"+ui->iwadSelect->currentText()+".wad");
            else
                argList.push_front(doomwaddirstr+"/"+ui->iwadSelect->currentText()+".wad");
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
    }

    // Again, don't allow the launch button to work twice in the space of 2 secs
    canLaunch=false;
    QTimer::singleShot(2000, this, SLOT(delayLaunch()));
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
    if(sel=="doom"||sel=="doomu"||sel=="doom1"||sel=="freedoom1"||sel=="freedoom"||sel=="bfgdoom1"||sel=="bfgdoom"||sel=="heretic"||sel=="heretic1"||sel=="chex"||sel=="hacx")
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
    /*
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    */
    /*
    QMessageBox msgBox;
    msgBox.setText("dsda-doom ");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    */
}

// Add pwads to be loaded
void MainWindow::on_plus_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select WAD file"),settings.value("primaryPWADFolder").toString(),tr("WAD files (*.wad *.deh *.bex)"));
    ui->wadsOnFolder->addItems(fileNames);
    if(fileNames.length()>0)
    {
        settings.setValue("primaryPWADFolder", fileNames[0]); // Make the folder you got this pwad to be the primary folder for pwads

        std::string p = ui->wadsOnFolder->item(0)->text().toStdString();
        if(p.substr(p.length()-3)=="wad")
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
}

// Remove a pwad form the list
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
    QString demoName = QFileDialog::getSaveFileName(this, tr("Demo file"),QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString().c_str(),tr("lmp files (*.lmp)"));
    ui->recordDemo->setText(demoName);
}

void MainWindow::on_pushButton_3_clicked() // Play demo
{
    QString demoName = QFileDialog::getOpenFileName(this, tr("Demo file"),QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString().c_str(),tr("lmp files (*.lmp)"));
    ui->recordDemo_2->setText(demoName);
}

void MainWindow::on_toolButton_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Pedro-Beirao/dsda-launcher/blob/main/Docs/dsda-doom_parameters.md"));
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
    ui->demoPlayer->setText(("Player: "+player));
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

