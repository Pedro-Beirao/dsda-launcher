#include "documentation.h"
#include "ui_documentation.h"

documentation::documentation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::documentation)
{
    ui->setupUi(this);
}

documentation::~documentation()
{
    delete ui;
}
