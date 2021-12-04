#ifndef QUICKARGS_H
#define QUICKARGS_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class quickargs;
}

class quickargs : public QWidget
{
    Q_OBJECT

public:
    explicit quickargs(QWidget *parent = nullptr);
    ~quickargs();

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void foooo3();
    void foooo();

private:
    Ui::quickargs *ui;
};

#endif // QUICKARGS_H
