#include "mainwindow.h"
#include "gameobject.h"
#include "game.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <iostream>
#include "terrain.h"
#include "dialogunitprice.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    map = new Map(this);
    MainWindow::setCentralWidget(map);

    changeTurnButton = new QPushButton("Change Turn", this); // ui->changeTurnButton
          changeTurnButton->setGeometry(50,250, 100, 50);
        QObject::connect(changeTurnButton, SIGNAL(clicked()), this, SLOT(changeTurn()));

    labelArnian = new QLabel("Arnian Le Tricozor", this);
        labelArnian->setGeometry(20,20, 200, 200);

    showUnitPriceButton = new QPushButton("Show Units Prices", this);
        showUnitPriceButton->setGeometry(50, 450, 100, 50);
        QObject::connect(showUnitPriceButton, SIGNAL(clicked()), this, SLOT(showPrice()));
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

Terrain& MainWindow::getMapObject(int i, int j)
{
    return map->getmapObject(i,j);
}

void MainWindow::changeTurn()
{
    Game& game = Game::Instance();
    game.turnChange();
}

void MainWindow::showPrice(){
    priceDialog = new  DialogUnitPrice(this);
    priceDialog->show();
}








