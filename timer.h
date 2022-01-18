#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QTreeWidgetItem>

class timer : public QObject
{
    Q_OBJECT
    public:
        explicit timer(QObject *parent = nullptr);
    private:
        QTimer* m_timer;
        QList<QTreeWidgetItem*> listaItem;

    public slots:
        void Sequence();
        void addItem(QTreeWidgetItem*& item);
        void removeItem(QTreeWidgetItem* item);

signals:

};

#endif // TIMER_H
