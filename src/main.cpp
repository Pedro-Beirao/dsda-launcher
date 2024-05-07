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

extern QSettings *settings;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Settings to be stored
#ifdef Q_OS_WIN
    settings = new QSettings(QCoreApplication::applicationDirPath() + "/dsda-launcher.ini", QSettings::IniFormat);

    // Check for previous registry settings and copy it to the new one if needed
    if (settings->value("version").toString()=="")
    {
        QSettings prev_reg_settings("pedrobeirao", "dsda-launcher");
        Q_FOREACH(QString key, prev_reg_settings.allKeys())
        {
            settings->setValue(key, prev_reg_settings.value(key));
        }
    }
#else
    settings = new QSettings("pedrobeirao", "dsda-launcher");
#endif

    MainWindow w;
    w.ensurePolished();
    w.show();

    if(settings->value("version").toString()!=version)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("dsda-launcher " + version);
        msgBox.setText("It is recommended that you use dsda-doom v0.26 or later");
        msgBox.setInformativeText(
                    "Here are a few tips you should know:\n"
                    "\n"
                    "- Drag .wad / .deh files on top of the launcher to add them to the loaded files\n"
                    "\n"
                    "- Drag .lmp files on top of the launcher to play the demo and autoselect the correct IWAD, PWADs and complevel\n"
                    "\n"
                    "- For the mentioned autoselect to work correctly, go to the settings and set the PWADs folders");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    a.setQuitOnLastWindowClosed(false);
    return a.exec();
}
