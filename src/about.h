#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QShortcut>
#include <QRegularExpression>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();
    Ui::About *ui;

public slots:
    void ctrlw();

private slots:
    void on_dsda_launch_pushButton_clicked();
};

#endif // ABOUT_H
