#include "orangestarwin.h"
#include "ui_orangestarwin.h"

OrangeStarWin::OrangeStarWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrangeStarWin)
{
    ui->setupUi(this);
}

OrangeStarWin::~OrangeStarWin()
{
    delete ui;
}
