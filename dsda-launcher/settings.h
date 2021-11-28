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
    QString getIWADsPath();

private slots:
    void on_checkBox_toggled(bool checked);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H