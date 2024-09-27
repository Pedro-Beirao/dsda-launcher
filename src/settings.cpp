#include "settings.h"
#include "ui_settings.h"
#include <mainwindow.h>

Settings::Settings(QWidget *parent) : QWidget(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->darkTheme_checkBox->setChecked(settings->value("theme")=="dark");
    on_darkTheme_checkBox_clicked(settings->value("theme")=="dark");

    ui->endoom_checkBox->setChecked(settings->value("endoom").toBool());

#if defined Q_OS_WIN
    ui->PWADFolders_textBrowser->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:8pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; "
                                         "text-indent:0px;\"><span style=\" font-size:8pt;\">When droping .lmp files into the launcher, it autoselects the correct IWAD, PWADs and complevel.</span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">For this to work, you need to add the folders you have your PWADs in, to the following container.</span></p></body></html>");
    ui->IWADFolders_textBrowser->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:8pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; "
                                         "text-indent:0px;\"><span style=\" font-size:8pt;\">The launcher will search for IWADs on these folders.</span></p><p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>");
#endif

    ui->PWADFolders_textBrowser->setVisible(false);
    ui->IWADFolders_textBrowser->setVisible(false);

    if (settings->value("complevels").isNull())
    {
        ui->minimalComplevels_radioButton->setChecked(true);
        ui->remember_checkBox->setChecked(true);
        settings->setValue("toggle1t", ui->fastText_lineEdit->text());
        settings->setValue("toggle1a", ui->fastParam_lineEdit->text());
        settings->setValue("toggle2t", ui->nomoText_lineEdit->text());
        settings->setValue("toggle2a", ui->nomoParam_lineEdit->text());
        settings->setValue("toggle3t", ui->respawnText_lineEdit->text());
        settings->setValue("toggle3a", ui->respawnParam_lineEdit->text());
        settings->setValue("toggle4t", ui->solonetText_lineEdit->text());
        settings->setValue("toggle4a", ui->solonetParam_lineEdit->text());
        settings->setValue("remember", true);
    }
    else
    {
        ui->fastText_lineEdit->setText(settings->value("toggle1t").toString());
        ui->fastParam_lineEdit->setText(settings->value("toggle1a").toString());
        ui->nomoText_lineEdit->setText(settings->value("toggle2t").toString());
        ui->nomoParam_lineEdit->setText(settings->value("toggle2a").toString());
        ui->respawnText_lineEdit->setText(settings->value("toggle3t").toString());
        ui->respawnParam_lineEdit->setText(settings->value("toggle3a").toString());
        ui->solonetText_lineEdit->setText(settings->value("toggle4t").toString());
        ui->solonetParam_lineEdit->setText(settings->value("toggle4a").toString());
        ui->remember_checkBox->setChecked(settings->value("remember").toBool());
        if(settings->value("complevels").toInt()==0)
        {
            ui->minimalComplevels_radioButton->setChecked(true);
        }
        else if(settings->value("complevels").toInt()==1)
        {
            ui->fullComplevels_radioButton->setChecked(true);
        }
    }

    if (settings->value("exeName").isNull())
    {
        ui->executable_lineEdit->setText("dsda-doom");
    }
    else
    {
        ui->executable_lineEdit->setText(settings->value("exeName").toString());
    }
    MainWindow::pMainWindow->changeGameName(ui->executable_lineEdit->text());

    ui->maxHistory_lineEdit->setValidator(new QRegularExpressionValidator (QRegularExpression("[0-9]{2}"), this));
    
    // Keyboard shortcut
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS

    // Closes the active window
    QShortcut *shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL), this, SLOT(close()));
    shortcut3->setAutoRepeat(false);

    if(settings->value("maxhistory").toString()!="")
        ui->maxHistory_lineEdit->setText(settings->value("maxhistory").toString());

    int size = settings->beginReadArray("resolutions");
    if(size!=0)
    {
        ui->resolutions_listWidget->clear();
        for (int i = 0; i < size; i++)
        {
            settings->setArrayIndex(i);
            ui->resolutions_listWidget->addItem(settings->value("res").toString());
            ui->resolutions_listWidget->item(i)->setFlags(QFlags<Qt::ItemFlag>(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled));
        }
    }
    else
    {
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  geom = screen->geometry();
        if(geom.width() > 1920 || geom.height() > 1080)
        {
            ui->resolutions_listWidget->item(0)->setText(QString::number(geom.width()) + "x" + QString::number(geom.height()));
            for (int i = 0; i < ui->resolutions_listWidget->count(); i++)
            {
                ui->resolutions_listWidget->item(i)->setFlags(QFlags<Qt::ItemFlag>(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled));
            }
        }
    }
    settings->endArray();
    MainWindow::pMainWindow->setResolutionsList(ui->resolutions_listWidget);

