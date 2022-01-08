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

// Find the name of the OS
std::string getOsNameS()
{
    #ifdef _WIN32
    return "Windows";
    #elif _WIN64
    return "Windows";
    #elif __APPLE__ || __MACH__
    return "MacOS";
    #else
    return "Linux";
    #endif
}

MainWindow * pmainWindow;

void Settings::changeButtonColorS(bool isDark)
{
    if(isDark && getOsNameS()=="MacOS")
    {
        ui->toolButton->setStyleSheet("QPushButton{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(50, 50, 50); color: rgb(150, 150, 150)}"
                                        "QPushButton:pressed{border: 1px solid rgb(120, 120, 120); border-radius:7px; background-color: rgb(75, 75, 75); color: rgb(150, 150, 150)}");
    }
    else if(getOsNameS()=="MacOS")
    {
        ui->toolButton->setStyleSheet("QPushButton{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(240,240,240); color: rgb(13,13,13)}"
                                        "QPushButton:pressed{border: 1px solid rgb(180, 180, 180); border-radius:7px; background-color: rgb(223,223,223); color: rgb(13,13,13)}");
    }
}

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    pmainWindow = MainWindow::getMainWin();

    if(settings.value("theme")=="light")
    {
        ui->checkBox->setChecked(false);
        on_checkBox_clicked(false);
    }
    else
    {
        ui->checkBox->setChecked(true);
        on_checkBox_clicked(true);
    }

    if(getOsNameS()=="MacOS")
    {
        QFont font = ui->label_2->font();
        font.setPixelSize(13);
        ui->label_2->setFont(font);
        font.setPixelSize(11);
        ui->label_3->setFont(font);
        ui->listWidget->clear();
        ui->listWidget->addItem(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.dsda-doom");
    }
    else
    {
        ui->textBrowser->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">When droping .lmp files into the launcher, it autoselects the correct IWAD, PWADs and complevel.</span></p><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">For this to work, you need to add the folders you have your PWADs in, to the following container.</span></p></body></html>");
    }

    ui->textBrowser->setVisible(false);

    if(settings.value("complevels").toString()=="")
    {
        ui->radioButton_2->setChecked(true);
    }
    else if(settings.value("complevels").toInt()==0)
    {
        ui->radioButton->setChecked(true);
    }
    else if(settings.value("complevels").toInt()==1)
    {
        ui->radioButton_2->setChecked(true);
    }
    else if(settings.value("complevels").toInt()==2)
    {
        ui->radioButton_3->setChecked(true);
    }

    QRegularExpression rgx("[0-9]{1}");
    QValidator *comValidator = new QRegularExpressionValidator (rgx, this);
    ui->lineEdit->setValidator(comValidator);
    
    // Keyboard shortcuts
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS
    // Open the folder to add the IWADs
    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_O | Qt::CTRL),this,SLOT(fooo()));
    shortcut->setAutoRepeat(false);

    // Closes the active window
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);

    if(settings.value("maxskilllevel").toString()!="")
        ui->lineEdit->setText(settings.value("maxskilllevel").toString());

    int size = settings.beginReadArray("resolutions");
    if(size!=0)
    {
        ui->listWidget_2->clear();
        for (int i = 0; i < size; i++) {
            settings.setArrayIndex(i);
            ui->listWidget_2->addItem(settings.value("res").toString());
        }
    }
    settings.endArray();
    pmainWindow->changeResolutions(ui->listWidget_2);

    size = settings.beginReadArray("pwadfolders");
    if(size!=0)
    {
        for (int i = 0; i < size; i++) {
            settings.setArrayIndex(i);
            if(settings.value("folder").toString()!="" && settings.value("folder").toString()!=ui->listWidget->item(0)->text())
                ui->listWidget->addItem(settings.value("folder").toString());
        }
    }
    settings.endArray();
}

