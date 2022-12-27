#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <qsettings.h>
#include <mainwindow.h>
#include "Mac.h"
#include <qshortcut.h>
#include <qstandardpaths.h>
#include <QProcess>
#include <QStyleFactory>
#include <QActionGroup>
#include <QItemDelegate>
#include <QScreen>

MainWindow * pmainWindow;

void Settings::changeButtonColorS(bool isDark)
{

}

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    pmainWindow = MainWindow::getMainWin();

    if(settings.value("theme")=="dark")
    {
        ui->checkBox->setChecked(true);
        on_checkBox_clicked(true);
    }
    else
    {
        ui->checkBox->setChecked(false);
        on_checkBox_clicked(false);
    }

#ifdef __APPLE__
        QFont font = ui->label_2->font();
        font.setPixelSize(13);
        ui->label_2->setFont(font);
#else
        ui->textBrowser->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">When droping .lmp files into the launcher, it autoselects the correct IWAD, PWADs and complevel.</span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">For this to work, you need to add the folders you have your PWADs in, to the following container.</span></p></body></html>");
#endif

    ui->textBrowser->setVisible(false);
    ui->textBrowser_2->setVisible(false);

    if(settings.value("complevels").toString()=="")
    {
        ui->radioButton->setChecked(true);
        settings.setValue("toggle1t", ui->lineEdit_3->text());
        settings.setValue("toggle1a", ui->lineEdit_5->text());
        settings.setValue("toggle2t", ui->lineEdit_4->text());
        settings.setValue("toggle2a", ui->lineEdit_6->text());
        settings.setValue("toggle3t", ui->lineEdit_7->text());
        settings.setValue("toggle3a", ui->lineEdit_9->text());
        settings.setValue("toggle4t", ui->lineEdit_8->text());
        settings.setValue("toggle4a", ui->lineEdit_10->text());
    }
    else
    {
        ui->lineEdit_3->setText(settings.value("toggle1t").toString());
        ui->lineEdit_5->setText(settings.value("toggle1a").toString());
        ui->lineEdit_4->setText(settings.value("toggle2t").toString());
        ui->lineEdit_6->setText(settings.value("toggle2a").toString());
        ui->lineEdit_7->setText(settings.value("toggle3t").toString());
        ui->lineEdit_9->setText(settings.value("toggle3a").toString());
        ui->lineEdit_8->setText(settings.value("toggle4t").toString());
        ui->lineEdit_10->setText(settings.value("toggle4a").toString());
        if(settings.value("complevels").toInt()==0)
        {
            ui->radioButton->setChecked(true);
        }
        else if(settings.value("complevels").toInt()==1)
        {
            ui->radioButton_3->setChecked(true);
        }
    }

    ui->lineEdit_2->setText(settings.value("exeName").toString());

    ui->lineEdit->setValidator(new QRegularExpressionValidator (QRegularExpression("[0-9]{1}"), this));
    ui->lineEdit_11->setValidator(new QRegularExpressionValidator (QRegularExpression("[0-9]{2}"), this));
    
    // Keyboard shortcut
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS

    // Closes the active window
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);

    if(settings.value("maxskilllevel").toString()!="")
        ui->lineEdit->setText(settings.value("maxskilllevel").toString());

    if(settings.value("maxhistory").toString()!="")
        ui->lineEdit_11->setText(settings.value("maxhistory").toString());

    int size = settings.beginReadArray("resolutions");
    if(size!=0)
    {
        ui->listWidget_2->clear();
        for (int i = 0; i < size; i++)
        {
            settings.setArrayIndex(i);
            ui->listWidget_2->addItem(settings.value("res").toString());
            ui->listWidget_2->item(i)->setFlags(QFlags<Qt::ItemFlag>(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled));
        }
    }
    else
    {
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect  geom = screen->geometry();
        if(geom.width() > 1920 || geom.height() > 1080)
        {
            ui->listWidget_2->item(0)->setText(QString::number(geom.width()) + "x" + QString::number(geom.height()));
            for (int i = 0; i < ui->listWidget_2->count(); i++)
            {
                ui->listWidget_2->item(i)->setFlags(QFlags<Qt::ItemFlag>(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled));
            }
        }
    }
    settings.endArray();
    pmainWindow->changeResolutions(ui->listWidget_2);