#if defined Q_OS_WIN
    ui->PWADFolders_listWidget->addItem("Same Folder as the Launcher");
    ui->PWADFolders_listWidget->addItem("%DOOMWADPATH%");

    ui->IWADFolders_listWidget->addItem("Same Folder as the Launcher");
    ui->IWADFolders_listWidget->addItem("%DOOMWADDIR%");
#else
    ui->PWADFolders_listWidget->addItem("$DOOMWADPATH");
    ui->PWADFolders_listWidget->addItem(datafolder);

    ui->IWADFolders_listWidget->addItem("$DOOMWADDIR");
    ui->IWADFolders_listWidget->addItem(datafolder);
#endif
    ui->PWADFolders_listWidget->item(0)->setFlags(QFlags<Qt::ItemFlag>());
    ui->PWADFolders_listWidget->item(1)->setFlags(QFlags<Qt::ItemFlag>());

    ui->IWADFolders_listWidget->item(0)->setFlags(QFlags<Qt::ItemFlag>());
    ui->IWADFolders_listWidget->item(1)->setFlags(QFlags<Qt::ItemFlag>());

    size = settings->beginReadArray("pwadfolders");
    if(size!=0)
    {
        for (int i = 0; i < size; i++) {
            settings->setArrayIndex(i);
            if(settings->value("folder").toString()!="")
                ui->PWADFolders_listWidget->addItem(settings->value("folder").toString());
        }
    }
    settings->endArray();

    size = settings->beginReadArray("iwadfolders");
    if(size!=0)
    {
        for (int i = 0; i < size; i++) {
            settings->setArrayIndex(i);
            if(settings->value("folder").toString()!="")
                ui->IWADFolders_listWidget->addItem(settings->value("folder").toString());
        }
    }
    settings->endArray();

    ui->saved_label->hide();
    ui->notsaved_label->hide();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_darkTheme_checkBox_clicked(bool checked)
{
    if(!checked)
    {
        qApp->setStyleSheet("QLabel::disabled {color: rgb(200, 200, 200);}"
                            "QLabel {border: none; margin: 0px;background-color: rgba(50, 50, 50, 0);font: 13px}");

#if defined Q_OS_MACOS
        macSetToLightTheme();

        ui->PWADFolders_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
        ui->IWADFolders_pushButton->setStyleSheet(STYLE_MAC_BUTTON_LIGHT);
#else
        QPalette lightPalette;
        qApp->setPalette(lightPalette);
#endif

        settings->setValue("theme", "light");
    }
    else
    {
#if defined Q_OS_MACOS
        macSetToDarkTheme();

        ui->PWADFolders_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
        ui->IWADFolders_pushButton->setStyleSheet(STYLE_MAC_BUTTON_DARK);
#elif defined Q_OS_LINUX
         QPalette darkPalette;
         darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
         darkPalette.setColor(QPalette::WindowText, Qt::white);
         darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
         darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
         darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
         darkPalette.setColor(QPalette::ToolTipText, Qt::white);
         darkPalette.setColor(QPalette::Text, Qt::white);
         darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
         darkPalette.setColor(QPalette::ButtonText, Qt::white);
         darkPalette.setColor(QPalette::BrightText, Qt::red);
         darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
         darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
         darkPalette.setColor(QPalette::HighlightedText, Qt::black);
         qApp->setPalette(darkPalette);
         qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

#elif defined Q_OS_WIN
         qApp->setStyleSheet("* {color: rgb(221, 221, 221);background: rgb(53, 53, 53);}"
                             "QLabel {border: none; margin: 0px;background-color: rgba(50, 50, 50, 0);font: 13px}"
                             "QLabel::disabled {color: rgb(120, 120, 120);}"
                             "QPushButton {border: 1px solid rgb(120, 120, 120); text-align:center; border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150); max-height: 25px;}"
                             "QPushButton:hover {border: 1px solid rgb(120, 120, 120); text-align:center; border-radius:5px; background-color: rgb(62, 62, 62); color: rgb(150, 150, 150)}"
                             //"QPushButton:default {border: 1px solid rgb(4,93,244)}"
                             "QCheckBox {spacing: 4px;border: none;}"
                             "QRadioButton {spacing: 4px;border: none;}"
                             "QTabWidget {background-color: rgba(50, 50, 200, 200); border: none; }"
                             "QTabWidget::pane {top: -1px;margin: 0px;padding: 0px;border: 1px solid rgb(79, 79, 79);}"
                             "QStackedWidget > QWidget{background: rgba(50, 50, 50, 0);}"
                             "QTabBar {qproperty-drawBase: 0;border: none;}"
                             "QTabBar::tab {padding-left: 0.7em;padding-right: 0.7em;padding-bottom: 4px;padding-top: 3px;min-width: 8ex;border-right: 1px solid rgb(79, 79, 79);border-left: 1px solid rgb(79, 79, 79);}"
                             "QTabBar::tab::top:!selected:hover {background-color: rgb(50, 50, 50)}"
                             "QTabBar::tab::selected {background: rgb(53, 53, 53); margin-left: -3px;margin-right: -3px;border-top: 1px solid rgb(79, 79, 79);border-bottom:none;}"
                             "QTabBar::tab:!selected {margin-top: 4px;background: rgb(47, 47, 47);border-top: 1px solid rgb(79, 79, 79);border-bottom: 1px solid rgb(79, 79, 79);}"
                             "QTabBar::tab:first:selected {margin-left: 0;}"
                             "QTabBar::tab:last:selected {margin-right: 0;}"
                             "QComboBox {border: 1px solid rgb(79, 79, 79);background: rgb(53, 53, 53);}"
                             "QComboBox::disabled {border: 1px solid rgb(60, 60, 60);}"
                             "QComboBox::arrow {border: 1px solid rgb(60, 60, 60);}"
                             "QComboBox::drop-down {margin: 5px; padding-left: 12px; height: 12px; width: 12px; image: url(\":/pngs/pngs/combo_box_arrow.png\");}"
                             "QGroupBox {border: 1px solid rgb(79, 79, 79);}"
                             "QComboBox:hover {border: 1px solid rgb(4,93,244); background-color: rgb(55,63,76)}"
                             "QComboBox:on {border: 1px solid rgb(4,93,244); background-color: rgb(43,69,94); selection-background-color:rgb(79, 79, 79)}"
                             "QComboBox:focus {border: 1px solid rgb(79, 79, 79); background: rgb(53, 53, 53);}"
                             "QCheckBox::indicator:unchecked:hover {background-color: rgb(240,240,240); border-radius: 3px}"
                             "QGroupBox {padding-top: 2px;padding-left:7px;border-radius: 3px;margin:1px;}"
                             "QGroupBox::title {subcontrol-origin: content;}"
                             "QMenuBar::item:selected {background: rgb(43,43,43)}"
                             "QMenuBar::item:pressed {background: rgb(43,43,43)}"
                             "QMenu {border: 1px solid rgb(79, 79, 79)}"
                             "QMenu::item:selected {background-color: rgb(55,63,86)}"
                             "QListView {alternate-background-color: rgb(63, 63, 63);}"
                             "QMessageBox QPushButton {padding: 5px 10px;}"
                             "QToolTip {color: rgb(63, 63, 63);}");

#endif
        settings->setValue("theme", "dark");
    }
}


