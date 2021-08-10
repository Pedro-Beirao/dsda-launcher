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
#include "documentation.h"
#include "defaultfolders.h"
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QRegularExpression>

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

QStringList images;

QSettings settings("pedrobeirao","dsda-launcher");

documentation *docWindow;
DefaultFolders *wadWindow;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    docWindow = new documentation;
    wadWindow = new DefaultFolders;

    QRegularExpression rgx("[0-9]{2}");
    QValidator *comValidator = new QRegularExpressionValidator (rgx, this);
    ui->episodeBox->setValidator(comValidator);
    ui->levelBox->setValidator(comValidator);

    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_O | Qt::CTRL),this,SLOT(foo()));
    shortcut->setAutoRepeat(false);

    QShortcut * shortcut2 = new QShortcut(QKeySequence(Qt::Key_N | Qt::CTRL),this,SLOT(foo2()));
    shortcut2->setAutoRepeat(false);

    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(foo3()));
    shortcut3->setAutoRepeat(false);

    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->demoPlayOptions->hide();

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

        ui->pushButton_2->setStyleSheet("color: rgb(50, 50, 50);");
    }

    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="doom" || filename=="DOOM")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="doom1" || filename=="DOOM1")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="doomu"|| filename=="DOOMU")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="doom2"|| filename=="DOOM2")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="doom2f"|| filename=="DOOM2f"|| filename=="DOOM2F")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="tnt"|| filename=="TNT")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="plutonia"|| filename=="PLUTONIA"|| filename=="Plutonia")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="freedoom1"|| filename=="FREEDOOM1"|| filename=="freedoom"|| filename=="FreeDoom1"|| filename=="FreeDoom"|| filename=="Freedoom1"|| filename=="Freedoom")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="freedoom2"|| filename=="FREEDOOM2"|| filename=="FreeDoom2"|| filename=="Freedoom2")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="heretic"|| filename=="HERETIC"|| filename=="Heretic")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="bfgdoom1"|| filename=="BFGDOOM1"|| filename=="bfgDOOM1"|| filename=="BfgDoom1"|| filename=="BFGdoom1")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="bfgdoom2"|| filename=="BFGDOOM2"|| filename=="bfgDOOM2"|| filename=="BfgDoom2"|| filename=="BFGdoom2")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="chex"||filename=="CHEX"||filename=="Chex")
        {
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        filename.resize (filename.size () - 4);
        if(filename=="hacx"||filename=="HACX"||filename=="Hacx")
        {
            ui->iwadSelect->addItems({filename});
        }
    }

    if(ui->iwadSelect->count()==0)
    {
        ui->toolTip->show();
    }
    else
    {
        ui->toolTip->hide();
    }


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

    ui->argumentText->appendPlainText(settings.value("argumentText").toString());
}


