#ifndef LOADLMP_H
#define LOADLMP_H

#include <QWidget>

namespace Ui {
class loadLMP;
}

class loadLMP : public QWidget
{
    Q_OBJECT

public:
    explicit loadLMP(QWidget *parent = nullptr);
    ~loadLMP();

private:
    Ui::loadLMP *ui;
};

#endif // LOADLMP_H
