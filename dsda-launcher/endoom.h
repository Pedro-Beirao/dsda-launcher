#ifndef ENDOOM_H
#define ENDOOM_H

#include <QWidget>
#include <QShortcut>
#include <QRegularExpression>
#include <unordered_map>

namespace Ui {
class endoom;
}

class endoom : public QWidget
{
    Q_OBJECT

private:
    // I am still confussed with what doomwiki says about the colors
    std::unordered_map<QChar, QString> colors =
    {
        {'0', "black"},
        {'1', "darkred"},
        {'2', "green"},
        {'3', "yellow"},
        {'4', "blue"},
        {'5', "purple"},
        {'6', "cyan"},
        {'7', "whitesmoke"},
        {'8', "gray"},
        {'9', "lightblue"},
        {'A', "lightgreen"},
        {'B', "lightcyan"},
        {'C', "lightred"},
        {'D', "lightmagenta"},
        {'E', "yellow"},
        {'F', "white"},
    };

public:
    explicit endoom(QWidget *parent = nullptr);
    ~endoom();

public slots:
    void fooo3();
    void changeText(QString s);
    void clearText();
    void showEndoom(QString qs);

private slots:
    void on_endoom_textEdit_textChanged();

private:
    Ui::endoom *ui;
};

#endif // ENDOOM_H