void Settings::on_plusPWADFolders_toolButton_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select PWAD folder"),"~/",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(dirName!="")
    {
        ui->PWADFolders_listWidget->addItem(dirName);
    }

    settings->beginWriteArray("pwadfolders");
    for (int i = 2; i < ui->PWADFolders_listWidget->count(); i++) {
        settings->setArrayIndex(i-2);
        settings->setValue("folder", ui->PWADFolders_listWidget->item(i)->text());
    }
    settings->endArray();
}

void Settings::on_minusPWADFolders_toolButton_clicked()
{
    if(ui->PWADFolders_listWidget->count()>2 && ui->PWADFolders_listWidget->currentRow()>1)
        ui->PWADFolders_listWidget->takeItem(ui->PWADFolders_listWidget->currentRow());

    settings->beginWriteArray("pwadfolders");
    for (int i = 2; i < ui->PWADFolders_listWidget->count(); i++) {
        settings->setArrayIndex(i-2);
        settings->setValue("folder", ui->PWADFolders_listWidget->item(i)->text());
    }
    settings->endArray();
}

void Settings::on_minimalComplevels_radioButton_toggled(bool checked)
{
    if(checked)
    {
        settings->setValue("complevels", 0);
        MainWindow::pMainWindow->setComplevelsList(MINIMAL_COMPLEVELS);
    }
}


