#ifndef HISTORYLIST_H
#define HISTORYLIST_H

#include <QWidget>

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

public slots:
    void getHistory();
};

#endif // HISTORYLIST_H
