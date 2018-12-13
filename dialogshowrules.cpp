#include "dialogshowrules.h"
#include "ui_dialogshowrules.h"

DialogShowRules::DialogShowRules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShowRules)
{
    ui->setupUi(this);
}

DialogShowRules::~DialogShowRules()
{
    delete ui;
}
