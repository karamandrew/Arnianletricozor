#include "dialogunitprice.h"
#include "ui_dialogunitprice.h"

DialogUnitPrice::DialogUnitPrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUnitPrice)
{
    ui->setupUi(this);
}

DialogUnitPrice::~DialogUnitPrice()
{
    delete ui;
}
