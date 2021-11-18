#include <windows.h>
#include <stdio.h>
#include <tchar.h>
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
#include <QSettings>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QRegularExpression>
#include <QDesktopServices>
#include <QtConcurrent>
#include <QMessageBox>

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

// List of all the IWADs detected
QStringList images;

// Settings to be stored
QSettings settings("pedrobeirao","dsda-launcher");

// These are the parameters with toggles you can customise
// These names come from the defaults I created
// ...ParamText is the text displayed on the launcher
// ...Param is the parameter loaded
// -fast
std::string fastParamText;
std::string fastParam;

// -nomonsters
std::string nomoParamText;
std::string nomoParam;

// -respawn
std::string respawnParamText;
std::string respawnParam;

// -solonet
std::string solonetParamText;
std::string solonetParam;

// This is the bottom row that you can customise
// 0 = Error / Nothing detected
// 1 = Default
// 2 = Custom
int bottomRow = 0;

// Prevents launching the game twice if the button "Launch" is pressed twice quickly
bool canLaunch = true;

// Lower case all letters of a string
QString lowerCase(std::string word)
{
    for(int i=0;i<word.length();i++)
    {
        word[i]=tolower(word[i]);
    }
    return word.c_str();
}

// Prevents launching the game twice if the button "Launch" is presse twice quickly
void MainWindow::delayLaunch()
{
    canLaunch=true;
}

// MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Allow files to be droped in the launcher (*.wad *.lmp)
    setAcceptDrops(true);

    // Add event filter to the "additional arguments" box
    ui->argumentText->installEventFilter(this);

    // Add event filter to the Launch button. This will allow you to see the current parameters when you hover your mouse
    ui->LaunchGameButton->installEventFilter(this);

    // The "episode" and "level" boxes can only take 2 numbers
    // This approach also prevents a problem where QT tried to add spaces to those boxes if no numbers were added
    QRegularExpression rgx("[0-9]{2}");
    QValidator *comValidator = new QRegularExpressionValidator (rgx, this);
    ui->episodeBox->setValidator(comValidator);
    ui->levelBox->setValidator(comValidator);

    // Keyboard shortcuts
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS
    // Open the folder to add the IWADs
    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_O | Qt::CTRL),this,SLOT(foo()));
    shortcut->setAutoRepeat(false);

    /* Might cause memory leaks, so Im going to comment this out for now
    // Creates a new instance of the MainWindow
    QShortcut * shortcut2 = new QShortcut(QKeySequence(Qt::Key_N | Qt::CTRL),this,SLOT(foo2()));
    shortcut2->setAutoRepeat(false);
    */

    // Closes the active window
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(foo3()));
    shortcut3->setAutoRepeat(false);

    // Hides some UI that looks ugly if hidden in other QT ways
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->demoPlayOptions->hide();

    // The 4 lines for the 4 parameter toggles
    int currentConfigLine = 0;

    // The 2 "+" lines for the bottom row texts
    int currentConfigBottomBox = 0;

    // The x lines for the bottom row boxes
    bool afterPlus = false;

    // launcher_config.txt file is where you can customise the launcher
    std::fstream newfile;
    std::string launcher_configFilePath;

    // Check if the launcher_config.txt file exists
    // If not, create it
    if(getOsName()=="MacOS")
    {
        try {
            system(("mkdir "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom").c_str());
        }  catch (...) { }
        QFileInfo check_file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/launcher_config.txt");
        if(!check_file.exists())
            system(("cp "+QCoreApplication::applicationDirPath()+"/../Resources/launcher_config.txt "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/").toStdString().c_str());

        launcher_configFilePath=(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/launcher_config.txt").toStdString();
    }
    else if(getOsName()=="Windows")
    {
        QFileInfo check_file(QCoreApplication::applicationDirPath()+"/launcher_config.txt");
        if(!check_file.exists())
        {
            std::ofstream file_;
            file_.open((QCoreApplication::applicationDirPath()+"/launcher_config.txt").toStdString());
            if(file_.is_open())
                file_ << "# For a complete guide on how to customize this launcher:\n# https://github.com/Pedro-Beirao/dsda-launcher/blob/main/Docs/launcher_config_guide.md\n\n\n\n\"Fast Monsters\" \"-fast\"\n\"No Monsters\" \"-nomonsters\"\n\n\"Respawn Monsters\" \"-respawn\"\n\n\"Solo Net\" \"-solo-net\"\n\n\n\n# Bottom row type:\n\n1\n\n\n\n# Edit the following, ONLY if you chose \"2\" before\n\n+\"Time\"\n\"-time_use\"\n\"-time_keys\"\n\"-time_secrets\"\n\"-time_all\"\n\n\n+\"Stats\"\n\"-levelstat\"\n\"-analysis\"\n\"both\"\n";
            file_.close();
        }

        launcher_configFilePath=(QCoreApplication::applicationDirPath()+"/launcher_config.txt").toStdString();
    }
    else
    {
        try {
            system(("mkdir "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom").c_str());
        }  catch (...) { }
        QFileInfo check_file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/launcher_config.txt");
        if(!check_file.exists())
        {
            std::ofstream file_;
            file_.open((QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/launcher_config.txt").toStdString());
            if(file_.is_open())
                file_ << "# For a complete guide on how to customize this launcher:\n# https://github.com/Pedro-Beirao/dsda-launcher/blob/main/Docs/launcher_config_guide.md\n\n\n\n\"Fast Monsters\" \"-fast\"\n\"No Monsters\" \"-nomonsters\"\n\n\"Respawn Monsters\" \"-respawn\"\n\n\"Solo Net\" \"-solo-net\"\n\n\n\n# Bottom row type:\n\n1\n\n\n\n# Edit the following, ONLY if you chose \"2\" before\n\n+\"Time\"\n\"-time_use\"\n\"-time_keys\"\n\"-time_secrets\"\n\"-time_all\"\n\n\n+\"Stats\"\n\"-levelstat\"\n\"-analysis\"\n\"both\"\n";
            file_.close();
        }
        launcher_configFilePath=(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/launcher_config.txt").toStdString();
    }

    // Open the launcher_config.txt file
    newfile.open(launcher_configFilePath,std::ios::in);
       if (newfile.is_open()){
           // tp will be looped on every line
          std::string tp;
          try {
              while(getline(newfile, tp))
              {
                  // If the first/second/third char is "#", then this is a comment, ignore
                  // If the line is too small, ignore
                if((tp[0]!='#'&&tp[1]!='#'&&tp[2]!='#') && tp.length()>3)
                {
                    // We need 2 strings, the Text and the Parameter
                    // The Text is between the first and second quotes
                    // The Parameter is between the third and forth quotes
                    int firstQuotes=100;
                    int secondQuotes=100;
                    int thirdQuotes=100;
                    int forthQuotes=100;

                    for(int i=0;i<tp.length();i++) // Loop the chars to find the 4 quotes
                    {
                        if(tp[i]=='"')
                        {
                            if(firstQuotes==100)
                            {
                                firstQuotes=i;
                            }
                            else if(secondQuotes==100)
                            {
                                secondQuotes=i;
                            }
                            else if(thirdQuotes==100)
                            {
                                thirdQuotes=i;
                            }
                            else if(forthQuotes==100)
                            {
                                forthQuotes=i;
                            }
                        }
                    }

                    // Find the strings using substr of tp
                    if(currentConfigLine==0)
                    {
                        fastParamText=tp.substr(firstQuotes+1,secondQuotes-firstQuotes-1);
                        fastParam=tp.substr(thirdQuotes+1,forthQuotes-thirdQuotes-1);
                        currentConfigLine++;
                    }
                    else if(currentConfigLine==1)
                    {
                        nomoParamText=tp.substr(firstQuotes+1,secondQuotes-firstQuotes-1);
                        nomoParam=tp.substr(thirdQuotes+1,forthQuotes-thirdQuotes-1);
                        currentConfigLine++;
                    }
                    else if(currentConfigLine==2)
                    {
                        respawnParamText=tp.substr(firstQuotes+1,secondQuotes-firstQuotes-1);
                        respawnParam=tp.substr(thirdQuotes+1,forthQuotes-thirdQuotes-1);
                        currentConfigLine++;
                    }
                    else if(currentConfigLine==3)
                    {
                        solonetParamText=tp.substr(firstQuotes+1,secondQuotes-firstQuotes-1);
                        solonetParam=tp.substr(thirdQuotes+1,forthQuotes-thirdQuotes-1);
                        currentConfigLine++;
                    }
                    if(bottomRow==2) // If the bottom row can be customised
                    {
                        if(tp[0]=='+') // "+" means that its the text at the top of the drop down menus
                        {
                            afterPlus=true;
                            int firstQuotesBottomText=100;
                            int secondQuotesBottomText=100;
                            for(int i=0;i<tp.length();i++)
                            {
                                if(tp[i]=='"')
                                {
                                    if(firstQuotesBottomText==100)
                                    {
                                        firstQuotesBottomText=i;
                                    }
                                    else if(secondQuotesBottomText==100)
                                    {
                                        secondQuotesBottomText=i;
                                    }
                                }
                            }

                            if(currentConfigBottomBox==0)
                            {
                                ui->label_6->setText(tp.substr(firstQuotesBottomText+1,secondQuotesBottomText-firstQuotesBottomText-1).c_str());

                                // Needed to make the font bigger because it looked odd
                                int size = ui->label_6->font().pointSize()+2;
                                QFont newFont(ui->label_6->font().family(),size);
                                ui->label_6->setFont(newFont);
                                currentConfigBottomBox++;
                            }
                            else if(currentConfigBottomBox==1)
                            {
                                ui->label_10->setText(tp.substr(firstQuotesBottomText+1,secondQuotesBottomText-firstQuotesBottomText-1).c_str());

                                // Needed to make the font bigger because it looked odd
                                int size = ui->label_10->font().pointSize()+2;
                                QFont newFont(ui->label_10->font().family(),size);
                                ui->label_10->setFont(newFont);
                                currentConfigBottomBox++;
                            }
                        }
                        else if(afterPlus)
                        {
                            if(tp[0]=='"')
                            {
                                int firstQuotesBottomBox=100;
                                int secondQuotesBottomBox=100;
                                for(int i=0;i<tp.length();i++)
                                {
                                    if(tp[i]=='"')
                                    {
                                        if(firstQuotesBottomBox==100)
                                        {
                                            firstQuotesBottomBox=i;
                                        }
                                        else if(secondQuotesBottomBox==100)
                                        {
                                            secondQuotesBottomBox=i;
                                        }
                                    }
                                }
                                std::string itemToAdd;
                                if(tp.substr(firstQuotesBottomBox+1,secondQuotesBottomBox-firstQuotesBottomBox-1)=="both"||tp.substr(firstQuotesBottomBox+1,secondQuotesBottomBox-firstQuotesBottomBox-1)=="all")
                                    itemToAdd=" "+tp.substr(firstQuotesBottomBox+1,secondQuotesBottomBox-firstQuotesBottomBox-1);
                                else
                                    itemToAdd=tp.substr(firstQuotesBottomBox+1,secondQuotesBottomBox-firstQuotesBottomBox-1);

                                if(currentConfigBottomBox==1)
                                    ui->timeKeysBox->addItem(itemToAdd.c_str());
                                else if(currentConfigBottomBox==2)
                                    ui->levelstatBox->addItem(itemToAdd.c_str());
                            }
                            else
                            {
                                afterPlus=false;
                            }
                        }
                    }
                }
                else if(tp[0]=='1' || tp[1]=='1') // If it finds a "1" at the beguining of the line, then its the Default bottom row
                {
                    ui->timeKeysBox->hide();
                    ui->levelstatBox->hide();
                    ui->label_10->hide();
                    bottomRow=1;
                    ui->comboBox_2->show();
                    ui->noCheck_3->show();
                    ui->label_6->show();
                }
                else if(tp[0]=='2' || tp[1]=='2') // If it finds a "2" at the beguining of the line, then its the Custom bottom row
                {
                    ui->comboBox_2->hide();
                    ui->noCheck_3->hide();
                    bottomRow=2;
                    ui->timeKeysBox->show();
                    ui->levelstatBox->show();
                    ui->label_10->show();
                    ui->label_6->show();
                }
                else if(bottomRow==0) // If it finds a "0" at the beguining of the line, then there was an error
                {
                    ui->timeKeysBox->hide();
                    ui->levelstatBox->hide();
                    ui->label_10->hide();
                    ui->comboBox_2->hide();
                    ui->noCheck_3->hide();
                    ui->label_6->hide();
                }
              }

              // Dont forget to close :P
              newfile.close();

          }  catch (...) {
              // Alright, found an error with the launcher_config.txt file, the launcher is still kinda usable, but its should be VERY clear to the user that something is not right
            qDebug() << "crash :(";

            on_editParameters_clicked();
          }
       }

    // Set the parameters text correctly
    ui->fastCheck->setText(fastParamText.c_str());
    ui->noCheck->setText(nomoParamText.c_str());
    ui->noCheck_4->setText(respawnParamText.c_str());
    ui->soloNetCheck->setText(solonetParamText.c_str());

    // Find the IWADs in the correct folder depending on the OS
    if(getOsName()=="MacOS" || getOsName()=="Linux")
    {
        try {
            system(("mkdir "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom").c_str());
            system(("cp "+QCoreApplication::applicationDirPath().toStdString()+"/../Resources/dsda-doom.wad "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom").c_str());

        }  catch (...) { }

        QDir directory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom");
        images = directory.entryList(QStringList() << "*.WAD",QDir::Files);
    }
    else
    {
        QDir directory = QDir::currentPath();
        images = directory.entryList(QStringList() << "*.WAD",QDir::Files);

        // Looked weird otherwise
        ui->pushButton_2->setStyleSheet("color: rgb(50, 50, 50);");
    }

    // This makes sure that a logic order to display the IWADs is followed
    // I think doing this is better than having random orders like: Doom 2 -> TNT -> Doom

    // Normal Doom
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="doom")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Shareware Doom
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="doom1")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Ultimate Doom
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="doomu")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Normal Doom 2
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="doom2")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // French Doom 2
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="doom2f")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // TNT
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="tnt")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Plutonia
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="plutonia")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // FreeDoom Phase 1
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="freedoom1" || filename=="freedoom")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // FreeDoom Phase 2
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="freedoom2")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Heretic
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="heretic")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Hexen
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="hexen")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // BFG Doom
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="bfgdoom1"||filename=="bfgdoom")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // BFG Doom 2
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="bfgdoom2")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Chex Quest 1
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="chex")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Hacx
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename=="hacx")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    // Other wads with the IWAD tag
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        filename=lowerCase(filename.toStdString());
        if(filename!="doom"&&filename!="doom1"&&filename!="doomu"&&filename!="doom2"&&filename!="tnt"&&filename!="plutonia"&&filename!="freedoom1"&&filename!="freedoom"&&filename!="freedoom2"&&filename!="heretic"&&filename!="hexen"&&filename!="chex"&&filename!="hacx")
        {
                std::ifstream file;
                if(getOsName()=="MacOS"||getOsName()=="Linux")
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
    try {
        ui->wadsOnFolder->addItem(settings.value("pwad1").toString());
        ui->wadsOnFolder->addItem(settings.value("pwad2").toString());
        ui->wadsOnFolder->addItem(settings.value("pwad3").toString());
    }  catch (...) {

    }
    for(int itemIndex = ui->wadsOnFolder->count()-1; itemIndex>=0; itemIndex--)
    {
        if(ui->wadsOnFolder->item(itemIndex)->text().toStdString().length()<5)
        {
            ui->wadsOnFolder->takeItem(itemIndex);
        }
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
    ui->timeKeysBox->setCurrentIndex(settings.value("timeKeys").toInt());
    ui->levelstatBox->setCurrentIndex(settings.value("levelstat").toInt());
}

// Drag Event for *.wad *.lmp
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

// Drop Event for *.wad *.lmp
void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        if(fileName.toStdString().back()=='p'||fileName.toStdString().back()=='P') // *.lmp file ends with "p"
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
                    std::string iwadText = "-iwad";
                    if(line.substr(0,5)=="-iwad")
                    {
                        std::vector< int > aspas; // "aspas" means "quotes" on portuguese, I dont feel like changing it rn :P
                        for(unsigned charIndex =0;charIndex<=line.length();charIndex++)
                        {
                            if(line[charIndex]=='"')
                            {
                                aspas.push_back(charIndex);
                            }
                        }
                        std::string iwadFile = line.substr(aspas[0]+1,aspas[1]-aspas[0]-1);
                        for(int item=0;item < ui->iwadSelect->count(); item++)
                        {
                            for(unsigned letterIndex=0;letterIndex<iwadFile.length();letterIndex++)
                            {
                                if(isupper(iwadFile[letterIndex]))
                                {
                                    iwadFile[letterIndex] = tolower(iwadFile[letterIndex]);
                                }
                            }
                            if(ui->iwadSelect->itemText(item).toStdString()+".wad"==iwadFile)
                            {
                                ui->iwadSelect->setCurrentIndex(item);
                            }
                        }
                    }
                }
        }
        else if(fileName.toStdString().back()=='d'||fileName.toStdString().back()=='D')
        {
            QStringList wadsToAdd;
            wadsToAdd.append(fileName);
            addWads(wadsToAdd);
            ui->tabs->setCurrentIndex(1);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::foo() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
    if(getOsName()=="MacOS"|| getOsName()=="Linux")
    {
        system(("open \""+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom\"").c_str());
    }
    else
    {
        system(("start \""+QCoreApplication::applicationDirPath().toStdString() + "\"").c_str());
    }
}

