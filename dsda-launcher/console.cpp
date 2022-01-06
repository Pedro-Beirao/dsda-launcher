#include "console.h"
#include "ui_console.h"
#include <QShortcut>
#include <QStandardPaths>
#include <QProcess>

// Find the name of the OS
std::string getOsNameC()
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

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);

    // Keyboard shortcuts
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS
    // Open the folder to add the IWADs
    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_O | Qt::CTRL),this,SLOT(fooo()));
    shortcut->setAutoRepeat(false);

    // Closes the active window
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);
}

Console::~Console()
{
    delete ui;
}

void Console::changeText(std::string s)
{
    QString previousText = ui->text->toPlainText();
    ui->text->setPlainText(previousText + s.c_str());
}

void Console::clearText()
{
    ui->text->setPlainText("");
}

void Console::fooo() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
    if(getOsNameC()=="MacOS"|| getOsNameC()=="Linux")
    {
        system(("open \""+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom\"").c_str());
    }
    else
    {
        QProcess::startDetached(("explorer \""+QCoreApplication::applicationDirPath().toStdString() + "\"").c_str());
    }
}

void Console::fooo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}
