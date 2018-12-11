#include "mainwindow.h"
#include "gameobject.h"
#include "game.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    map = new Map(this);
    MainWindow::setCentralWidget(map);

    changeTurnButton = new QPushButton("Change Turn", this);
          changeTurnButton->setGeometry(50,50, 100, 50);
        QObject::connect(changeTurnButton, SIGNAL(clicked()), this, SLOT(changeTurn()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMapObjects(){
    map->setmapobject();
}

void MainWindow::redraw()
{
    map->redraw();
}

Gameobject& MainWindow::getMapObject(int i, int j)
{
    return map->getmapObject(i,j);
}

void MainWindow::changeTurn()
{
    Game& game = Game::Instance();
    game.turnChange();
}
