/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *LaunchGameButton;
    QPlainTextEdit *argumentText;
    QComboBox *compLevelSelect;
    QLabel *label;
    QComboBox *iwadSelect;
    QLabel *label_2;
    QLabel *episodeText;
    QLabel *label_5;
    QComboBox *diffBox;
    QLineEdit *episodeBox;
    QLineEdit *levelBox;
    QLabel *levelText;
    QGroupBox *groupBox;
    QToolButton *toolButton;
    QGroupBox *groupBox_4;
    QLabel *label_3;
    QToolButton *toolButton_3;
    QPushButton *pushButton;
    QTabWidget *tabs;
    QWidget *tab;
    QCheckBox *fastCheck;
    QCheckBox *noCheck;
    QLabel *label_6;
    QCheckBox *noCheck_3;
    QCheckBox *noCheck_4;
    QCheckBox *soloNetCheck;
    QWidget *widget;
    QWidget *wadsTab;
    QListWidget *wadsOnFolder;
    QToolButton *plus;
    QToolButton *minus;
    QToolButton *toolButton_2;
    QWidget *demoTab;
    QLabel *label_7;
    QLineEdit *recordDemo;
    QLineEdit *recordDemo_2;
    QLabel *label_8;
    QWidget *tab_2;
    QComboBox *comboBox;
    QLabel *label_4;
    QLabel *label_9;
    QLabel *wadLName;
    QLabel *levelL;
    QTextBrowser *toolTip;
    QComboBox *comboBox_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QComboBox *demoPlayOptions;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(350, 454);
        MainWindow->setMinimumSize(QSize(350, 454));
        MainWindow->setMaximumSize(QSize(350, 454));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        LaunchGameButton = new QPushButton(centralwidget);
        LaunchGameButton->setObjectName(QString::fromUtf8("LaunchGameButton"));
        LaunchGameButton->setGeometry(QRect(250, 420, 81, 25));
        LaunchGameButton->setStyleSheet(QString::fromUtf8(""));
        LaunchGameButton->setAutoDefault(false);
        LaunchGameButton->setFlat(false);
        argumentText = new QPlainTextEdit(centralwidget);
        argumentText->setObjectName(QString::fromUtf8("argumentText"));
        argumentText->setGeometry(QRect(30, 357, 291, 51));
        argumentText->setAcceptDrops(false);
        argumentText->setAutoFillBackground(false);
        argumentText->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(180, 180, 180);\n"
"\n"
"color: #000;\n"
"height: 20px;\n"
"background-color:rgb(255, 255, 255);\n"
"border-radius:3px"));
        argumentText->setInputMethodHints(Qt::ImhNone);
        compLevelSelect = new QComboBox(centralwidget);
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->addItem(QString());
        compLevelSelect->setObjectName(QString::fromUtf8("compLevelSelect"));
        compLevelSelect->setGeometry(QRect(110, 55, 201, 21));
        compLevelSelect->setStyleSheet(QString::fromUtf8(""));
        compLevelSelect->setMaxVisibleItems(14);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 27, 41, 16));
        iwadSelect = new QComboBox(centralwidget);
        iwadSelect->setObjectName(QString::fromUtf8("iwadSelect"));
        iwadSelect->setGeometry(QRect(110, 25, 201, 21));
        iwadSelect->setStyleSheet(QString::fromUtf8(""));
        iwadSelect->setFrame(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(35, 57, 81, 16));
        episodeText = new QLabel(centralwidget);
        episodeText->setObjectName(QString::fromUtf8("episodeText"));
        episodeText->setGeometry(QRect(55, 100, 51, 20));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(190, 100, 61, 20));
        diffBox = new QComboBox(centralwidget);
        diffBox->addItem(QString());
        diffBox->addItem(QString());
        diffBox->addItem(QString());
        diffBox->addItem(QString());
        diffBox->addItem(QString());
        diffBox->addItem(QString());
        diffBox->setObjectName(QString::fromUtf8("diffBox"));
        diffBox->setGeometry(QRect(250, 100, 61, 21));
        diffBox->setStyleSheet(QString::fromUtf8(""));
        episodeBox = new QLineEdit(centralwidget);
        episodeBox->setObjectName(QString::fromUtf8("episodeBox"));
        episodeBox->setGeometry(QRect(110, 99, 51, 21));
        episodeBox->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(160, 160, 160);\n"