void Settings::fooo() // CTRL+O runs this function to open the folder where the IWADs should be placed in
{
    if(getOsNameS()=="MacOS"|| getOsNameS()=="Linux")
    {
        system(("open \""+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom\"").c_str());
    }
    else
    {
        QProcess::startDetached(("explorer \""+QCoreApplication::applicationDirPath().toStdString() + "\"").c_str());
    }
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
        #elif __WIN32__
                qApp->setStyle(QStyleFactory::create("Windowsvista"));
                QPalette lightPalette;
                qApp->setPalette(lightPalette);
        #else
                qApp->setStyle(QStyleFactory::create("Fusion"));
                QPalette lightPalette;
                qApp->setPalette(lightPalette);

        #endif
        settings.setValue("theme","light");
        pmainWindow->changeButtonColor(false);
        changeButtonColorS(false);
    }
    else
     {
        #ifdef __APPLE__
        macSetToDarkTheme();
        #else
        qApp->setStyle(QStyleFactory::create("Fusion"));
        QPalette darkPalette;
            darkPalette.setColor(QPalette::Window, QColor(53,53,53));
            darkPalette.setColor(QPalette::WindowText, Qt::white);
            darkPalette.setColor(QPalette::Base, QColor(25,25,25));
            darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
            darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
            darkPalette.setColor(QPalette::ToolTipText, Qt::white);
            darkPalette.setColor(QPalette::Text, Qt::white);
            darkPalette.setColor(QPalette::Button, QColor(53,53,53));
            darkPalette.setColor(QPalette::ButtonText, Qt::white);
            darkPalette.setColor(QPalette::BrightText, Qt::red);
            darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

            darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::HighlightedText, Qt::black);

            qApp->setPalette(darkPalette);
            qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
        #endif
        settings.setValue("theme","dark");
        pmainWindow->changeButtonColor(true);
        changeButtonColorS(true);
    }
}


void Settings::on_toolButton_2_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select PWAD folder"),"/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(dirName!="")
    {
        //std::string iwadPath = fileName[0].toStdString();
        //std::size_t found = iwadPath.find_last_of("/\\");
        ui->listWidget->addItem(dirName);
    }

    settings.beginWriteArray("pwadfolders");
    for (int i = 1; i < ui->listWidget->count(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("folder", ui->listWidget->item(i)->text());
        qDebug()<<ui->listWidget->item(i)->text();
    }
    settings.endArray();
}

void Settings::on_toolButton_3_clicked()
{
    if(ui->listWidget->count()>1 and ui->listWidget->currentRow()!=0)
        ui->listWidget->takeItem(ui->listWidget->currentRow());

    settings.beginWriteArray("pwadfolders");
    for (int i = 1; i < ui->listWidget->count(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("folder", ui->listWidget->item(i)->text());
    }
    settings.endArray();
}

void Settings::on_pushButton_clicked()
{
    if(getOsNameS()=="MacOS" || getOsNameS()=="Linux")
    {
        system(("open "+QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString()+"/.dsda-doom/dsda-launcher.json").c_str());
    }
    else
    {
        QProcess::startDetached(("notepad \""+QCoreApplication::applicationDirPath().toStdString() + "\\dsda-launcher.json\"").c_str());
    }
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


void Settings::on_radioButton_2_toggled(bool checked)
{
    if(checked)
    {
        settings.setValue("complevels", 1);
        pmainWindow->changeComplevelsList(1);
    }
}


void Settings::on_radioButton_3_toggled(bool checked)
{
    if(checked)
    {
        settings.setValue("complevels", 2);
        pmainWindow->changeComplevelsList(2);
    }
}


void Settings::on_toolButton_5_clicked()
{
    if(ui->listWidget_2->count()>1)
        ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
}



void Settings::on_toolButton_4_clicked()
{
    ui->listWidget_2->insertItem(0,"");
    ui->listWidget_2->item(0)->setFlags(QFlags<Qt::ItemFlag>(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled));
    ui->listWidget_2->scrollToTop();
    ui->listWidget_2->setCurrentRow(0);
}


void Settings::on_listWidget_2_itemChanged(QListWidgetItem *item)
{
    pmainWindow->changeResolutions(ui->listWidget_2);
}

void Settings::on_toolButton_6_clicked()
{
    if(ui->listWidget_2->currentRow()!=0)
    {
        int row = ui->listWidget_2->currentRow();
        QListWidgetItem *item = ui->listWidget_2->takeItem(row);
        ui->listWidget_2->insertItem(row-1,item);
        ui->listWidget_2->setCurrentRow(row-1);
        pmainWindow->changeResolutions(ui->listWidget_2);
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
        pmainWindow->changeResolutions(ui->listWidget_2);
    }
}

void Settings::closeEvent(QCloseEvent *event) // When closing the launcher, save the settings
{
    settings.beginWriteArray("resolutions");
    for (int i = 0; i < ui->listWidget_2->count(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("res", ui->listWidget_2->item(i)->text());
    }
    settings.endArray();
}


void Settings::on_toolButton_clicked()
{
    ui->textBrowser->setVisible(!ui->textBrowser->isVisible());
}

