#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include"gameobject.h"
#include "map.h"
#include "terrain.h"



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

private slots :
    void changeTurn();
    void showPrice();

private:
    Ui::MainWindow *ui;
    Map *map;
    QPushButton *changeTurnButton = nullptr;
    QPushButton *showUnitPriceButton = nullptr;
    QLabel *labelArnian = nullptr;

};

#endif // MAINWINDOW_H
