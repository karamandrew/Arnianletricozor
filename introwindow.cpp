#include "introwindow.h"
#include "ui_introwindow.h"

IntroWindow::IntroWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntroWindow)
{
    ui->setupUi(this);
}

IntroWindow::~IntroWindow()
{
    delete ui;
}
