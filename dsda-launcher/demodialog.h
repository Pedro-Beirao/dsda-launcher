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

class demodialog : public QDialog
{
    Q_OBJECT

public:
    explicit demodialog(QStringList iwad_list, QWidget *parent = nullptr);
    int get_iwad_index();

private:
    QComboBox *iwad_comboBox;
    QListWidget *files_listWidget;
    QStringList files_paths;
};

#endif // DEMODIALOG_H


