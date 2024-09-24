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
  std::unordered_map<QString, QString> colors = {
      {"0m", "#000000"}, // Black
      {"1m", "#aa0000"}, // Red
      {"2m", "#00aa00"}, // Green
      {"3m", "#aa5500"}, // Yellow
      {"4m", "#0000aa"}, // Blue
      {"5m", "#aa00aa"}, // Magenta
      {"6m", "#00aaaa"}, // Cyan
      {"7m", "#aaaaaa"}, // White
      {"8m", "white"},   //
      {"9m", "white"},   //

      {"0;", "#555555"},   // Bright Black
      {"1;", "#ff5555 "},  // Bright Red
      {"2;", "#55ff55"},   // Bright Green
      {"3;", "#ffff55"},   // Bright Yellow
      {"4;", "#5555ff"},   // Bright Blue
      {"5;", "#ff55ff"},   // Bright Magenta
      {"6;", "#55ffff"},   // Bright Cyan
      {"7;", "#ffffff"},   // Bright White
      {"8;", "lightgray"}, //
      {"9;", "white"},     //
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