void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        if(fileName.toStdString().back()=='p')
        {
            ui->tabs->setCurrentIndex(2);
            ui->recordDemo_2->setText(fileName);
            std::ifstream file;
                file.open(fileName.toStdString());
                // Make sure the file opened properly

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
                        qDebug()<<line.c_str();
                        std::vector< int > aspas;
                        for(unsigned charIndex =0;charIndex<=line.length();charIndex++)
                        {
                            if(line[charIndex]=='"')
                            {
                                aspas.push_back(charIndex);
                            }
                        }
                        qDebug()<<aspas;
                        std::string iwadFile = line.substr(aspas[0]+1,aspas[1]-aspas[0]-1);
                        qDebug()<<iwadFile.c_str();
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
                        qDebug()<<iwadFile.c_str();
                    }

                }

        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::foo()
{
    if(getOsName()=="MacOS"|| getOsName()=="Linux")
    {
        system(("open "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom").c_str());
    }
    else
    {
        system(("open "+QCoreApplication::applicationDirPath().toStdString()).c_str());
    }
}

void MainWindow::foo2()
{
    MainWindow *newMainWindow = new MainWindow;
    newMainWindow->show();
}

void MainWindow::foo3()
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

void MainWindow::addWads(QStringList fileNames)
{
    ui->wadsOnFolder->addItems(fileNames);
}


std::string arguments = " ";
bool isFast=false;
bool noMo =false;
bool isRespawn=false;
std::string isFulscreen="w";
bool isSoloNet = false;


void MainWindow::on_LaunchGameButton_clicked()
{

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

    int diffIndex = ui->diffBox->currentIndex();
    settings.setValue("skill",diffIndex);
    if(ui->episodeBox->text().length()>0)
    {
        if(diffIndex==1)
        {
            arguments+=" -skill 1 ";
        }
        else if(diffIndex==2)
        {
            arguments+=" -skill 2 ";
        }
        else if(diffIndex==3)
        {
            arguments+=" -skill 3 ";
        }
        else if(diffIndex==4)
        {
            arguments+=" -skill 4 ";
        }
        else if(diffIndex==5)
        {
            arguments+=" -skill 5 ";
        }
    }



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

    if(ui->episodeBox->text().toStdString()=="")
    {
        settings.remove("warp1");
    }
    if(ui->levelBox->text().toStdString()=="")
    {
        settings.remove("warp2");
    }

    qDebug() <<  ui->wadsOnFolder->count();

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

    }

    std::string dehFiles = "";
    std::string files = "";

    for(int item=0;item < ui->wadsOnFolder->count(); item++)
    {
        if(ui->wadsOnFolder->item(item)->text().toStdString().back()=='h')
        {
            dehFiles += " '" + ui->wadsOnFolder->item(item)->text().toStdString()+"' ";
        }
        else
        {
            files += " '" + ui->wadsOnFolder->item(item)->text().toStdString()+"' ";
        }
    }
    arguments += " -deh "+ dehFiles +" -file "+ files;



    settings.setValue("fast",false);
    settings.setValue("nomo",false);
    settings.setValue("respawn",false);
    if(isFast)
    {
        arguments += " -fast ";
        settings.setValue("fast",true);
    }
    if(noMo)
    {
        arguments += " -nomonsters ";
        settings.setValue("nomo",true);
    }
    if(isRespawn)
    {
        arguments += " -respawn ";
        settings.setValue("respawn",true);
    }

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
    settings.setValue("solonet",false);
    if(isSoloNet)
    {
        arguments += " -solo-net";
        settings.setValue("solonet",true);
    }
    if(ui->recordDemo->text().size()>5)
    {
        arguments += " -record "+ui->recordDemo->text().toStdString();
    }
    if(ui->recordDemo_2->text().size()>5)
    {
        if(ui->demoPlayOptions->currentIndex()==0)
        {
            arguments += " -playdemo "+ui->recordDemo_2->text().toStdString();
        }
        else if(ui->demoPlayOptions->currentIndex()==1)
        {
            arguments += " -timedemo "+ui->recordDemo_2->text().toStdString();
        }
        else if(ui->demoPlayOptions->currentIndex()==2)
        {
            arguments += " -fastdemo "+ui->recordDemo_2->text().toStdString();
        }
    }

    if(ui->argumentText->toPlainText().toStdString()!="")
    {
        settings.setValue("argumentText",ui->argumentText->toPlainText().toStdString().c_str());
    }
    else
    {
        settings.remove("argumentText");
    }


    arguments += " " + ui->argumentText->toPlainText().toStdString() + " ";
    std::replace(arguments.begin(), arguments.end(), '\n', ' ');

    settings.setValue("iwad",ui->iwadSelect->currentIndex());


    if(getOsName()=="MacOS")
    {
        std::string homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
        std::string execPath = QCoreApplication::applicationDirPath().toStdString();
        system(("rm "+homePath+"/.dsda-doom/LogFile.txt").c_str());
        qDebug() << system("ls");
        qDebug() << system("pwd");
        qDebug() << (execPath+"/../Resources/dsda-doom -iwad "+homePath+"/.dsda-doom/"+ui->iwadSelect->currentText().toStdString()+".wad "+arguments+" >> "+homePath+"/.dsda-doom/LogFile.txt").c_str();
        system(("cd ~/ && " + execPath+"/../Resources/dsda-doom -iwad "+homePath+"/.dsda-doom/"+ui->iwadSelect->currentText().toStdString()+".wad "+arguments+" >> "+homePath+"/.dsda-doom/LogFile.txt &").c_str());
        arguments=" ";
    }
    else if(getOsName()=="Linux")
    {
        std::string homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
        std::string execPath = QCoreApplication::applicationDirPath().toStdString();
        system(("rm "+homePath+"/.dsda-doom/LogFile.txt").c_str());

        system((execPath+ "/dsda-doom -iwad "+ui->iwadSelect->currentText().toStdString()+".wad "+arguments+" >> "+homePath+"/.dsda-doom/LogFile.txt &").c_str());
        arguments=" ";
    }
    else
    {
        std::string execPath = QCoreApplication::applicationDirPath().toStdString();
        system(("cmd /c "+execPath+ "\\dsda-doom -iwad "+ui->iwadSelect->currentText().toStdString()+".wad "+arguments+" >> LogFile.txt &").c_str());
        arguments=" ";
    }


}



void MainWindow::on_iwadSelect_currentIndexChanged(int index)
{
    std::string sel = (ui->iwadSelect->currentText()).toStdString();
    for (int i = 0; i < int(sel.length()); i++)
        {
            sel[i] = tolower(sel[i]);
        }
    if(sel=="doom"||sel=="DOOM"||sel=="doomu"||sel=="DOOMU"||sel=="doom1"||sel=="DOOM1"||sel=="freedoom1"||sel=="freedoom"||sel=="bfgdoom1"||sel=="bfgdoom"||sel=="heretic"||sel=="HERETIC"||sel=="chex"||sel=="hacx")
    {
        ui->levelBox->show();
        ui->levelText->show();
        ui->episodeText->setText("Episode");
    }
    else
    {
        ui->levelBox->hide();
        ui->levelText->hide();
        ui->episodeText->setText("Level");
    }

    if(ui->tabs->currentIndex()==3)
    {
        reloadLeaderboard();
    }

}


void MainWindow::on_pushButton_clicked()
{
    if(getOsName()=="MacOS" || getOsName()=="Linux")
    {
        std::string homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
        system(("open "+homePath+"/.dsda-doom/LogFile.txt >> "+homePath+"/.dsda-doom/LogFile.txt").c_str());
    }
    else
    {
        system("start LogFile.txt >> LogFile.txt");
    }
}

void MainWindow::on_plus_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select WAD file"),settings.value("primaryPWADFolder").toString(),tr("WAD files (*.wad *.deh *.bex)"));
    ui->wadsOnFolder->addItems(fileNames);
    if(fileNames.length()>0)
    {
        settings.setValue("primaryPWADFolder", fileNames[0]);
    }
}


