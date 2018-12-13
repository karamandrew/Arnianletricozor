#include "dialogshowcommands.h"
#include "ui_dialogshowcommands.h"

DialogShowCommands::DialogShowCommands(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShowCommands)
{
    ui->setupUi(this);
}

DialogShowCommands::~DialogShowCommands()
{
    delete ui;
}
