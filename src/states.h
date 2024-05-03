#ifndef STATES_H
#define STATES_H

#include <QObject>
#include <QLineEdit>
#include <QCheckBox>

class states : public QObject
{
    Q_OBJECT
public:
    explicit states(QObject *parent = nullptr);
    static void LoadState(QString fileName, bool isString);
    static void SaveState(QString fileName);

signals:

};

#endif // STATES_H
