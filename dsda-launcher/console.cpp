#include "console.h"
#include "ui_console.h"

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
}

Console::~Console()
{
    delete ui;
}

void Console::changeText(std::string s)
{
    QString previousText = ui->text->toPlainText();
    ui->text->setPlainText(previousText + s.c_str());
}

void Console::clearText()
{
    ui->text->setPlainText("");
}
