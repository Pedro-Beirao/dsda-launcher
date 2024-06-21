#ifndef STATES_H
#define STATES_H

#include <QCheckBox>
#include <QLineEdit>
#include <QObject>
#include <QTextStream>

class states : public QObject
{
    Q_OBJECT
  public:
    explicit states(QObject *parent = nullptr);
    static void loadStateFromFile(QString filePath);
    static void loadStateFromString(QString string);
    static void saveStateToFile(QString filePath);
    static void loadStateOld(QTextStream &stream);
    static void loadStateNew(QTextStream &stream);

  signals:
};

#endif // STATES_H