void Settings::on_fullComplevels_radioButton_toggled(bool checked)
{
    if(checked)
    {
        settings->setValue("complevels", 1);
        MainWindow::pMainWindow->setComplevelsList(FULL_COMPLEVELS);
    }
}


void Settings::on_minusResolutions_toolButton_clicked()
{
    if(ui->resolutions_listWidget->count()>0)
        ui->resolutions_listWidget->takeItem(ui->resolutions_listWidget->currentRow());
    settingsChanged();

}



void Settings::on_plusResolutions_toolButton_clicked()
{
    ui->resolutions_listWidget->insertItem(0,"");
    ui->resolutions_listWidget->item(0)->setFlags(QFlags<Qt::ItemFlag>(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled));
    ui->resolutions_listWidget->scrollToTop();
    ui->resolutions_listWidget->setCurrentRow(0);
    settingsChanged();
}


void Settings::on_resolutions_listWidget_itemChanged(QListWidgetItem *item)
{
    settingsChanged();
}

void Settings::on_upResolutions_toolButton_clicked()
{
    if(ui->resolutions_listWidget->currentRow()>0)
    {
        int row = ui->resolutions_listWidget->currentRow();
        QListWidgetItem *item = ui->resolutions_listWidget->takeItem(row);
        ui->resolutions_listWidget->insertItem(row-1,item);
        ui->resolutions_listWidget->setCurrentRow(row-1);
        settingsChanged();
    }
}


void Settings::on_downResolutions_toolButton_clicked()
{
    if(ui->resolutions_listWidget->currentRow()<ui->resolutions_listWidget->count()-1)
    {
        int row = ui->resolutions_listWidget->currentRow();
        QListWidgetItem *item = ui->resolutions_listWidget->takeItem(row);
        ui->resolutions_listWidget->insertItem(row+1,item);
        ui->resolutions_listWidget->setCurrentRow(row+1);
        settingsChanged();
    }
}

void Settings::closeEvent(QCloseEvent *event) // When closing the launcher, save the settings
{

}


void Settings::on_PWADFolders_pushButton_clicked()
{
    ui->PWADFolders_textBrowser->setVisible(!ui->PWADFolders_textBrowser->isVisible());
}


void Settings::on_executable_lineEdit_textChanged(const QString &arg1)
{
    settingsChanged();
    if (arg1.isEmpty())
    {
        ui->executable_lineEdit->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    }
    else
    {
        ui->executable_lineEdit->setStyleSheet(STYLE_TEXT_NORMAL);
    }
}


