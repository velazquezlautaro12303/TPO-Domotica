/**
 * @file iluminacion.h
 * @version 1.0
 * @date 10/09/2021
 */

#ifndef ILUMICACION_H
#define ILUMICACION_H

#include <QWidget>
#include <QDial>
#include <QLabel>
#include <QProgressBar>
#include "serialterminal.h"

class Ilumicacion : public QWidget
{
    Q_OBJECT
    public:
        explicit Ilumicacion(SerialTerminal &connectionSerial, QWidget *parent = nullptr);

    private:
        QDial  *dial;
        QLabel *label_Ilumicaion;
        QProgressBar *progressBar;
    signals:

};

#endif // ILUMICACION_H

