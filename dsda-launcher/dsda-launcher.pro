QT       += core gui

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
    deploy {
        APP_FILES.files += ./lib
        APP_FILES.files += ./dsda-doom.wad
        message("ready for deploy")
    }
    APP_FILES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += APP_FILES
    QMAKE_INFO_PLIST =./Info.plist
}

DEFINES += "APP_NAME=dsda-launcher"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    loadlmp.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    loadlmp.h \
    mainwindow.h

FORMS += \
    loadlmp.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
    build

DISTFILES += \
    Style.qml
