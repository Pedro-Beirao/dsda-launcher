#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <qsettings.h>
#include <mainwindow.h>


Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    if(ui->checkBox->isChecked())
    {
        ui->lineEdit->setReadOnly(true);
    }

    ui->restartWarning->hide();
}

Settings::~Settings()
{
    delete ui;
}

QString Settings::getIWADsPath()
{
    if(ui->checkBox->isChecked())
    {
        return QCoreApplication::applicationDirPath();
    }
    else
    {
        return ui->lineEdit->text();
    }
}

void Settings::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit->setStyleSheet("color: rgb(139, 139, 139);");
    }
    else
    {
        ui->lineEdit->setReadOnly(false);
        ui->lineEdit->setStyleSheet("");
    }
}


void Settings::on_pushButton_clicked()
{
    if(!ui->checkBox->isChecked())
    {
        QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Select the IWADs folder path"),"/",tr("Folder (*.wad)"));
        if(fileName.size()>0)
        {
            std::string iwadPath = fileName[0].toStdString();
            std::size_t found = iwadPath.find_last_of("/\\");
            ui->lineEdit->setText(iwadPath.substr(0,found).c_str());
        }
    }
}


void Settings::on_pushButton_2_clicked()
{
    settings.setValue("iwadspath",getIWADsPath());

    ui->restartWarning->show();
}

