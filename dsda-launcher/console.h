#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>

namespace Ui {
class Console;
}

class Console : public QWidget
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = nullptr);
    ~Console();
    Ui::Console *ui;

public slots:
    void fooo();
    void fooo3();
    void changeText(std::string s);
    void clearText();
};

#endif // CONSOLE_H