void Settings::on_save_pushButton_clicked()
{
    ui->notsaved_label->hide();
    ui->saved_label->show();

    MainWindow::pMainWindow->setResolutionsList(ui->resolutions_listWidget);

    MainWindow::pMainWindow->setToggles(ui->fastText_lineEdit->text(), ui->fastParam_lineEdit->text(), ui->nomoText_lineEdit->text(), ui->nomoParam_lineEdit->text(), ui->respawnText_lineEdit->text(), ui->respawnParam_lineEdit->text(), ui->solonetText_lineEdit->text(), ui->solonetParam_lineEdit->text());

    if (ui->executable_lineEdit->text().isEmpty())
    {
        MainWindow::pMainWindow->changeGameName("dsda-doom");
    }
    else
    {
        MainWindow::pMainWindow->changeGameName(ui->executable_lineEdit->text());
    }

    settings->setValue("exeName", ui->executable_lineEdit->text());

    settings->setValue("toggle1t", ui->fastText_lineEdit->text());
    settings->setValue("toggle1a", ui->fastParam_lineEdit->text());

    settings->setValue("toggle2t", ui->nomoText_lineEdit->text());
    settings->setValue("toggle2a", ui->nomoParam_lineEdit->text());

    settings->setValue("toggle3t", ui->respawnText_lineEdit->text());
    settings->setValue("toggle3a", ui->respawnParam_lineEdit->text());

    settings->setValue("toggle4t", ui->solonetText_lineEdit->text());
    settings->setValue("toggle4a", ui->solonetParam_lineEdit->text());

    settings->beginWriteArray("resolutions");
    for (int i = 0; i < ui->resolutions_listWidget->count(); i++) {
        settings->setArrayIndex(i);
        settings->setValue("res", ui->resolutions_listWidget->item(i)->text());
    }
    settings->endArray();
}

void set_placeholder_styleSheet(QLineEdit *l, const QString &arg1)
{
    if(arg1=="")
    {
        l->setStyleSheet(STYLE_TEXT_PLACEHOLDER);
    }
    else
    {
        l->setStyleSheet(STYLE_TEXT_NORMAL);
    }
}

void Settings::on_fastText_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->fastText_lineEdit, arg1);
    settingsChanged();
}


void Settings::on_fastParam_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->fastParam_lineEdit, arg1);
    settingsChanged();
}


void Settings::on_nomoText_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->nomoText_lineEdit, arg1);
    settingsChanged();
}


void Settings::on_nomoParam_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->nomoParam_lineEdit, arg1);
    settingsChanged();
}


void Settings::on_respawnText_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->respawnText_lineEdit, arg1);
    settingsChanged();
}


void Settings::on_respawnParam_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->respawnParam_lineEdit, arg1);
    settingsChanged();
}


void Settings::on_solonetText_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->solonetText_lineEdit, arg1);
    settingsChanged();
}


void Settings::on_solonetParam_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->solonetParam_lineEdit, arg1);
    settingsChanged();
}

void Settings::settingsChanged()
{
    ui->saved_label->hide();
    ui->notsaved_label->show();
}

void Settings::on_maxHistory_lineEdit_textChanged(const QString &arg1)
{
    set_placeholder_styleSheet(ui->maxHistory_lineEdit, arg1);
    settings->setValue("maxhistory", arg1);
}


void Settings::on_IWADFolders_pushButton_clicked()
{
    ui->IWADFolders_textBrowser->setVisible(!ui->IWADFolders_textBrowser->isVisible());
}


void Settings::on_plusIWADFolders_toolButton_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select IWAD folder"),"~/",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(dirName!="")
    {
        ui->IWADFolders_listWidget->addItem(dirName);
    }

    settings->beginWriteArray("iwadfolders");
    for (int i = 2; i < ui->IWADFolders_listWidget->count(); i++) {
        settings->setArrayIndex(i-2);
        settings->setValue("folder", ui->IWADFolders_listWidget->item(i)->text());
    }
    settings->endArray();
}


void Settings::on_minusIWADFolders_toolButton_clicked()
{
    if(ui->IWADFolders_listWidget->count()>2 && ui->IWADFolders_listWidget->currentRow()>1)
        ui->IWADFolders_listWidget->takeItem(ui->IWADFolders_listWidget->currentRow());

    settings->beginWriteArray("iwadfolders");
    for (int i = 2; i < ui->IWADFolders_listWidget->count(); i++) {
        settings->setArrayIndex(i-2);
        settings->setValue("folder", ui->IWADFolders_listWidget->item(i)->text());
    }
    settings->endArray();
}


void Settings::on_endoom_checkBox_clicked(bool checked)
{
    settings->setValue("endoom", checked);
}


void Settings::on_remember_checkBox_toggled(bool checked)
{
    settings->setValue("remember", checked);
}

