#ifndef DEMODIALOG_H
#define DEMODIALOG_H

#include "funcs.h"
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QLabel>
#include <QPair>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>
#include <qtablewidget.h>

class demodialog : public QDialog
{
    Q_OBJECT

public:
  explicit demodialog(QString missing_iwad, QStringList missing_files, QWidget *parent = nullptr);
  int get_iwad_index();
  QStringList get_files_list();

private:
    QComboBox *iwad_comboBox;
    QTableWidget *files_listWidget;
    QVector<QPair<QString, QString>> files_paths;
    QLabel *selected_count;
    void update_selected_count();
    void findFiles();
};

#endif // DEMODIALOG_H