"padding-left: 6px;\n"
"color: #000;\n"
"height: 20px;\n"
"background-color:rgb(255, 255, 255);\n"
"border-radius:3px"));
        episodeBox->setInputMethodHints(Qt::ImhDigitsOnly);
        levelBox = new QLineEdit(centralwidget);
        levelBox->setObjectName(QString::fromUtf8("levelBox"));
        levelBox->setGeometry(QRect(110, 129, 51, 21));
        levelBox->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(160, 160, 160);\n"
"padding-left: 6px;\n"
"color: #000;\n"
"height: 20px;\n"
"background-color:rgb(255, 255, 255);\n"
"border-radius:3px"));
        levelBox->setInputMethodHints(Qt::ImhDigitsOnly);
        levelText = new QLabel(centralwidget);
        levelText->setObjectName(QString::fromUtf8("levelText"));
        levelText->setGeometry(QRect(70, 130, 41, 20));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 311, 151));
        groupBox->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(37, 37, 37);\n"
""));
        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(20, 15, 20, 20));
        QFont font;
        font.setPointSize(12);
        toolButton->setFont(font);
        toolButton->setCheckable(true);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 335, 311, 81));
        groupBox_4->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 5, 251, 16));
        label_3->setStyleSheet(QString::fromUtf8(""));
        toolButton_3 = new QToolButton(groupBox_4);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setGeometry(QRect(155, 6, 13, 13));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 420, 101, 25));
        pushButton->setFont(font);
        pushButton->setIconSize(QSize(16, 16));
        pushButton->setAutoDefault(false);
        pushButton->setFlat(false);
        tabs = new QTabWidget(centralwidget);
        tabs->setObjectName(QString::fromUtf8("tabs"));
        tabs->setGeometry(QRect(20, 170, 311, 155));
        tabs->setStyleSheet(QString::fromUtf8(""));
        tabs->setTabShape(QTabWidget::Rounded);
        tabs->setUsesScrollButtons(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        fastCheck = new QCheckBox(tab);
        fastCheck->setObjectName(QString::fromUtf8("fastCheck"));
        fastCheck->setGeometry(QRect(20, 10, 111, 20));
        fastCheck->setStyleSheet(QString::fromUtf8(""));
        fastCheck->setChecked(false);
        noCheck = new QCheckBox(tab);
        noCheck->setObjectName(QString::fromUtf8("noCheck"));
        noCheck->setGeometry(QRect(170, 40, 111, 20));
        noCheck->setStyleSheet(QString::fromUtf8(""));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 84, 101, 16));
        QFont font1;
        font1.setPointSize(13);
        label_6->setFont(font1);
        noCheck_3 = new QCheckBox(tab);
        noCheck_3->setObjectName(QString::fromUtf8("noCheck_3"));
        noCheck_3->setGeometry(QRect(170, 97, 111, 20));
        noCheck_4 = new QCheckBox(tab);
        noCheck_4->setObjectName(QString::fromUtf8("noCheck_4"));
        noCheck_4->setGeometry(QRect(20, 40, 141, 20));
        noCheck_4->setStyleSheet(QString::fromUtf8(""));
        soloNetCheck = new QCheckBox(tab);
        soloNetCheck->setObjectName(QString::fromUtf8("soloNetCheck"));
        soloNetCheck->setGeometry(QRect(170, 10, 121, 20));
        widget = new QWidget(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 73, 281, 1));
        widget->setStyleSheet(QString::fromUtf8("color: rgb(200, 200, 200);\n"
"background-color: rgb(78, 79, 80);\n"
""));
        tabs->addTab(tab, QString());
        wadsTab = new QWidget();
        wadsTab->setObjectName(QString::fromUtf8("wadsTab"));
        wadsOnFolder = new QListWidget(wadsTab);
        wadsOnFolder->setObjectName(QString::fromUtf8("wadsOnFolder"));
        wadsOnFolder->setGeometry(QRect(10, 0, 251, 121));
        wadsOnFolder->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(139, 138, 140);\n"
