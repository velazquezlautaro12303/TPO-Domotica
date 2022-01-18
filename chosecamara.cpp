#include "chosecamara.h"
#include "ui_chosecamara.h"

ChoseCamara::ChoseCamara(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChoseCamara)
{
    ui->setupUi(this);
}

ChoseCamara::~ChoseCamara()
{
    delete ui;
}
