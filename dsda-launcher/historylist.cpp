#include "historylist.h"
#include "ui_historylist.h"

historyList::historyList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::historyList)
{
    ui->setupUi(this);
}

historyList::~historyList()
{
    delete ui;
}
