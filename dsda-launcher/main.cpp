#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QStyleFactory>



int main(int argc, char *argv[])
{
    #ifdef LINUX
    std::string os = "Linux";
    #else
    #ifdef WINDOWS
    std::string os = "Windows";
    #else
    std::string os = "Mac OSX";
    #endif
    #endif

    if(os=="Linux" || os=="Windows")
    {
        QApplication::setStyle("Fusion");
    }


    QApplication a(argc, argv);

    MainWindow w;
    //QFile file("/users/pedro/desktop/style.qss");
    //file.open(QFile::ReadOnly);
    //QString styleSheet = QLatin1String(file.readAll());
    //w.setStyleSheet(styleSheet);

    w.ensurePolished();
    w.show();

    return a.exec();
}
