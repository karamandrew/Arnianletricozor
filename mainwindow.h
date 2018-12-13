#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include"gameobject.h"
#include "map.h"
#include "terrain.h"
#include "dialogunitprice.h"



class Gameobject;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void redraw();
    void createMapObjects();
    Terrain& getMapObject(int i, int j);
    void updateMoneyTeam(int teamT, int teamF);
    void updateTurn(bool turn);

private slots :
    void changeTurn();
    void showPrice();

private:
    Ui::MainWindow *ui;
    DialogUnitPrice *priceDialog;
    Map *map;
    QPushButton *changeTurnButton = nullptr;
    QPushButton *showUnitPriceButton = nullptr;
    QLabel* labelArnian = nullptr;
    bool m_turn;
    QLabel* labelMoneyT = nullptr;
    QLabel* labelMoneyF = nullptr;

};

#endif // MAINWINDOW_H
