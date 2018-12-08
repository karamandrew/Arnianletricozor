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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::redraw()
{
    map->setmapobject();

    map->redraw();
}

Gameobject& MainWindow::getMapObject(int i, int j)
{
    return map->getmapObject(i,j);
}
