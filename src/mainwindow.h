#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#elif __APPLE__
#include "Mac.h"
#endif

#include "./ui_mainwindow.h"
#include "console.h"
#include "constants.h"
#include "demodialog.h"
#include "endoom.h"
#include "funcs.h"
#include "historylist.h"
#include "settings.h"
#include "states.h"
#include <QClipboard>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QMimeData>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProcess>
#include <QPushButton>
#include <QRegularExpression>
#include <QSettings>
#include <QShortcut>
#include <QStandardPaths>
#include <QTextEdit>
#include <QtConcurrent>
#include <QtNetwork>
#include <qgraphicseffect.h>

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
    void gameIsRunningDialog();

    QString exeName = "dsda-doom";

    void enable_disable_skill_comboBox();

    // Prevents launching the game twice if the button "Launch" is pressed twice quickly
    bool canLaunch = true;

    // Create an instance of the windows
    Settings *settingsWindow;
    Console *consoleWindow;
    historyList *historyListWindow;
    demodialog *demoDialog;
    endoom *endoomWindow;

    QString endoomString;

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow *pMainWindow;
    void addPwads(QStringList fileNames);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *ev);
    QComboBox *iwad_comboBox();
    QComboBox *complevel_comboBox();
    QLineEdit *episode_lineEdit();
    QLineEdit *level_lineEdit();
    QComboBox *difficulty_comboBox();
    QCheckBox *toggle1_checkBox();
    QCheckBox *toggle2_checkBox();
    QCheckBox *toggle3_checkBox();
    QCheckBox *toggle4_checkBox();
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
    void on_launchGame_pushButton_clicked(bool returnTooltip, QString exportCmd);
    void on_iwad_comboBox_currentIndexChanged(int index);
    void on_console_pushButton_clicked();
    void on_addPwads_toolButton_clicked();
    void on_removeWads_toolButton_clicked();
    void on_record_pushButton_clicked();
    void on_playback_pushButton_clicked();
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void on_additionalArguments_pushButton_clicked();

    // Actions
    void on_actionLoadState_triggered();
    void on_actionSaveState_triggered();
    void on_actionWhatIsThisState_triggered();
    void on_actionGithubDsdalauncher_triggered();
    void on_actionCheckForUpdatesDsdalauncher_triggered();
    void on_actionGithubDsdadoom_triggered();
    void on_actionCheckForUpdatesDsdadoom_triggered();
    void on_actionOpenSettings_triggered();
    void on_actionTips_triggered();
    void on_actionOpenHistory_triggered();
    void on_actionExportCommand_triggered();
    void on_actionOpenIWADsFolder_triggered();
    void on_actionOpenConsole_triggered();

    void setMaxSkillLevel(int max);
    void changeButtonColor(bool isDark);
    void setComplevelsList(QStringList list);
    void setResolutionsList(QListWidget *list);
    void dropFile(QString fileName);
    void dropLmp(QString filePath);
    void findIwads();
    void changeExeName(QString newName);
    void setToggles(QString t1, QString a1, QString t2, QString a2, QString t3, QString a3, QString t4, QString a4);
    void whenAnimationFinishNext();
    void whenAnimationFinishPrevious();
    void nextStackedWidget();
    void previousStackedWidget();
    void SaveHistory(QStringList args);
    void Launch(QStringList arguments);
    void showSSLDialog();
    void on_tooltip_pushButton_clicked();

  public Q_SLOTS:
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void error(QProcess::ProcessError error);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();

private slots:
  void demoDialog_accepted();
  void on_viddump_lineEdit_textChanged(const QString &arg1);
  void on_playback_comboBox_currentIndexChanged(int index);
  void on_viddump_pushButton_clicked();
  void on_showCommandLine_pushButton_clicked();
  void on_episode_lineEdit_textChanged(const QString &arg1);
  void on_nextPage_pushButton_clicked();
  void on_previousPage_pushButton_clicked();
  void on_hud_lineEdit_textChanged(const QString &arg1);
  void on_config_lineEdit_textChanged(const QString &arg1);
  void on_hud_pushButton_clicked();
  void on_config_pushButton_clicked();
  void on_playback_lineEdit_textChanged(const QString &arg1);
  QFileInfoList findIwads_possibleFiles();
  void loadSelected();
  void saveSelected();
  void setStyles();
  QStringList getArguments();
};
extern QSettings *settings;

#endif // MAINWINDOW_H
