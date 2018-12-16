#include "dialognewgame.h"
#include "ui_dialognewgame.h"

#include "game.h"

DialogNewGame::DialogNewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewGame)
{
    ui->setupUi(this);
}

DialogNewGame::~DialogNewGame()
{
    delete ui;
}

void DialogNewGame::on_pushButton_clicked()
{
    Game& game = Game::Instance();
    game.restart(1);
    this->close();
}

void DialogNewGame::on_pushButton_2_clicked()
{
    Game& game = Game::Instance();
    game.restart(2);
    this->close();
}

void DialogNewGame::on_pushButton_3_clicked()
{
    Game& game = Game::Instance();
    game.restart(3);
    this->close();
}

void DialogNewGame::on_pushButton_4_clicked()
{
    Game& game = Game::Instance();
    game.restart(4);
    this->close();
}
