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

void DialogBuyTerre::getInfo(int x, int y, bool value){
    m_x = x;
    m_y = y;
    m_value = value;
}


void DialogBuyTerre::on_pushButton_clicked()
{
    this->close();
}

void DialogBuyTerre::on_pushButton_2_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 1);
    this->close();
}

void DialogBuyTerre::on_pushButton_3_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 2);
    this->close();
}

void DialogBuyTerre::on_pushButton_4_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 3);
    this->close();
}

void DialogBuyTerre::on_pushButton_5_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 4);
    this->close();
}

void DialogBuyTerre::on_pushButton_6_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 5);
    this->close();
}

void DialogBuyTerre::on_pushButton_7_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 6);
    this->close();
}

void DialogBuyTerre::on_pushButton_8_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 7);
    this->close();
}

void DialogBuyTerre::on_pushButton_9_clicked()
{
    Game& game = Game::Instance();
    game.createUnit( m_x, m_y, m_type, m_value, 8);
    this->close();
}
