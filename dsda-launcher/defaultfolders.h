#ifndef DEFAULTFOLDERS_H
#define DEFAULTFOLDERS_H

#include <QWidget>

namespace Ui {
class DefaultFolders;
}

class DefaultFolders : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultFolders(QWidget *parent = nullptr);
    ~DefaultFolders();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::DefaultFolders *ui;
};

#endif // DEFAULTFOLDERS_H
