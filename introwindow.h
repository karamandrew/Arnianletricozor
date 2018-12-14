#ifndef MENU_H
#define INTROWINDOW_H
#include "mainwindow.h"
#include <QMainWindow>

namespace Ui {
class IntroWindow;
}

class IntroWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IntroWindow(QWidget *parent = nullptr);
    ~IntroWindow();


    //MainWindow *getWindow() const;
    void setWindow(MainWindow *value);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::IntroWindow *ui;
    MainWindow *main;
};

#endif // INTROWINDOW_H
