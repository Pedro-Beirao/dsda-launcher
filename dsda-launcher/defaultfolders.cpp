#include "defaultfolders.h"
#include "ui_defaultfolders.h"
#include <QSettings>
#include "mainwindow.h"


DefaultFolders::DefaultFolders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DefaultFolders)
{
    ui->setupUi(this);
}

DefaultFolders::~DefaultFolders()
{
    delete ui;
}


void DefaultFolders::on_lineEdit_textChanged(const QString &arg1)
{
    MainWindow mainWindow;
    mainWindow.changePrimaryPWADFolder(arg1);
}

