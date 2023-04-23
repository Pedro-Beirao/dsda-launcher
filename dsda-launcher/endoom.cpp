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
    QShortcut * shortcut3 = new QShortcut(QKeySequence(Qt::Key_W | Qt::CTRL),this,SLOT(fooo3()));
    shortcut3->setAutoRepeat(false);

    ui->endoom_textEdit->setReadOnly(true);
}

endoom::~endoom()
{
    delete ui;
}

void endoom::changeText(QString s)
{
    ui->endoom_textEdit->append(s);
}

void endoom::clearText()
{
    ui->endoom_textEdit->setPlainText("");
}


void endoom::fooo3() // CTRL+W runs this function close the active window
{
    QWidget *currentWindow = QApplication::activeWindow();
    currentWindow->close();
}

void endoom::showEndoom(QString qs)
{
    QRegularExpression regex("\033");
    QStringList qsl = qs.split(regex);

    QString ret;

    int col = 0;

    for (int i = 0; i < qsl.size() - 3; i++)
    {
        if (qsl[i].size() < 4 || qsl[i][1] != '3') continue;
        QString foreground = colors[qsl[i][2]];

        i++;
        if (qsl[i].size() < 4 || qsl[i][1] != '4') continue;
        QString background = colors[qsl[i][2]];

        i++;
        if (qsl[i].size() < 3) continue;
        QString character = qsl[i][qsl[i].size()-1];

        i++;
        if (character == " ") character = "&nbsp;";

        ret.append("<span style='color: " + foreground + ";background-color: " + background + ";'>" + character + "</span>");

        col++;
        if (col >= 80)
        {
            ret.append("<span><br/></span>");
            col = 0;
        }
    }
    ui->endoom_textEdit->append(ret);
}

void endoom::on_endoom_textEdit_textChanged()
{
    QSize size = ui->endoom_textEdit->document()->size().toSize();

    ui->endoom_textEdit->setFixedHeight( size.height() + 10);
    ui->endoom_textEdit->setFixedWidth( size.width() + 10);

    setFixedSize(size);
}

