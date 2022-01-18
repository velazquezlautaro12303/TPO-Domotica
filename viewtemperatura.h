#ifndef VIEWTEMPERATURA_H
#define VIEWTEMPERATURA_H

#include <QWidget>
#include <QLabel>

class ViewTemperatura : public QWidget
{
    Q_OBJECT
public:
    explicit ViewTemperatura(QWidget *parent = nullptr);
    void setTemp(QString cadena);
private:
    QLabel *label;
signals:

};

#endif // VIEWTEMPERATURA_H
