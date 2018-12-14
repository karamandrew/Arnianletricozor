#include "bluemoonwin.h"
#include "ui_bluemoonwin.h"

BlueMoonWin::BlueMoonWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlueMoonWin)
{
    ui->setupUi(this);
}

BlueMoonWin::~BlueMoonWin()
{
    delete ui;
}
