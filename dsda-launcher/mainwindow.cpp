#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QStandardPaths>

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    if(getOsName()=="MacOS" || getOsName()=="Linux")
    {
        QDir directory(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom");
        images = directory.entryList(QStringList() << "*.wad",QDir::Files);
    }
    else
    {
        QDir directory = QDir::currentPath();
        images = directory.entryList(QStringList() << "*.wad",QDir::Files);
    }

    foreach(QString filename, images) {
        if(filename=="doom.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="doom1.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="doomu.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="doom2.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="doom2f.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="tnt.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="plutonia.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="freedoom1.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="freedoom2.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="heretic.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="bfgdoom1.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="bfgdoom2.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="chex.wad")
        {
            filename.resize (filename.size () - 4);
            ui->iwadSelect->addItems({filename});
        }
    }
    foreach(QString filename, images) {
        if(filename=="hacx.wad")
        {
            filename.resize (filename.size () - 4);
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

}


MainWindow::~MainWindow()
{
    delete ui;
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

    int complevelIndex = ui->compLevelSelect->currentIndex();
    if(complevelIndex==1)
    {
        arguments+=" -complevel 0 ";
    }
    else if(complevelIndex==2)
    {
        arguments+=" -complevel 1 ";
    }
    else if(complevelIndex==3)
    {
        arguments+=" -complevel 2 ";
    }
    else if(complevelIndex==4)
    {
        arguments+=" -complevel 3 ";
    }
    else if(complevelIndex==5)
    {
        arguments+=" -complevel 4 ";
    }
    else if(complevelIndex==6)
    {
        arguments+=" -complevel 5 ";
    }
    else if(complevelIndex==7)
    {
        arguments+=" -complevel 6 ";
    }
    else if(complevelIndex==8)
    {
        arguments+=" -complevel 7 ";
    }
    else if(complevelIndex==9)
    {
        arguments+=" -complevel 10 ";
    }
    else if(complevelIndex==10)
    {
        arguments+=" -complevel 11 ";
    }
    else if(complevelIndex==11)
    {
        arguments+=" -complevel 16 ";
    }
    else if(complevelIndex==12)
    {
        arguments+=" -complevel 17 ";
    }

    int diffIndex = ui->diffBox->currentIndex();
    if(diffIndex==1)
    {
        arguments+=" -skill 1 ";
    }
    if(diffIndex==2)
    {
        arguments+=" -skill 2 ";
    }
    if(diffIndex==3)
    {
        arguments+=" -skill 3 ";
    }
    if(diffIndex==4)
    {
        arguments+=" -skill 4 ";
    }
    if(diffIndex==5)
    {
        arguments+=" -skill 5 ";
    }



    if(ui->levelBox->text().toStdString()!= "" && !ui->levelBox->isHidden())
    {
        arguments += " -warp "+ui->episodeBox->text().toStdString()+" "+ui->levelBox->text().toStdString();
    }
    else if(ui->episodeBox->text().toStdString()!= "" && ui->levelBox->isHidden())
    {
        arguments += " -warp "+ui->episodeBox->text().toStdString();
    }

    for(int item=0; item++;item < ui->wadsOnFolder->count())
    {
        if(ui->wadsOnFolder->item(item)->text().toStdString().back()=='h')
        {
            arguments += " -deh '" + ui->wadsOnFolder->item(item)->text().toStdString()+"' ";
        }
        else
        {
            arguments += " -file '" + ui->wadsOnFolder->item(item)->text().toStdString()+"' ";
        }
    }

    if(isFast)
    {
        arguments += " -fast ";
    }
    if(noMo)
    {
        arguments += " -nomonsters ";
    }
    if(isRespawn)
    {
        arguments += " -respawn ";
    }

    if(ui->comboBox_2->currentIndex()==0)
    {
        arguments += " -w ";
    }
    else
    {
        arguments += " -geom "+ ui->comboBox_2->currentText().toStdString()+isFulscreen;
    }
    if(isSoloNet)
    {
        arguments += " -solo-net";
    }



    arguments += " " + ui->argumentText->toPlainText().toStdString();
    std::replace(arguments.begin(), arguments.end(), '\n', ' ');


    if(getOsName()=="MacOS" || getOsName()=="Linux")
    {
        std::string homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
        std::string execPath = QCoreApplication::applicationDirPath().toStdString();
        system((execPath+"/../Resources/dsda-doom -iwad "+homePath+"/.dsda-doom/"+ui->iwadSelect->currentText().toStdString()+".wad "+arguments+" >> "+homePath+"/.dsda-doom/LogFile.txt").c_str());
    }
    else
    {
        system(("dsda-doom -iwad "+ui->iwadSelect->currentText().toStdString()+".wad "+arguments+" >> LogFile.txt").c_str());
    }


}



void MainWindow::on_iwadSelect_currentIndexChanged(int index)
{
    QString sel = ui->iwadSelect->currentText();
    if(sel=="doom"||sel=="doomu"||sel=="doom1"||sel=="freedoom1"||sel=="bfgdoom1"||sel=="heretic")
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
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select WAD file"),"",tr("WAD files (*.wad *.deh)"));
    ui->wadsOnFolder->addItems(fileNames);
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
        ui->comboBox->show();
    }
    else
    {
        ui->comboBox->hide();
    }
}

