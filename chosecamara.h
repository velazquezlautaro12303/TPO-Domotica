#ifndef CHOSECAMARA_H
#define CHOSECAMARA_H

#include <QWidget>

namespace Ui {
class ChoseCamara;
}

class ChoseCamara : public QWidget
{
    Q_OBJECT

    public:
        explicit ChoseCamara(QWidget *parent = nullptr);
        ~ChoseCamara();

    private:
        Ui::ChoseCamara *ui;
};

#endif // CHOSECAMARA_H
