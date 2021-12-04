#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <qsettings.h>
#include <mainwindow.h>
#include "Mac.h"
#include <qshortcut.h>
#include <qstandardpaths.h>

// Find the name of the OS
std::string getOsNameS()
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

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->restartWarning->hide();

    if(settings.value("theme")=="light")
    {
        ui->checkBox->setChecked(false);
        on_checkBox_clicked(false);
    }
    else
    {
        ui->checkBox->setChecked(true);
        on_checkBox_clicked(true);
    }

    // Keyboard shortcuts
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS
    // Open the folder to add the IWADs
    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_O | Qt::CTRL),this,SLOT(fooo()));
    shortcut->setAutoRepeat(false);

    // Closes the active window
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);
}

void Settings::fooo() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
    if(getOsNameS()=="MacOS"|| getOsNameS()=="Linux")
    {
        system(("open \""+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom\"").c_str());
    }
    else
    {
        system(("explorer \""+QCoreApplication::applicationDirPath().toStdString() + "\"").c_str());
    }
}

void Settings::fooo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

Settings::~Settings()
{
    delete ui;
}

/*
void Settings::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit->setStyleSheet("color: rgb(139, 139, 139);");
    }
    else
    {
        ui->lineEdit->setReadOnly(false);
        ui->lineEdit->setStyleSheet("");
    }
}


void Settings::on_pushButton_clicked()
{
    if(!ui->checkBox->isChecked())
    {
        QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Select the IWADs folder path"),"/",tr("Folder (*.wad)"));
        if(fileName.size()>0)
        {
            std::string iwadPath = fileName[0].toStdString();
            std::size_t found = iwadPath.find_last_of("/\\");
            ui->lineEdit->setText(iwadPath.substr(0,found).c_str());
        }
    }
}
*/

void Settings::on_pushButton_2_clicked()
{
    //settings.setValue("iwadspath",getIWADsPath());

    ui->restartWarning->show();
}




void Settings::on_checkBox_clicked(bool checked)
{
    if(!checked)
    {
        #ifdef __APPLE__ || __MACH__
        macSetToLightTheme();
        #else
        QFile f( "lstyle.qss" );
        if ( !f.exists() )
        {
           qWarning() << "Unable to set dark stylesheet, file not found";
        }
        else
        {
           f.open( QFile::ReadOnly | QFile::Text );
           QTextStream ts( &f );
           qApp->setStyleSheet( ts.readAll() );
        }
        #endif
        settings.setValue("theme","light");
    }
    else
     {
        #ifdef __APPLE__ || __MACH__
        macSetToDarkTheme();
        #else
        QFile f( "dstyle.qss" );
        if ( !f.exists() )
        {
           qWarning() << "Unable to set dark stylesheet, file not found";
        }
        else
        {
           f.open( QFile::ReadOnly | QFile::Text );
           QTextStream ts( &f );
           qApp->setStyleSheet( ts.readAll() );
        }
        #endif
        settings.setValue("theme","dark");
    }
}


void Settings::on_toolButton_2_clicked()
{
    QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Select a PWAD folder path"),"/",tr("Folder (*.wad)"));
    if(fileName.size()>0)
    {/*
        std::string iwadPath = fileName[0].toStdString();
        std::size_t found = iwadPath.find_last_of("/\\");
        ui->lineEdit->setText(iwadPath.substr(0,found).c_str());
    */}
}

