#include "timer.h"

timer::timer(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer();
    m_timer->start(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Sequence()));
}

void timer::Sequence()
{
    static bool state = false;

    if(!state)
    {
        foreach (QTreeWidgetItem* var, listaItem) {
            var->setBackgroundColor(0, QColor::fromRgb(255,0,0));
        }
        state = true;
    }
    else
    {
        foreach (QTreeWidgetItem* var, listaItem) {
            var->setBackgroundColor(0, QColor::fromRgb(255,255,255));
        }
        state = false;
    }
}

void timer::addItem(QTreeWidgetItem*& item)
{
    listaItem.append(item);
}

void timer::removeItem(QTreeWidgetItem* item)
{
    item->setBackgroundColor(0, QColor::fromRgb(255,255,255));
    listaItem.removeOne(item);
}
