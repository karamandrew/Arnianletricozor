#include "dialogbuyair.h"
#include "ui_dialogbuyair.h"
#include "game.h"

DialogBuyAir::DialogBuyAir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBuyAir)
{
    ui->setupUi(this);
}

DialogBuyAir::~DialogBuyAir()
{
    delete ui;
}

void DialogBuyAir::on_spinBox_valueChanged(int arg1)
{
    m_unitWanted = arg1;
}


void DialogBuyAir::getInfo(int x, int y, bool value){
    m_x = x;
    m_y = y;
    m_value = value;
}

void DialogBuyAir::on_spinBox_editingFinished()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, m_unitWanted);
    this->close();

}