"padding-left: 6px;\n"
"color: #000;\n"
"height: 20px;\n"
"background-color:rgb(230, 230, 230);\n"
"border-radius:3px"));
        wadsOnFolder->setWordWrap(true);
        plus = new QToolButton(wadsTab);
        plus->setObjectName(QString::fromUtf8("plus"));
        plus->setGeometry(QRect(274, 10, 21, 21));
        plus->setStyleSheet(QString::fromUtf8("border-image: url(:/pngs/pngs/plus.png);\n"
"color: rgb(255, 255, 255);"));
        minus = new QToolButton(wadsTab);
        minus->setObjectName(QString::fromUtf8("minus"));
        minus->setGeometry(QRect(274, 40, 21, 21));
        minus->setStyleSheet(QString::fromUtf8("border-image: url(:/pngs/pngs/minus.png);\n"
"color: rgb(255, 255, 255);"));
        toolButton_2 = new QToolButton(wadsTab);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(272, 90, 26, 22));
        tabs->addTab(wadsTab, QString());
        demoTab = new QWidget();
        demoTab->setObjectName(QString::fromUtf8("demoTab"));
        label_7 = new QLabel(demoTab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(15, 5, 91, 16));
        recordDemo = new QLineEdit(demoTab);
        recordDemo->setObjectName(QString::fromUtf8("recordDemo"));
        recordDemo->setGeometry(QRect(10, 25, 221, 21));
        recordDemo->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(180, 180, 180);\n"
"padding-left: 6px;\n"
"color: #000;\n"
"height: 20px;\n"
"background-color:rgb(255, 255, 255);\n"
"border-radius:3px"));
        recordDemo_2 = new QLineEdit(demoTab);
        recordDemo_2->setObjectName(QString::fromUtf8("recordDemo_2"));
        recordDemo_2->setGeometry(QRect(10, 75, 221, 21));
        recordDemo_2->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(180, 180, 180);\n"
"padding-left: 6px;\n"
"color: #000;\n"
"height: 20px;\n"
"background-color:rgb(255, 255, 255);\n"
"border-radius:3px"));
        label_8 = new QLabel(demoTab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(15, 55, 91, 16));
        tabs->addTab(demoTab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        comboBox = new QComboBox(tab_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 10, 131, 24));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 45, 60, 16));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 70, 60, 16));
        wadLName = new QLabel(tab_2);
        wadLName->setObjectName(QString::fromUtf8("wadLName"));
        wadLName->setGeometry(QRect(80, 45, 60, 16));
        levelL = new QLabel(tab_2);
        levelL->setObjectName(QString::fromUtf8("levelL"));
        levelL->setGeometry(QRect(80, 70, 60, 16));
        tabs->addTab(tab_2, QString());
        toolTip = new QTextBrowser(centralwidget);
        toolTip->setObjectName(QString::fromUtf8("toolTip"));
        toolTip->setEnabled(true);
        toolTip->setGeometry(QRect(10, 50, 201, 75));
        toolTip->setFont(font1);
        toolTip->setStyleSheet(QString::fromUtf8("border: 1px solid rgb(160, 160, 160);\n"
"padding-left: 6px;\n"
"color: #000;\n"
"height: 20px;\n"
"background-color:rgb(255, 255, 255);\n"
"border-radius:3px"));
        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(40, 295, 131, 21));
        comboBox_2->setStyleSheet(QString::fromUtf8(""));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(260, 216, 61, 30));
        pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(260, 267, 61, 30));
        pushButton_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        demoPlayOptions = new QComboBox(centralwidget);
        demoPlayOptions->addItem(QString());
        demoPlayOptions->addItem(QString());
        demoPlayOptions->addItem(QString());
        demoPlayOptions->setObjectName(QString::fromUtf8("demoPlayOptions"));
        demoPlayOptions->setGeometry(QRect(35, 295, 121, 20));
        demoPlayOptions->setStyleSheet(QString::fromUtf8("height:10px"));
        MainWindow->setCentralWidget(centralwidget);
        groupBox_4->raise();
        groupBox->raise();
        LaunchGameButton->raise();
        argumentText->raise();
        compLevelSelect->raise();
        label->raise();
        iwadSelect->raise();
        label_2->raise();
        episodeText->raise();
        label_5->raise();
        diffBox->raise();
        episodeBox->raise();
        levelBox->raise();
        levelText->raise();
        pushButton->raise();
        tabs->raise();
        toolTip->raise();
        comboBox_2->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        demoPlayOptions->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 350, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        LaunchGameButton->setDefault(true);
        pushButton->setDefault(false);
        tabs->setCurrentIndex(3);
        pushButton_2->setDefault(true);
        pushButton_3->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "dsda-launcher", nullptr));
        LaunchGameButton->setText(QCoreApplication::translate("MainWindow", "Launch", nullptr));
