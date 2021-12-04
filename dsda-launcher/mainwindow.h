#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow * getMainWin();

private:
    Ui::MainWindow *ui;
    static MainWindow * pMainWindow;

public slots:
    void addWads(QStringList fileNames);
    void get_leaderboards(std::string wad, std::string level, std::string category);
    void reloadLeaderboard(bool changeWad, bool callApi);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *ev);
    void delayLaunch();
    void closeEvent(QCloseEvent *event);
    void on_LaunchGameButton_clicked(bool onExit, bool returnTooltip);
    void on_iwadSelect_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_plus_clicked();
    void on_minus_clicked();
    void on_fastCheck_toggled(bool checked);
    void on_noCheck_toggled(bool checked);
    void on_toolButton_toggled(bool checked);
    void on_noCheck_4_toggled(bool checked);
    void on_noCheck_3_toggled(bool checked);
    void on_soloNetCheck_toggled(bool checked);
    void on_tabs_currentChanged(int index);
    void foo();
    void foo2();
    void foo3();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void on_toolButton_3_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_episodeBox_textChanged(const QString &arg1);
    void on_levelBox_textChanged(const QString &arg1);
    void on_editParameters_clicked();
    void clearLeaderboard();
    void addToArguments(QString string);

private slots:


    void on_toolButton_5_clicked();
    void on_ReloadLead_clicked();
    void on_wadLName_textChanged(const QString &arg1);
    void on_toolButton_4_clicked();
};
extern QSettings settings;

#endif // MAINWINDOW_H