#ifdef _WIN32
        ui->listWidget->addItem("Same Folder as the Launcher");
        ui->listWidget->addItem("%DOOMWADPATH%");

        ui->listWidget_3->addItem("Same Folder as the Launcher");
        ui->listWidget_3->addItem("%DOOMWADDIR%");
#else
        ui->listWidget->addItem("$DOOMWADPATH");
        ui->listWidget->addItem(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom");

        ui->listWidget_3->addItem("$DOOMWADDIR");
        ui->listWidget_3->addItem(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom");
#endif
    ui->listWidget->item(0)->setFlags(QFlags<Qt::ItemFlag>());
    ui->listWidget->item(1)->setFlags(QFlags<Qt::ItemFlag>());

    ui->listWidget_3->item(0)->setFlags(QFlags<Qt::ItemFlag>());
    ui->listWidget_3->item(1)->setFlags(QFlags<Qt::ItemFlag>());

    size = settings.beginReadArray("pwadfolders");
    if(size!=0)
    {
        for (int i = 0; i < size; i++) {
            settings.setArrayIndex(i);
            if(settings.value("folder").toString()!="")
                ui->listWidget->addItem(settings.value("folder").toString());
        }
    }
    settings.endArray();

    size = settings.beginReadArray("iwadfolders");
    if(size!=0)
    {
        for (int i = 0; i < size; i++) {
            settings.setArrayIndex(i);
            if(settings.value("folder").toString()!="")
                ui->listWidget_3->addItem(settings.value("folder").toString());
        }
    }
    settings.endArray();

    ui->label_8->hide();
    ui->label_5->hide();
}

void Settings::fooo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_checkBox_clicked(bool checked)
{
    if(!checked)
    {
        #ifdef __APPLE__
        macSetToLightTheme();
        changeButtonColorS(false);
        #endif
        //#else
        //#endif
        QFile styleFile(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/Downloads/a.qss" );
        styleFile.open( QFile::ReadOnly );
        QString style( styleFile.readAll() );
        qApp->setStyleSheet( style );

        settings.setValue("theme","light");
        pmainWindow->changeButtonColor(false);
    }
    else
     {
        #ifdef __APPLE__
        macSetToDarkTheme();
        changeButtonColorS(true);
        #endif

        qApp->setStyleSheet("* {background: rgb(53, 53, 53);color: rgb(221, 221, 221);}"
                            "QLabel {border: none; margin: 0px}"
                            "QPushButton {border: 1px solid rgb(120, 120, 120); text-align:center; border-radius:5px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                            "QPushButton:pressed {border: 1px solid rgb(120, 120, 120); text-align:center; border-radius:5px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}"
                            "QCheckBox {spacing: 4px;border: none;}"
                            "QRadioButton {spacing: 4px;border: none;}"
                            "QTabWidget {background: rgb(45, 45, 45); border: none}"
                            "QTabWidget::pane {top: -1px;margin: 0px;padding: 0px;border: 1px solid rgb(79, 79, 79);}"
                            "QTabBar {qproperty-drawBase: 0;border: none;}"
                            "QTabBar::tab {padding-left: 5px;padding-right: 5px;padding-bottom: 4px;padding-top: 3px;min-width: 8ex;border-right: 1px solid rgb(79, 79, 79);border-left: 1px solid rgb(79, 79, 79);}"
                            "QTabBar::tab::top:!selected:hover {background-color: rgb(50, 50, 50)}"
                            "QTabBar::tab::selected {background: rgb(53, 53, 53); margin-left: -3px;margin-right: -3px;border-top: 1px solid rgb(79, 79, 79);border-bottom:none;}"
                            "QTabBar::tab:!selected {margin-top: 4px;background: rgb(47, 47, 47);border-top: 1px solid rgb(79, 79, 79);border-bottom: 1px solid rgb(79, 79, 79);}"
                            "QTabBar::tab:first:selected {margin-left: 0;}"
                            "QTabBar::tab:last:selected {margin-right: 0;}"
                            "QComboBox {border: 1px solid rgb(79, 79, 79);}"
                            "QComboBox::drop-down {margin: 5px; padding-left: 12px; height: 12px; width: 12px; image: url(\":/pngs/pngs/combo_box_arrow.png\");}"
                            "QGroupBox {border: 1px solid rgb(79, 79, 79);}"
                            "QComboBox:hover {border: 1px solid rgb(4,93,244); background-color: rgb(55,63,76)}"
                            "QComboBox:on {border: 1px solid rgb(4,93,244); background-color: rgb(43,69,94); selection-background-color:rgb(43,69,94)}"
                            "QComboBox:focus {border: 1px solid rgb(79, 79, 79); background: rgb(53, 53, 53);}"
                            "QCheckBox::indicator:unchecked:hover {background-color: rgb(240,240,240); border-radius: 3px}"
                            "QMenuBar::item:selected {background: rgb(43,43,43)}"
                            "QMenuBar::item:pressed {background: rgb(43,43,43)}"
                            "QMenu {border: 1px solid rgb(79, 79, 79)}"
                            "QMenu::item:selected {background-color: rgb(55,63,76)}"
                            );

        //#endif
        settings.setValue("theme","dark");
        pmainWindow->changeButtonColor(true);
    }
}


void Settings::on_toolButton_2_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select PWAD folder"),"~/",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(dirName!="")
    {
        ui->listWidget->addItem(dirName);
    }

    settings.beginWriteArray("pwadfolders");
    for (int i = 2; i < ui->listWidget->count(); i++) {
        settings.setArrayIndex(i-2);
        settings.setValue("folder", ui->listWidget->item(i)->text());
    }
    settings.endArray();
}

void Settings::on_toolButton_3_clicked()
{
    if(ui->listWidget->count()>2 && ui->listWidget->currentRow()>1)
        ui->listWidget->takeItem(ui->listWidget->currentRow());

    settings.beginWriteArray("pwadfolders");
    for (int i = 2; i < ui->listWidget->count(); i++) {
        settings.setArrayIndex(i-2);
        settings.setValue("folder", ui->listWidget->item(i)->text());
    }
    settings.endArray();
}


void Settings::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1!="")
    {
        settings.setValue("maxskilllevel",arg1.toInt());
        pmainWindow->changeMaxSkillLevel(arg1.toInt());
    }
}


