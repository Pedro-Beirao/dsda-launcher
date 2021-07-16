#ifndef DOCUMENTATION_H
#define DOCUMENTATION_H

#include <QWidget>

namespace Ui {
class documentation;
}

class documentation : public QWidget
{
    Q_OBJECT

public:
    explicit documentation(QWidget *parent = nullptr);
    ~documentation();

private:
    Ui::documentation *ui;
};

#endif // DOCUMENTATION_H
