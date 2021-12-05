#include "quickargs.h"
#include "ui_quickargs.h"
#include "mainwindow.h"
#include <QShortcut>
#include <QStandardPaths>
#include <QProcess>

// Find the name of the OS
std::string getOsNameQ()
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

quickargs::quickargs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quickargs)
{
    ui->setupUi(this);

    // Keyboard shortcuts
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS
    // Open the folder to add the IWADs
    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_O | Qt::CTRL),this,SLOT(foooo()));
    shortcut->setAutoRepeat(false);

    // Closes the active window
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(foooo3()));
    shortcut3->setAutoRepeat(false);

}

quickargs::~quickargs()
{
    delete ui;
}

void quickargs::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->text(0)!="Custom" && item->childCount()==0)
    {
        MainWindow * mw = MainWindow::getMainWin();
        mw->addToArguments(item->text(0));
        this->hide();
    }
}

void quickargs::foooo() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
    if(getOsNameQ()=="MacOS"|| getOsNameQ()=="Linux")
    {
        system(("open \""+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom\"").c_str());
    }
    else
    {
        QProcess::startDetached(("explorer \""+QCoreApplication::applicationDirPath().toStdString() + "\"").c_str());
    }
}

void quickargs::foooo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