void Settings::on_radioButton_toggled(bool checked)
{
    if(checked)
    {
        settings.setValue("complevels", 0);
        pmainWindow->changeComplevelsList(0);
    }
}


void Settings::on_radioButton_3_toggled(bool checked)
{
    if(checked)
    {
        settings.setValue("complevels", 1);
        pmainWindow->changeComplevelsList(1);
    }
}


void Settings::on_toolButton_5_clicked()
{
    if(ui->listWidget_2->count()>0)
        ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
    settingsChanged();

}



void Settings::on_toolButton_4_clicked()
{
    ui->listWidget_2->insertItem(0,"");
    ui->listWidget_2->item(0)->setFlags(QFlags<Qt::ItemFlag>(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled));
    ui->listWidget_2->scrollToTop();
    ui->listWidget_2->setCurrentRow(0);
    settingsChanged();
}


void Settings::on_listWidget_2_itemChanged(QListWidgetItem *item)
{
    settingsChanged();
}

void Settings::on_toolButton_6_clicked()
{
    if(ui->listWidget_2->currentRow()!=0)
    {
        int row = ui->listWidget_2->currentRow();
        QListWidgetItem *item = ui->listWidget_2->takeItem(row);
        ui->listWidget_2->insertItem(row-1,item);
        ui->listWidget_2->setCurrentRow(row-1);
        settingsChanged();
    }
}


void Settings::on_toolButton_7_clicked()
{
    if(ui->listWidget_2->currentRow()!=ui->listWidget_2->count()-1)
    {
        int row = ui->listWidget_2->currentRow();
        QListWidgetItem *item = ui->listWidget_2->takeItem(row);
        ui->listWidget_2->insertItem(row+1,item);
        ui->listWidget_2->setCurrentRow(row+1);
        settingsChanged();
    }
}