void MainWindow::foo2() // CTRL+N runs this function to open a new instance of the MainWindow
{
    MainWindow *newMainWindow = new MainWindow;
    newMainWindow->show();
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
bool isFast=false;
bool noMo =false;
bool isRespawn=false;
bool isSoloNet = false;
std::string isFulscreen="w";


void MainWindow::on_LaunchGameButton_clicked(bool onExit, bool returnTooltip) // Runs when you click the launch button or when you close the launcher (When closing, it will not run the game, but actually just save the settings)
{
    if(!canLaunch) // Dont allow 2 launchs in the time of 2 sec
        return;

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
    settings.setValue("complevel",complevelIndex);
    if(complevelString[0]!='D')
    {
        std::string complevelText = " -complevel ";
        complevelText.push_back(complevelString[0]);
        complevelText.push_back(complevelString[1]);
        arguments+=complevelText+" ";
    }

    // Difficulty or Skill
    int diffIndex = ui->diffBox->currentIndex();
    settings.setValue("skill",diffIndex);
    if(ui->episodeBox->text().length()>0)
    {
        std::string skillArg = " -skill ";
        arguments+=" -skill "+std::to_string(diffIndex)+" ";
    }

    // Warping in Doom takes 2 boxes. 1 for the episode, 1 for the mission
    // Warping in Doom 2 takes 1 box, for the map
    if(ui->levelBox->text().toStdString()!= "" && !ui->levelBox->isHidden())
    {
        arguments += " -warp "+ui->episodeBox->text().toStdString()+" "+ui->levelBox->text().toStdString();
        settings.setValue("warp1",ui->episodeBox->text().toStdString().c_str());
        settings.setValue("warp2",ui->levelBox->text().toStdString().c_str());
    }
    else if(ui->episodeBox->text().toStdString()!= "" && ui->levelBox->isHidden())
    {
        arguments += " -warp "+ui->episodeBox->text().toStdString();
        settings.setValue("warp1",ui->episodeBox->text().toStdString().c_str());
        settings.remove("warp2");
    }

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

    // You can store 3 pwads at a time
    // There are better ways of doing this that even allow more pwads to be stored, but noone loads more than 3 pwads at a time in boom
    // When I make a fork of this launcher to accept any source port, I'll be sure to fix this so people can enjoy Brootal Dewm, Too Many Shotguns, Russian Overkill and HDoom at the same time
    try {
        settings.setValue("pwad1","");
        settings.setValue("pwad2","");
        settings.setValue("pwad3","");

        if(ui->wadsOnFolder->count()>=3)
        {
            settings.setValue("pwad3",ui->wadsOnFolder->item(2)->text());
            settings.setValue("pwad2",ui->wadsOnFolder->item(1)->text());
            settings.setValue("pwad1",ui->wadsOnFolder->item(0)->text());
        }
        else if(ui->wadsOnFolder->count()==2)
        {
            settings.setValue("pwad3","");
            settings.setValue("pwad2",ui->wadsOnFolder->item(1)->text());
            settings.setValue("pwad1",ui->wadsOnFolder->item(0)->text());
        }
        else if(ui->wadsOnFolder->count()==1)
        {
            settings.setValue("pwad3","");
            settings.setValue("pwad2","");
            settings.setValue("pwad1",ui->wadsOnFolder->item(0)->text());
        }
        else
        {
            settings.setValue("pwad3","");
            settings.setValue("pwad2","");
            settings.setValue("pwad1","");
        }

    }  catch (...) {
            // Safeguard to when you dont have 3 pwads loaded at the same time
    }


    /* You can load 3 types of files.
        *.wad -file
        *.deh -deh
        *.bex -deh
    */
    std::string dehFiles = "";
    std::string files = "";
    for(int item=0;item < ui->wadsOnFolder->count(); item++)
    {
        if(ui->wadsOnFolder->item(item)->text().toStdString().back()=='h')
        {
            dehFiles += " \"" + ui->wadsOnFolder->item(item)->text().toStdString()+"\" ";
        }
        else
        {
            files += " \"" + ui->wadsOnFolder->item(item)->text().toStdString()+"\" ";
        }
    }
    if(dehFiles!="")
    {
        if(getOsName()=="Windows")
        {
            for(int i=0; i<dehFiles.length();i++)
            {
                if(dehFiles[i]=='/')
                    dehFiles[i]='\\';
            }
        }
        arguments+= " -deh "+ dehFiles;
    }
    if(files!="")
    {
        if(getOsName()=="Windows")
        {
            for(int i=0; i<files.length();i++)
            {
                if(files[i]=='/')
                    files[i]='\\';
            }
        }
        arguments+= " -file "+ files;
    }


    // Again, these are the parameters available on toggles
    settings.setValue("fast",false);
    settings.setValue("nomo",false);
    settings.setValue("respawn",false);
    settings.setValue("solonet",false);
    if(isFast)
    {
        arguments += " "+fastParam+" ";
        settings.setValue("fast",true);
    }
    if(noMo)
    {
        arguments += " "+nomoParam+" ";
        settings.setValue("nomo",true);
    }
    if(isRespawn)
    {
        arguments += " "+respawnParam+" ";
        settings.setValue("respawn",true);
    }
    if(isSoloNet)
    {
        arguments += " "+solonetParam+" ";
        settings.setValue("solonet",true);
    }

    if(bottomRow==1)
    {
        settings.setValue("fullscreen",false);
        settings.setValue("geom",ui->comboBox_2->currentIndex());
        if(isFulscreen!="w")
        {
            settings.setValue("fullscreen",true);
        }
        if(ui->comboBox_2->currentIndex()==0)
        {
            if(isFulscreen=="w")
            {
                arguments += " -nofullscreen ";
            }
            else
            {
                arguments += " -fullscreen ";
            }
        }
        else
        {
            arguments += " -geom "+ ui->comboBox_2->currentText().toStdString()+isFulscreen;
        }
    }
    else if(bottomRow==2)
    {
        if(ui->timeKeysBox->currentIndex()==ui->timeKeysBox->count()-1 && ui->timeKeysBox->count()>1)
        {
            if(lowerCase(ui->timeKeysBox->currentText().toStdString())==" all"||lowerCase(ui->timeKeysBox->currentText().toStdString())==" both")
            {
                for(int i=(ui->timeKeysBox->count()-2);i>0;i--)
                {
                    arguments += " "+ui->timeKeysBox->itemText(i).toStdString()+" ";
                }
            }
            else
            {
                arguments += " "+ui->timeKeysBox->currentText().toStdString()+" ";
            }
        }
        else
        {
            arguments += " "+ui->timeKeysBox->currentText().toStdString()+" ";
        }
        settings.setValue("timeKeys", ui->timeKeysBox->currentIndex());

        if(ui->levelstatBox->currentIndex()==ui->levelstatBox->count()-1 && ui->levelstatBox->count()>1)
        {
            if(lowerCase(ui->levelstatBox->currentText().toStdString())==" all"||lowerCase(ui->levelstatBox->currentText().toStdString())==" both")
            {
                for(int i=(ui->levelstatBox->count()-2);i>0;i--)
                {
                    arguments += " "+ui->levelstatBox->itemText(i).toStdString()+" ";
                }
            }
            else
            {
                arguments += " "+ui->levelstatBox->currentText().toStdString()+" ";
            }
        }
        else
        {
            arguments += " "+ui->levelstatBox->currentText().toStdString()+" ";
        }
        settings.setValue("levelstat", ui->levelstatBox->currentIndex());
    }


    if(ui->recordDemo->text().size()>5)
    {
        arguments += " -record \""+ui->recordDemo->text().toStdString()+"\" ";
    }

    if(ui->recordDemo_2->text().size()>5)
    {
        if(ui->demoPlayOptions->currentIndex()==0)
        {
            arguments += " -playdemo \""+ui->recordDemo_2->text().toStdString()+"\" "; // Plays demo at normal speed
        }
        else if(ui->demoPlayOptions->currentIndex()==1)
        {
            arguments += " -timedemo \""+ui->recordDemo_2->text().toStdString()+"\" "; // Used for viddumping
        }
        else if(ui->demoPlayOptions->currentIndex()==2)
        {
            arguments += " -fastdemo \""+ui->recordDemo_2->text().toStdString()+"\" "; // Used for benchmarks
        }
    }

    // Again, we need to remove the setting if the additional parameters box is empty so that it does not appear when we open the launcher again
    if(ui->argumentText->toPlainText().toStdString()!="")
    {
        settings.setValue("argumentText",ui->argumentText->toPlainText().toStdString().c_str());
    }
    else
    {
        settings.remove("argumentText");
    }

    // Before, it was possible to hit ENTER on the additional parameters box, so we needed to change it to SPACE
    // I'll comment that out for future reference
    arguments += " " + ui->argumentText->toPlainText().toStdString() + " ";
    // std::replace(arguments.begin(), arguments.end(), '\n', ' ');

    settings.setValue("iwad",ui->iwadSelect->currentIndex());

    qDebug() << arguments.c_str();

    // All settings were saved, if the app is quiting, then exit this function
    if(onExit)
        return;

    if(returnTooltip)
    {
        ui->LaunchGameButton->setToolTip("dsda-doom -iwad "+ui->iwadSelect->currentText()+".wad "+arguments.c_str());
        arguments=" ";
        return;
    }

    if(getOsName()=="MacOS") // Tested
    {
        std::string homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
        std::string execPath = QCoreApplication::applicationDirPath().toStdString();
        system(("cd ~/ && " + execPath+"/../Resources/dsda-doom -iwad "+homePath+"/.dsda-doom/"+ui->iwadSelect->currentText().toStdString()+".wad "+arguments+" >> "+homePath+"/.dsda-doom/LogFile.txt &").c_str());
        arguments=" ";
    }
    else if(getOsName()=="Linux") // Havent tested this yet. Sure hope it works
    {
        std::string homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
        std::string execPath = QCoreApplication::applicationDirPath().toStdString();
        system(("rm "+homePath+"/.dsda-doom/LogFile.txt").c_str());

        system(("cd ~/ && " +execPath+ "/dsda-doom -iwad "+ui->iwadSelect->currentText().toStdString()+".wad "+arguments+" >> "+homePath+"/.dsda-doom/LogFile.txt &").c_str());
        arguments=" ";
    }

//I could not do getOsName()=="Windows" here, because it would give me errors when compiling to non Windows machines

#ifdef _WIN32
        std::string execPath = QCoreApplication::applicationDirPath().toStdString();
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
#endif

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
    if(sel=="doom"||sel=="doomu"||sel=="doom1"||sel=="freedoom1"||sel=="freedoom"||sel=="bfgdoom1"||sel=="bfgdoom"||sel=="heretic"||sel=="chex"||sel=="hacx")
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

    // Reload the DSDA leaderboards only if the active tab is the DSDA one
    if(ui->tabs->currentIndex()==3)
    {
        reloadLeaderboard();
    }

}

// Show the LogFile.txt
void MainWindow::on_pushButton_clicked()
{
    if(getOsName()=="MacOS" || getOsName()=="Linux")
    {
        std::string homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
        system(("open "+homePath+"/.dsda-doom/LogFile.txt >> "+homePath+"/.dsda-doom/LogFile.txt").c_str());
    }
    else
    {
        std::string logPath = "\"" + QCoreApplication::applicationDirPath().toStdString() + "\\LogFile.txt\"";
        for(int i=0; i<logPath.length();i++)
        {
            if(logPath[i]=='/')
                logPath[i]='\\';
        }
        qDebug() << logPath.c_str();
        QProcess::startDetached(("notepad.exe " + logPath).c_str());
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
void MainWindow::on_toolButton_toggled(bool checked)
{
    if(checked)
        ui->toolTip->show();
    else
        ui->toolTip->hide();
}

void MainWindow::on_tabs_currentChanged(int index)
{
    if(index==0)
    {
        if(bottomRow!=2)
            ui->comboBox_2->show();
    }
    else
    {
        ui->comboBox_2->hide();
    }

    if(index==2)
    {
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->demoPlayOptions->show();
    }
    else
    {
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        ui->demoPlayOptions->hide();
    }

    if(index==3) // Reload the DSDA leaderboards only if the active tab is the DSDA one
    {
        reloadLeaderboard();
    }
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
    qDebug() << QString(("https://dsdarchive.com/api/demos/records?wad="+wad+"&level="+level+"&category="+category).c_str());

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
            qDebug() << "Key = " << key << ", Value = " << value.toString();
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
    reloadLeaderboard();
}

bool reloadingLeaderboards=false;

void MainWindow::reloadLeaderboard()
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



    if(ui->wadsOnFolder->count()<1)
    {
        wad = ui->iwadSelect->currentText().toStdString();
        for (int i = 0; i < wad.length(); i++)
            {
                wad[i] = tolower(wad[i]);
            }
        if(wad=="doomu"||wad=="doom1")
        {
            wad="doom";
        }
    }
    else
    {
        std::string wad1 = ui->wadsOnFolder->item(0)->text().toStdString();
        for (int i = 0; i < wad1.length(); i++)
            {
                wad1[i] = tolower(wad1[i]);
            }
        wad=wad1;
        for (int i = 0; i < wad1.length(); i++)
        {
            if(wad1[i]=='/')
            {
                wad = wad1.substr(i+1);
                wad.resize(wad.length()-4);
            }
        }
    }

    if(ui->levelBox->text().toStdString()!= "" && !ui->levelBox->isHidden())
    {
        level = "E"+ui->episodeBox->text().toStdString()+"M"+ui->levelBox->text().toStdString();
    }
    else if(ui->episodeBox->text().toStdString()!= "" && ui->levelBox->isHidden())
    {
        if(ui->episodeBox->text().toStdString().length()==1)
        {
            level = "Map 0"+ui->episodeBox->text().toStdString();
        }
        else
        {
            level = "Map "+ui->episodeBox->text().toStdString();
        }

    }
    else if(!ui->levelBox->isHidden())
    {
        level = "E1M1";
    }
    else
    {
        level = "Map 01";
    }

    ui->wadLName->setText(wad.c_str());
    ui->levelL->setText(level.c_str());

    for (int i = 0; i < int(level.length()); i++)
        {
            if(level[i]==' ')
            {
                level.erase(i);
                level.insert(i,"%20");
                if(ui->episodeBox->text().toStdString().length()>1)
                {
                    level.append(ui->episodeBox->text().toStdString());
                }
                else if(ui->episodeBox->text().toStdString().length()==1)
                {
                    level.append("0" + ui->episodeBox->text().toStdString());
                }
                else
                {
                    level.append("01");
                }
            }
        }
    qDebug() << (wad +" "+ level +" "+ category).c_str();

    reloadingLeaderboards=false;
    get_leaderboards(wad,level,category);

}

void MainWindow::on_toolButton_4_clicked() // Download the demo file of a run
{
    QString link = demoFile;
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_episodeBox_textChanged(const QString &arg1)
{
    if(ui->tabs->currentIndex()==3 && arg1.toStdString().length()>0)
    {
        // Prevents crashes
        QFuture<void> future = QtConcurrent::run([=]() {
            reloadLeaderboard();
        });
    }
}

void MainWindow::on_levelBox_textChanged(const QString &arg1)
{
    if(ui->tabs->currentIndex()==3 && arg1.toStdString().length()>0)
    {
        // Prevents crashes
        QFuture<void> future = QtConcurrent::run([=]() {
            reloadLeaderboard();
        });
    }
}

void MainWindow::on_editParameters_clicked() // Customise the launcher
{
    if(getOsName()=="MacOS"||getOsName()=="Linux")
    {
        system(("open "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom/launcher_config.txt").c_str());
    }
    else
    {
        system("start launcher_config.txt");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) // ENTER makes the game start
{
    if(event->key()==0x01000005 || event->key()==0x01000004) // Key is either ENTER or RETURN
    {
        on_LaunchGameButton_clicked(false, false);
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *ev) // ENTER does not work on the additional parameters box
{

      if (object == (QObject*)ui->LaunchGameButton) {
            if (ev->type() == QEvent::Enter)
            {
                on_LaunchGameButton_clicked(false, true);
                return QWidget::eventFilter(object, ev);
            }
            if(ev->type() == QEvent::MouseButtonPress)
            {
                on_LaunchGameButton_clicked(false, false);
                return QWidget::eventFilter(object, ev);
            }
      }
      if (ev->type() == QEvent::KeyPress)
      {
           QKeyEvent* keyEvent = (QKeyEvent*)ev;

           if (keyEvent->key() == 0x01000005 || keyEvent->key() == 0x01000004) // Key is either ENTER or RETURN
           {
                on_LaunchGameButton_clicked(false, false);
                return true;
           }
    }
      return false;
}

void MainWindow::closeEvent(QCloseEvent *event) // When closing the launcher, save the settings
{
    on_LaunchGameButton_clicked(true, false);
}


