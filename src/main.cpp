#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QSplashScreen>
#include <QStyleFactory>
#include <QTimer>
#include "theme.h"

extern QSettings *settings;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Settings to be stored
#if defined Q_OS_WIN
    settings = new QSettings(QCoreApplication::applicationDirPath() + "/" + APP_NAME + ".ini", QSettings::IniFormat);

    // Check for previous registry settings and copy it to the new one if needed
    if (settings->value("version").toString()=="")
    {
        QSettings prev_reg_settings("pedrobeirao", APP_NAME); // Legacy path
        Q_FOREACH(QString key, prev_reg_settings.allKeys())
        {
            settings->setValue(key, prev_reg_settings.value(key));
        }
    }
#else
    settings = new QSettings("pedrobeirao", APP_NAME);
#endif

    MainWindow w;
    w.ensurePolished();
    w.show();

    setWindowTitleBar(w.winId()); // This should be called after every window.show()

    a.setQuitOnLastWindowClosed(false);
    return a.exec();
}
