#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bootstrap.h>
#include "bootstrap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addWads(QStringList fileNames);
    void get_leaderboards(std::string wad, std::string level, std::string category);

private:
    Ui::MainWindow *ui;


private slots:
    void on_LaunchGameButton_clicked();
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
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void on_toolButton_3_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_toolButton_4_clicked();
};
#endif // MAINWINDOW_H