void Settings::closeEvent(QCloseEvent *event) // When closing the launcher, save the settings
{

}


void Settings::on_toolButton_clicked()
{
    ui->textBrowser->setVisible(!ui->textBrowser->isVisible());
}


void Settings::on_lineEdit_2_textChanged(const QString &arg1)
{
    settingsChanged();
    if(arg1=="")
    {
        ui->lineEdit_2->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_2->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
}


void Settings::on_pushButton_clicked()
{
    ui->label_5->hide();
    ui->label_8->show();

    pmainWindow->changeResolutions(ui->listWidget_2);

    pmainWindow->changeToggles(ui->lineEdit_3->text(),ui->lineEdit_5->text(),ui->lineEdit_4->text(),ui->lineEdit_6->text(),ui->lineEdit_7->text(),ui->lineEdit_9->text(),ui->lineEdit_8->text(),ui->lineEdit_10->text());

    if (ui->lineEdit_2->text()=="")
    {
        pmainWindow->changeExeName("dsda-doom");
    }
    else
    {
        pmainWindow->changeExeName(ui->lineEdit_2->text());
    }

    settings.setValue("toggle1t", ui->lineEdit_3->text());
    settings.setValue("toggle1a", ui->lineEdit_5->text());

    settings.setValue("toggle2t", ui->lineEdit_4->text());
    settings.setValue("toggle2a", ui->lineEdit_6->text());

    settings.setValue("toggle3t", ui->lineEdit_7->text());
    settings.setValue("toggle3a", ui->lineEdit_9->text());

    settings.setValue("toggle4t", ui->lineEdit_8->text());
    settings.setValue("toggle4a", ui->lineEdit_10->text());

    settings.beginWriteArray("resolutions");
    for (int i = 0; i < ui->listWidget_2->count(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("res", ui->listWidget_2->item(i)->text());
    }
    settings.endArray();
}


void Settings::on_lineEdit_3_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_3->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_3->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settingsChanged();
}


void Settings::on_lineEdit_5_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_5->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_5->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settingsChanged();
}


void Settings::on_lineEdit_4_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_4->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_4->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settingsChanged();
}


void Settings::on_lineEdit_6_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_6->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_6->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settingsChanged();
}


void Settings::on_lineEdit_7_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_7->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_7->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settingsChanged();
}


void Settings::on_lineEdit_8_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_8->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_8->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settingsChanged();
}


void Settings::on_lineEdit_9_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_9->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_9->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settingsChanged();
}


void Settings::on_lineEdit_10_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_10->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_10->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settingsChanged();
}

void Settings::settingsChanged()
{
    ui->label_8->hide();
    ui->label_5->show();
}

void Settings::on_lineEdit_11_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        ui->lineEdit_11->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(150, 150, 150); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    else
    {
        ui->lineEdit_11->setStyleSheet("border: 1px solid rgb(180, 180, 180); padding-left: 6px;height: 20px; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border-radius:3px");
    }
    settings.setValue("maxhistory", arg1);
}


void Settings::on_toolButton_9_clicked()
{
    ui->textBrowser_2->setVisible(!ui->textBrowser_2->isVisible());
}


void Settings::on_toolButton_10_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select IWAD folder"),"~/",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(dirName!="")
    {
        ui->listWidget_3->addItem(dirName);
    }

    settings.beginWriteArray("iwadfolders");
    for (int i = 2; i < ui->listWidget_3->count(); i++) {
        settings.setArrayIndex(i-2);
        settings.setValue("folder", ui->listWidget_3->item(i)->text());
    }
    settings.endArray();
}


void Settings::on_toolButton_8_clicked()
{
    if(ui->listWidget_3->count()>2 && ui->listWidget_3->currentRow()>1)
        ui->listWidget_3->takeItem(ui->listWidget_3->currentRow());

    settings.beginWriteArray("iwadfolders");
    for (int i = 2; i < ui->listWidget_3->count(); i++) {
        settings.setArrayIndex(i-2);
        settings.setValue("folder", ui->listWidget_3->item(i)->text());
    }
    settings.endArray();
}