#if QT_CONFIG(tooltip)
        argumentText->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        argumentText->setPlainText(QString());
        compLevelSelect->setItemText(0, QCoreApplication::translate("MainWindow", "Default", nullptr));
        compLevelSelect->setItemText(1, QCoreApplication::translate("MainWindow", "Doom v1.2", nullptr));
        compLevelSelect->setItemText(2, QCoreApplication::translate("MainWindow", "Doom v1.666", nullptr));
        compLevelSelect->setItemText(3, QCoreApplication::translate("MainWindow", "Doom v1.9 / Doom II", nullptr));
        compLevelSelect->setItemText(4, QCoreApplication::translate("MainWindow", "Ultimate Doom", nullptr));
        compLevelSelect->setItemText(5, QCoreApplication::translate("MainWindow", "Final Doom", nullptr));
        compLevelSelect->setItemText(6, QCoreApplication::translate("MainWindow", "DOSDoom", nullptr));
        compLevelSelect->setItemText(7, QCoreApplication::translate("MainWindow", "TASDoom", nullptr));
        compLevelSelect->setItemText(8, QCoreApplication::translate("MainWindow", "Boom", nullptr));
        compLevelSelect->setItemText(9, QCoreApplication::translate("MainWindow", "LxDoom", nullptr));
        compLevelSelect->setItemText(10, QCoreApplication::translate("MainWindow", "MBF", nullptr));
        compLevelSelect->setItemText(11, QCoreApplication::translate("MainWindow", "Old PrBoom", nullptr));
        compLevelSelect->setItemText(12, QCoreApplication::translate("MainWindow", "Current PrBoom", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "IWAD", nullptr));
#if QT_CONFIG(whatsthis)
        iwadSelect->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_2->setText(QCoreApplication::translate("MainWindow", "CompLevel", nullptr));
        episodeText->setText(QCoreApplication::translate("MainWindow", "Episode", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Difficulty", nullptr));
        diffBox->setItemText(0, QString());
        diffBox->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));
        diffBox->setItemText(2, QCoreApplication::translate("MainWindow", "2", nullptr));
        diffBox->setItemText(3, QCoreApplication::translate("MainWindow", "3", nullptr));
        diffBox->setItemText(4, QCoreApplication::translate("MainWindow", "4", nullptr));
        diffBox->setItemText(5, QCoreApplication::translate("MainWindow", "5", nullptr));

        levelText->setText(QCoreApplication::translate("MainWindow", "Level", nullptr));
