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

void Settings::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        ui->lineEdit->setReadOnly(true);
    }
    else
    {
        ui->lineEdit->setReadOnly(false);
    }
}


void Settings::on_pushButton_clicked()
{
    QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Select dsda-doom folder path path"),"/",tr("Folder (*)"));
    ui->lineEdit->setText(fileName[0]);
}

