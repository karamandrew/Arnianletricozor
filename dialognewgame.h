#ifndef DIALOGNEWGAME_H
#define DIALOGNEWGAME_H

//#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class DialogNewGame;
}

class DialogNewGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewGame(QWidget *parent = nullptr);
    ~DialogNewGame();
   //void setWindow(MainWindow *value);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DialogNewGame *ui;
   // MainWindow *main;
};

#endif // DIALOGNEWGAME_H