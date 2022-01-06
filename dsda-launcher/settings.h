#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QListWidget>

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

    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_toolButton_5_clicked();

    void on_toolButton_4_clicked();
    void on_listWidget_2_itemChanged(QListWidgetItem *item);

    void on_toolButton_6_clicked();
    void closeEvent(QCloseEvent *event);
    void changeButtonColorS(bool isDark);

    void on_toolButton_7_clicked();

    void on_toolButton_3_clicked();

    void on_checkBox_2_toggled(bool checked);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
