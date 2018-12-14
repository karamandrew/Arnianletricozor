#include "introwindow.h"
#include "ui_introwindow.h"
#include "mainwindow.h"
//#include"Gameobject.h"
//#include "game.h"
#include <QApplication>
#include <QHBoxLayout>
//#include "player.h"
IntroWindow::IntroWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IntroWindow)
{
    ui->setupUi(this);
}

IntroWindow::~IntroWindow()
{
    delete ui;
}

void IntroWindow::setWindow(MainWindow *window)
{
    main = window;
}



void IntroWindow::on_pushButton_clicked()
{
    main->setUp(1);
    main->show();
    this->close();
}

void IntroWindow::on_pushButton_2_clicked()
{
    main->setUp(2);
    main->show();
    this->close();
}

void IntroWindow::on_pushButton_3_clicked()
{
    main->setUp(3);
    main->show();
    this->close();
}
