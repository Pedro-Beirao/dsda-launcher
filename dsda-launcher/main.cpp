#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QStyleFactory>
#include <QSplashScreen>
#include <QTimer>
#include <QDebug>


int main(int argc, char *argv[])
{
    #ifdef LINUX
    std::string os = "Linux";
    #else
    #ifdef WIN32
    std::string os = "Windows";
    #else
    std::string os = "Mac OSX";
    #endif
    #endif



    if(os=="Linux" || os=="Windows")
    {
       // QApplication::setStyle("Fusion");
        qApp->setStyle(QStyleFactory::create("Fusion"));

            QPalette darkPalette;
            darkPalette.setColor(QPalette::Window, QColor(53,53,53));
            darkPalette.setColor(QPalette::WindowText, Qt::white);
            darkPalette.setColor(QPalette::Base, QColor(25,25,25));
            darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
            darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
            darkPalette.setColor(QPalette::ToolTipText, Qt::white);
            darkPalette.setColor(QPalette::Text, Qt::white);
            darkPalette.setColor(QPalette::Button, QColor(53,53,53));
            darkPalette.setColor(QPalette::ButtonText, Qt::white);
            darkPalette.setColor(QPalette::BrightText, Qt::red);
            darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

            darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::HighlightedText, Qt::black);
            /*
            qApp->setStyle(QStyleFactory::create("Fusion"));

            QPalette newPalette;
            newPalette.setColor(QPalette::Window,          QColor( 37,  37,  37));
            newPalette.setColor(QPalette::WindowText,      QColor(212, 212, 212));
            newPalette.setColor(QPalette::Base,            QColor( 60,  60,  60));
            newPalette.setColor(QPalette::AlternateBase,   QColor( 45,  45,  45));
            newPalette.setColor(QPalette::PlaceholderText, QColor(127, 127, 127));
            newPalette.setColor(QPalette::Text,            QColor(212, 212, 212));
            newPalette.setColor(QPalette::Button,          QColor( 45,  45,  45));
            newPalette.setColor(QPalette::ButtonText,      QColor(212, 212, 212));
            newPalette.setColor(QPalette::BrightText,      QColor(240, 240, 240));
            newPalette.setColor(QPalette::Highlight,       QColor( 38,  79, 120));
            newPalette.setColor(QPalette::HighlightedText, QColor(240, 240, 240));

            newPalette.setColor(QPalette::Light,           QColor( 60,  60,  60));
            newPalette.setColor(QPalette::Midlight,        QColor( 52,  52,  52));
            newPalette.setColor(QPalette::Dark,            QColor( 30,  30,  30) );
            newPalette.setColor(QPalette::Mid,             QColor( 37,  37,  37));
            newPalette.setColor(QPalette::Shadow,          QColor( 0,    0,   0));

            newPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));

            qApp->setPalette(newPalette);
            */

            qApp->setPalette(darkPalette);

            qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    }


    QApplication a(argc, argv);

    MainWindow w;
    w.ensurePolished();
    w.show();

    a.setQuitOnLastWindowClosed(false);

    return a.exec();
}
