#ifndef RIEL_H
#define RIEL_H

#include <QWidget>
#include <QRadioButton>
#include "serialterminal.h"

class Riel : public QWidget
{
    Q_OBJECT
private:
    QRadioButton *arriba;
    QRadioButton *abajo;
public:
    explicit Riel(SerialTerminal &connectionSerial, QWidget *parent = nullptr);

signals:

};

#endif // RIEL_H
