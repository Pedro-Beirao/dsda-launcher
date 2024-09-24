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
    std::unordered_map<QString, QString> colors =
    {
        {"0m", "black"},
        {"1m", "darkred"},
        {"2m", "green"},
        {"3m", "yellow"},
        {"4m", "blue"},
        {"5m", "purple"},
        {"6m", "cyan"},
        {"7m", "whitesmoke"},
        {"8m", "gray"},
        {"9m", "white"},

        {"0;", "gray"},
        {"1;", "indianred "},
        {"2;", "lawngreen"},
        {"3;", "gold"},
        {"4;", "#6871ff"},
        {"5;", "magenta"},
        {"6;", "lightcyan"},
        {"7;", "white"},
        {"8;", "lightgray"},
        {"9;", "white"},
    };

public:
    explicit endoom(QWidget *parent = nullptr);
    ~endoom();

  public slots:
    void showEndoom(QString consoleOutput);

  private slots:
    void on_endoom_textEdit_textChanged();

  private:
    Ui::endoom *ui;
};

#endif // ENDOOM_H
