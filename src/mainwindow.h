#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#elif __APPLE__
#include "Mac.h"
#endif

#include <QMainWindow>
#include <QSettings>
#include <QProcess>
#include <QListWidget>
#include <QPushButton>
#include <QDir>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QStandardPaths>
#include <QShortcut>
#include <fstream>
#include <iostream>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <vector>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QRegularExpression>
#include <QDesktopServices>
#include <QtConcurrent>
#include <QMessageBox>
#include "settings.h"
#include <string>
#include "console.h"
#include <QClipboard>
#include <sstream>
#include <qgraphicseffect.h>
#include "historylist.h"
#include "demodialog.h"
#include "states.h"
#include <QTextEdit>
#include "endoom.h"

const QString version = "v1.3.1";

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    // If dsda-doom is running
    bool running = false;
    void gameIsRunning();

    QString exeName = "dsda-doom";

    void enable_disable_skill_comboBox();
    void enable_disable_complevel_comboBox();

    #if defined(__APPLE__) || defined(__linux__)
    QString dotfolder = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom";
    QString historyPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom/history.states";
    #else
    QString historyPath;
    #endif

    QString execPath;

    // These are the parameters with toggles you can customise
    // These names come from the defaults I created
    QString fastParam = "-fast";
    QString nomoParam = "-nomonsters";
    QString respawnParam = "-respawn";
    QString solonetParam = "-solo-net";

    QVector<QPair<QString, QString>> iwads_paths;

    // Prevents launching the game twice if the button "Launch" is pressed twice quickly
    bool canLaunch = true;

    // Create an instance of the windows
    Settings *settingsWindow;
    Console *consoleWindow;
    historyList *historyListWindow;
    demodialog *demoDialog;
    endoom *endoomWindow;

    QString endoomString;

    QStringList doom1IWADs = {
        "doom",
        "doom1",
        "doomu",
        "freedoom",
        "freedoom1",
        "bfgdoom",
        "bfgdoom1",

        "heretic",
        "heretic1",

        "chex",
        "rekkrsa"
    };

    QStringList doom2IWADs = {
        "doom2",
        "doom2f",
        "freedoom2",
        "bfgdoom2",

        "tnt",
        "plutonia",

        "hexen",

        "hacx"
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow *pMainWindow;
    void addWads(QStringList fileNames);
    void get_leaderboards(std::string wad, std::string level, std::string category);
    void reloadLeaderboard(bool changeWad, bool callApi);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *ev);
    QComboBox *iwad_comboBox();
    QComboBox *complevel_comboBox();
    QLineEdit *episode_lineEdit();
    QLineEdit *level_lineEdit();
    QComboBox *difficulty_comboBox();
    QCheckBox *fast_checkBox();
    QCheckBox *nomo_checkBox();
    QCheckBox *respawn_checkBox();
    QCheckBox *solonet_checkBox();
    QComboBox *resolution_comboBox();
    QCheckBox *fullscreen_checkBox();
    QLineEdit *hud_lineEdit();
    QLineEdit *config_lineEdit();
    QComboBox *track_comboBox();
    QComboBox *time_comboBox();
    QListWidget *wads_listWidget();
    QLineEdit *record_lineEdit();
    QLineEdit *playback_lineEdit();
    QLineEdit *viddump_lineEdit();
    QComboBox *playback_comboBox();
    QTextEdit *additionalArguments_textEdit();

public slots:
    void delayLaunch();
    void closeEvent(QCloseEvent *event);
    void on_launchGame_pushButton_clicked(bool onExit, bool returnTooltip, std::string exportCmd);
    void on_iwad_comboBox_currentIndexChanged(int index);
    void on_console_pushButton_clicked();
    void on_addWads_toolButton_clicked();
    void on_removeWads_toolButton_clicked();
    void on_fast_checkBox_toggled(bool checked);
    void on_nomo_checkBox_toggled(bool checked);
    void on_tooltip_pushButton_clicked();
    void on_respawn_checkBox_toggled(bool checked);
    void on_fullscreen_checkBox_toggled(bool checked);
    void on_solonet_checkBox_toggled(bool checked);
    void foo();
    void foo3();
    void on_record_pushButton_clicked();
    void on_playback_pushButton_clicked();
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void on_additionalArguments_pushButton_clicked();
    void on_dsda_comboBox_currentIndexChanged(int index);
    void clearLeaderboard();
    void addToArguments(QString string);
    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionGithub_triggered();
    void on_actionGithub_2_triggered();
    void on_actionCheck_for_updates_triggered();
    void on_actionSet_triggered();
    void on_actionTips_triggered();
    void on_actionWhat_is_this_triggered();
    void on_actionCheck_for_Updates_triggered();
    void changeMaxSkillLevel(int max);
    void changeButtonColor(bool isDark);
    void changeComplevelsList(int i);
    void changeResolutions(QListWidget *list);
    void dropFile(QString fileName);
    void dropLmp(QString fileName);
    QString getFilePath(QString fileName);
    void findIwads(int type);
    void changeExeName(QString newName);
    void on_actionCommand_triggered();
    void on_actionOpen_IWAD_folder_triggered();
    void on_actionOpen_Console_triggered();
    void changeToggles(QString t1, QString a1, QString t2, QString a2, QString t3, QString a3, QString t4, QString a4);
    void changeWadLName();
    void whenAnimationFinishn();
    void whenAnimationFinishp();
    void nextStackedWidget();
    void previousStackedWidget();
    void on_actionHistory_triggered();
    void SaveHistory(QString iwad, QStringList args);
    void Launch(QString iwadName, QStringList argList);
    void showSSLDialog();

public Q_SLOTS:
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void error(QProcess::ProcessError error);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();

private slots:
    void demoDialog_accepted();
    void on_showLeaderboard_toolButton_clicked();
    void on_reloadLeaderboard_toolButton_clicked();
    void on_wadDSDA_lineEdit_textChanged(const QString &arg1);
    void on_viddump_lineEdit_textChanged(const QString &arg1);
    void on_playback_comboBox_currentIndexChanged(int index);
    void on_viddump_pushButton_clicked();
    void on_showCommandLine_pushButton_clicked();
    void on_levelDSDA_lineEdit_textChanged(const QString &arg1);
    void on_episode_lineEdit_textChanged(const QString &arg1);
    void on_nextPage_pushButton_clicked();
    void on_previousPage_pushButton_clicked();
    void on_hud_lineEdit_textChanged(const QString &arg1);
    void on_config_lineEdit_textChanged(const QString &arg1);
    void on_hud_pushButton_clicked();
    void on_config_pushButton_clicked();
    void on_playback_lineEdit_textChanged(const QString &arg1);
};
extern QSettings *settings;

#endif // MAINWINDOW_H
