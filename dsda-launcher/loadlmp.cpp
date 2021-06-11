#include "loadlmp.h"
#include "ui_loadlmp.h"

loadLMP::loadLMP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loadLMP)
{
    ui->setupUi(this);
}

loadLMP::~loadLMP()
{
    delete ui;
}
