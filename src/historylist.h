#ifndef HISTORYLIST_H
#define HISTORYLIST_H

#include <QWidget>
#include "fstream"
#include <QStandardPaths>
#include <QSettings>
#include <QShortcut>

namespace Ui {
class historyList;
}

class historyList : public QWidget
{
    Q_OBJECT

public:
    explicit historyList(QWidget *parent = nullptr);
    ~historyList();

private:
    Ui::historyList *ui;

    QString historyPath;

  public slots:
    void getHistory();
    void fooo3();
private slots:
    void on_load_pushButton_clicked();
    void on_launch_pushButton_clicked();
};

#endif // HISTORYLIST_H
