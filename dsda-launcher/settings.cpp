#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    if(ui->checkBox->isChecked())
    {
        ui->lineEdit->setReadOnly(true);
    }
}

Settings::~Settings()
{
    delete ui;
}

QString Settings::getDsdaDoomPath()
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
        QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Select dsda-doom folder path path"),"/",tr("Folder (*)"));
        if(fileName.size()>0)
            ui->lineEdit->setText(fileName[0]);
    }
}

