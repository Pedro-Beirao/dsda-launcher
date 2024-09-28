QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += APP_NAME='\\"dsda-launcher\\"'

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060202    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    console.cpp \
    constants.cpp \
    demodialog.cpp \
    endoom.cpp \
    funcs.cpp \
    historylist.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow_actions.cpp \
    mainwindow_bottom.cpp \
    mainwindow_demos.cpp \
    mainwindow_options.cpp \
    mainwindow_styles.cpp \
    mainwindow_top.cpp \
    mainwindow_wads.cpp \
    settings.cpp \
    states.cpp \
    theme.cpp

HEADERS += \
    console.h \
    constants.h \
    demodialog.h \
    endoom.h \
    funcs.h \
    historylist.h \
    mainwindow.h \
    settings.h \
    states.h \
    styles.h \
    theme.h

FORMS += \
    console.ui \
    endoom.ui \
    historylist.ui \
    mainwindow.ui \
    settings.ui

include ($$PWD/QSimpleUpdater/QSimpleUpdater.pri)

win32 {
    CONFIG += c++11
    RC_ICONS = icons/dsda-launcher.ico
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++ -static
}

mac {
    CONFIG += c++11 appbundle
    ICON = icons/dsda-launcher.icns
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