void MainWindow::on_minus_clicked()
{
    ui->wadsOnFolder->takeItem(ui->wadsOnFolder->currentRow());
}




void MainWindow::on_fastCheck_toggled(bool checked)
{
    if(checked)
    {
        isFast=true;
    }
    else
    {
        isFast=false;
    }
}


void MainWindow::on_noCheck_toggled(bool checked)
{
    if(checked)
    {
        noMo=true;
    }
    else
    {
        noMo=false;
    }
}


void MainWindow::on_toolButton_toggled(bool checked)
{
    if(checked)
    {
        ui->toolTip->show();
    }
    else
    {
        ui->toolTip->hide();
    }
}


void MainWindow::on_noCheck_4_toggled(bool checked)
{
    if(checked)
    {
        isRespawn=true;
    }
    else
    {
        isRespawn=false;
    }
}


void MainWindow::on_noCheck_3_toggled(bool checked)
{
    if(checked)
    {
        isFulscreen="f";
    }
    else
    {
        isFulscreen="w";
    }
}


void MainWindow::on_soloNetCheck_toggled(bool checked)
{
    if(checked)
    {
        isSoloNet=true;
    }
    else
    {
        isSoloNet=false;
    }
}


void MainWindow::on_tabs_currentChanged(int index)
{
    if(index==0)
    {
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

    if(index==3)
    {
        reloadLeaderboard();
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    QString demoName = QFileDialog::getSaveFileName(this, tr("Demo file"),QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString().c_str(),tr("lmp files (*.lmp)"));
    ui->recordDemo->setText(demoName);
}


void MainWindow::on_pushButton_3_clicked()
{
    QString demoName = QFileDialog::getOpenFileName(this, tr("Demo file"),QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).toStdString().c_str(),tr("lmp files (*.lmp)"));
    ui->recordDemo_2->setText(demoName);
}


void MainWindow::on_toolButton_3_clicked()
{
    docWindow->show();
}

QString demoFile;

void MainWindow::get_leaderboards(std::string wad, std::string level, std::string category)
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






void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    reloadLeaderboard();
}



bool reloadingLeaderboards=false;

void MainWindow::reloadLeaderboard()
{

    reloadingLeaderboards=true;
    std::string arg1 = ui->comboBox->currentText().toStdString();
    std::string category;

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

#include <QDesktopServices>
#include <QtConcurrent>

void MainWindow::on_toolButton_4_clicked()
{
    QString link = demoFile;
    QDesktopServices::openUrl(QUrl(link));
}


void MainWindow::on_episodeBox_textChanged(const QString &arg1)
{
    if(ui->tabs->currentIndex()==3 && arg1.toStdString().length()>0)
    {
        QFuture<void> future = QtConcurrent::run([=]() {
            reloadLeaderboard();
        });
    }
}


void MainWindow::on_levelBox_textChanged(const QString &arg1)
{
    if(ui->tabs->currentIndex()==3 && arg1.toStdString().length()>0)
    {
        QFuture<void> future = QtConcurrent::run([=]() {
            reloadLeaderboard();
        });
    }
}

void MainWindow::on_toolButton_2_clicked()
{
    wadWindow->show();
}

void MainWindow::changePrimaryPWADFolder(QString arg1)
{
    settings.setValue("primaryPWADFolder", arg1);
}
