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



void DialogBuyAir::getInfo(int x, int y, bool value){
    m_x = x;
    m_y = y;
    m_value = value;
}

void DialogBuyAir::on_pushButton_clicked()
{
    this->close();
}


void DialogBuyAir::on_pushButton_2_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 1);
    this->close();
}

void DialogBuyAir::on_pushButton_3_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 2);
    this->close();
}

void DialogBuyAir::on_pushButton_4_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 3);
    this->close();
}


