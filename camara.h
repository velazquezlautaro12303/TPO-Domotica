/**
 * @file camara.h
 * @version 1.0
 * @date 10/09/2021
 */

#ifndef CAMARA_H
#define CAMARA_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include "myvideocapture.h"
#include "serialterminal.h"
#include <QTreeWidgetItem>
#include "timer.h"

class Camara : public QWidget
{
    Q_OBJECT
    public:
        explicit Camara(QTreeWidgetItem *&_item, SerialTerminal &connectionSerial, timer &_timer, int id_camara = 1, QWidget *parent = nullptr);
        MyVideoCapture* mOpenCV_videoCapture;

    private:
        QLabel* camara;
        QTreeWidgetItem *item;
    signals:
        void sendItem(QTreeWidgetItem*&);
    private slots:
        void setPixmap();
        void Expand();
};

#endif // CAMARA_H
