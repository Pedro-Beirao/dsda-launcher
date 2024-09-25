#include "endoom.h"
#include "ui_endoom.h"

endoom::endoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::endoom)
{
    ui->setupUi(this);

    // Keyboard shortcut
    // Qt::CTRL is the CTRL key for Windows/Linux and is the CMD key for MacOS

    // Closes the active window
    QShortcut *shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL), this, SLOT(close()));
    shortcut3->setAutoRepeat(false);

    ui->endoom_textEdit->setReadOnly(true);
}

endoom::~endoom()
{
    delete ui;
}
void endoom::showEndoom(QString consoleOutput)
{
    ui->endoom_textEdit->setText("");

    QStringList qsl = consoleOutput.split("\033[0m");

    QString ret;

    int col = 0;
    ret.append("<table cellspacing='0' cellpadding='0'><tr>");

    for (int i = 0; i < qsl.size(); i++)
    {
        QStringList cs = qsl[i].split("\033");

        QString character = cs.last()[cs.last().size() - 1];

        QString foreground, background;
        for (int j = 0; j < cs.size() - 1; j++)
        {
            if (cs[j].size() < 4) continue;
            if (cs[j][1] == '3') foreground = colors[cs[j].mid(2, 2)];
            if (cs[j][1] == '4') background = colors[cs[j].mid(2, 2)];
        }

        if (character == " ") character = "&nbsp;";

        ret.append("<td style='color: " + foreground + ";background-color: " + background + "; padding: 0px;'>" + character + "</td>");

        col++;
        if (col >= 80)
        {
            ret.append("</tr><tr>");
            col = 0;
        }
    }
    ret.append("</tr></table>");

    ui->endoom_textEdit->append(ret);
}

void endoom::on_endoom_textEdit_textChanged()
{
    QSize size = ui->endoom_textEdit->document()->size().toSize();

    ui->endoom_textEdit->setFixedHeight(size.height() + 10);
    ui->endoom_textEdit->setFixedWidth(size.width() + 10);

    setFixedSize(size);
}

