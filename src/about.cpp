#include "about.h"
#include "ui_about.h"
#include <mainwindow.h>

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    // Keyboard shortcut
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS

    // Closes the active window
    QShortcut *shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL), this, SLOT(close()));
    shortcut3->setAutoRepeat(false);

    ui->about_version_label->setText("DSDA-Launcher " + version);

    #if defined Q_OS_MACOS
        ui->about_version_label->setStyleSheet("QLabel {  font-size:18pt; font-weight:700; }");
 
    #elif defined Q_OS_WIN
        ui->about_version_label->setStyleSheet("QLabel {  font-size:11pt; font-weight:700; }");
 
    #else
        ui->about_version_label->setStyleSheet("QLabel {  font-size:10pt; font-weight:700; }");
    #endif
}

About::~About()
{
    delete ui;
}

void About::on_dsda_launch_pushButton_clicked() { QDesktopServices::openUrl(QUrl("https://github.com/Pedro-Beirao/dsda-launcher")); }

void About::ctrlw() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}
