#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QStyleFactory>
#include <QSplashScreen>
#include <QTimer>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    // Settings to be stored
    QSettings settings("pedrobeirao","dsda-launcher");

    QApplication a(argc, argv);

    MainWindow w;
    w.ensurePolished();
    w.show();

    if(settings.value("version").toString()!=version)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("dsda-launcher " + version);
        msgBox.setText("It is recommended that you use dsda-doom v0.25 or later");
        msgBox.setInformativeText("Here are a few tips you should know:\n\n- Drag .wad / .deh files on top of the launcher to add them to the loaded files\n\n- Drag .lmp files on top of the launcher to play the demo and autoselect the correct IWAD, PWADs and complevel\n\n- For the mentioned autoselect to work correctly, go to the settings and set the PWADs folders");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    a.setQuitOnLastWindowClosed(false);
    return a.exec();
}
