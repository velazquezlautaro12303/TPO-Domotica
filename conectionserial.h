#ifndef CONECTIONSERIAL_H
#define CONECTIONSERIAL_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class ConectionSerial;
}

class ConectionSerial : public QWidget
{
    Q_OBJECT

    public:
        explicit ConectionSerial(QWidget *parent = nullptr);
        ~ConectionSerial();

    private:
        Ui::ConectionSerial *ui;
        QString portName;
        QSerialPort *port;
        void EnumerarPuertos();
};

#endif // CONECTIONSERIAL_H
