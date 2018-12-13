#include "dialoglanguage.h"
#include "ui_dialoglanguage.h"

DialogLanguage::DialogLanguage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLanguage)
{
    ui->setupUi(this);
}

DialogLanguage::~DialogLanguage()
{
    delete ui;
}
