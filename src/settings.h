#ifndef SETTINGS_H
#define SETTINGS_H

#include "Mac.h"
#include "styles.h"
#include <QActionGroup>
#include <QFileDialog>
#include <QItemDelegate>
#include <QListWidget>
#include <QProcess>
#include <QScreen>
#include <QStyleFactory>
#include <QWidget>
#include <qsettings.h>
#include <qshortcut.h>
#include <qstandardpaths.h>

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
  void on_darkTheme_checkBox_clicked(bool checked);

  void on_minimalComplevels_radioButton_toggled(bool checked);
  void on_fullComplevels_radioButton_toggled(bool checked);

  void on_resolutions_listWidget_itemChanged(QListWidgetItem *item);

  void closeEvent(QCloseEvent *event);

  void on_downResolutions_toolButton_clicked();
  void on_upResolutions_toolButton_clicked();
  void on_minusResolutions_toolButton_clicked();
  void on_plusResolutions_toolButton_clicked();

  void on_executable_lineEdit_textChanged(const QString &arg1);

  void on_save_pushButton_clicked();

  void on_fastText_lineEdit_textChanged(const QString &arg1);
  void on_fastParam_lineEdit_textChanged(const QString &arg1);
  void on_nomoText_lineEdit_textChanged(const QString &arg1);
  void on_nomoParam_lineEdit_textChanged(const QString &arg1);
  void on_respawnText_lineEdit_textChanged(const QString &arg1);
  void on_respawnParam_lineEdit_textChanged(const QString &arg1);
  void on_solonetText_lineEdit_textChanged(const QString &arg1);
  void on_solonetParam_lineEdit_textChanged(const QString &arg1);

  void settingsChanged();

  void on_maxHistory_lineEdit_textChanged(const QString &arg1);

  void on_IWADFolders_pushButton_clicked();
  void on_minusIWADFolders_toolButton_clicked();
  void on_plusIWADFolders_toolButton_clicked();

  void on_PWADFolders_pushButton_clicked();
  void on_minusPWADFolders_toolButton_clicked();
  void on_plusPWADFolders_toolButton_clicked();

  void on_endoom_checkBox_clicked(bool checked);

  void on_remember_checkBox_toggled(bool checked);

  void on_updaterStartLauncher_checkBox_toggled(bool checked);
  void on_updaterStartGame_checkBox_toggled(bool checked);

private:
  Ui::Settings *ui;
  void ReadSettings();
};

#endif // SETTINGS_H
