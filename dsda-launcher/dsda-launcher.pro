QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += "APP_NAME=dsda-launcher"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    console.cpp \
    historylist.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp

HEADERS += \
    console.h \
    historylist.h \
    mainwindow.h \
    settings.h

FORMS += \
    console.ui \
    historylist.ui \
    mainwindow.ui \
    settings.ui

win32 {
    CONFIG += c++11
    RC_ICONS = dsda-launcher.ico
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -static
}

mac {
    CONFIG += c++11 appbundle
    ICON = dsda-launcher.icns
    !noport {
        APP_FILES.files = ./dsda-doom
        APP_FILES.files += ./dsda-doom.wad
    }
    deploy {
        QMAKE_APPLE_DEVICE_ARCHS=arm64 x86_64
        message("Compiling for both archs")
    }
    APP_FILES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += APP_FILES
    QMAKE_INFO_PLIST =./Info.plist
    HEADERS += Mac.h
    OBJECTIVE_SOURCES += Mac.mm
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
    build

DISTFILES += \
    Style.qml