#if QT_CONFIG(tooltip)
        toolButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#808080;\">Additional Arguments</span></p></body></html>", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Console Log", nullptr));
        fastCheck->setText(QCoreApplication::translate("MainWindow", " Fast Monsters", nullptr));
        noCheck->setText(QCoreApplication::translate("MainWindow", " No Monsters", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Resolution</span></p></body></html>", nullptr));
        noCheck_3->setText(QCoreApplication::translate("MainWindow", " Fullscreen", nullptr));
        noCheck_4->setText(QCoreApplication::translate("MainWindow", " Respawn Monsters", nullptr));
        soloNetCheck->setText(QCoreApplication::translate("MainWindow", " Solo Net", nullptr));
        tabs->setTabText(tabs->indexOf(tab), QCoreApplication::translate("MainWindow", "Options", nullptr));
        plus->setText(QString());
        minus->setText(QString());
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        tabs->setTabText(tabs->indexOf(wadsTab), QCoreApplication::translate("MainWindow", "Wads", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Record", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Playback", nullptr));
        tabs->setTabText(tabs->indexOf(demoTab), QCoreApplication::translate("MainWindow", "Demos", nullptr));
        comboBox->setItemText(0, QString());
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "UV Speed", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "UV Max", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "UV Fast", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "UV Respawn", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("MainWindow", "NM Speed", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("MainWindow", "NM 100S", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("MainWindow", "Tyson", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("MainWindow", "Pacifist", nullptr));
        comboBox->setItemText(9, QCoreApplication::translate("MainWindow", "Stroller", nullptr));
        comboBox->setItemText(10, QCoreApplication::translate("MainWindow", "NoMo", nullptr));
        comboBox->setItemText(11, QCoreApplication::translate("MainWindow", "NoMo 100S", nullptr));
        comboBox->setItemText(12, QCoreApplication::translate("MainWindow", "Collector", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "Wad:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Level:", nullptr));
        wadLName->setText(QString());
        levelL->setText(QString());
        tabs->setTabText(tabs->indexOf(tab_2), QCoreApplication::translate("MainWindow", "DSDA", nullptr));
        toolTip->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Don't see any IWAD?     ^</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Press  </span><span style=\" font-size:11pt; font-weight:600;\">ctrl + o</span><span style=\" font-size:11pt;\"> / </span><span style=\" font-size:11pt; "
                        "font-weight:600;\">cmd + o</span><span style=\" font-size:11pt;\">  and drag your IWADs to the folder that opened</span></p></body></html>", nullptr));
        comboBox_2->setItemText(0, QString());
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "2560x1600", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "2048x1280", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "1680x1050", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("MainWindow", "1650x1050", nullptr));
        comboBox_2->setItemText(5, QCoreApplication::translate("MainWindow", "1440x900", nullptr));
        comboBox_2->setItemText(6, QCoreApplication::translate("MainWindow", "1280x800", nullptr));
        comboBox_2->setItemText(7, QCoreApplication::translate("MainWindow", "1152x720", nullptr));
        comboBox_2->setItemText(8, QCoreApplication::translate("MainWindow", "1024x768", nullptr));
        comboBox_2->setItemText(9, QCoreApplication::translate("MainWindow", "1024x640", nullptr));
        comboBox_2->setItemText(10, QCoreApplication::translate("MainWindow", "840x525", nullptr));
        comboBox_2->setItemText(11, QCoreApplication::translate("MainWindow", "825x525", nullptr));
        comboBox_2->setItemText(12, QCoreApplication::translate("MainWindow", "800x600", nullptr));
        comboBox_2->setItemText(13, QCoreApplication::translate("MainWindow", "640x480", nullptr));
        comboBox_2->setItemText(14, QCoreApplication::translate("MainWindow", "640x400", nullptr));
        comboBox_2->setItemText(15, QCoreApplication::translate("MainWindow", "320x240", nullptr));
        comboBox_2->setItemText(16, QCoreApplication::translate("MainWindow", "320x200", nullptr));

        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Create", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Choose", nullptr));
        demoPlayOptions->setItemText(0, QCoreApplication::translate("MainWindow", "Play Demo", nullptr));
        demoPlayOptions->setItemText(1, QCoreApplication::translate("MainWindow", "Time Demo", nullptr));
        demoPlayOptions->setItemText(2, QCoreApplication::translate("MainWindow", "Fast Demo", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
