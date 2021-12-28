#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

public slots:

private slots:
    void fooo();
    void fooo3();
    void on_checkBox_clicked(bool checked);

    void on_toolButton_2_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
