#include "dialogbuyterre.h"
#include "ui_dialogbuyterre.h"
#include "game.h"

DialogBuyTerre::DialogBuyTerre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBuyTerre)
{
    ui->setupUi(this);
}

DialogBuyTerre::~DialogBuyTerre()
{
    delete ui;
}

void DialogBuyTerre::on_spinBox_valueChanged(int arg1)
{
    m_unitWanted = arg1;
}



void DialogBuyTerre::getInfo(int x, int y, bool value){
    m_x = x;
    m_y = y;
    m_value = value;
}

void DialogBuyTerre::on_spinBox_editingFinished()
{
    Game& game = Game::Instance();
    if (m_unitWanted != 0){
        this->close();
        game.createUnit( m_x, m_y, m_type, m_value, m_unitWanted);
    }
}
