#ifndef DEMODIALOG_H
#define DEMODIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QSettings>
#include <mainwindow.h>
#include <QPair>

class demodialog : public QDialog
{
    Q_OBJECT

public:
    explicit demodialog(QStringList iwad_list, QWidget *parent = nullptr);
    int get_iwad_index();

private:
    QComboBox *iwad_comboBox;
    QListWidget *files_listWidget;
    QVector<QPair<QString, QString>> files_paths;
    QLabel *selected_count;
    void update_selected_count();
};

#endif // DEMODIALOG_H


