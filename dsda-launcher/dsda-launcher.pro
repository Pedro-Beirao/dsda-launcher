QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32|unix
{
    CONFIG += c++11
    RC_ICONS = doom-launcher.ico
}
macx
{
    CONFIG += c++11 appbundle
    ICON = doom-launcher.icns
    APP_FILES.files = ./dsda-doom
    APP_FILES.files += ./dsda-doom.wad
    APP_FILES.files += ./launcher_config.txt
    deploy {
        APP_FILES.files += ./lib
        message("ready for deploy")
    }
    APP_FILES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += APP_FILES
    QMAKE_INFO_PLIST =./Info.plist
    HEADERS += Mac.h
    OBJECTIVE_SOURCES += Mac.mm
}

DEFINES += "APP_NAME=dsda-launcher"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settings.cpp

HEADERS += \
    mainwindow.h \
    settings.h

FORMS += \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
    build

DISTFILES += \
    Style.qml
