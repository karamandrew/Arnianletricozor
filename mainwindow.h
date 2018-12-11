#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QMainWindow>
#include <QPushButton>
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

private:
    Ui::MainWindow *ui;
    Map *map;
    QPushButton *changeTurnButton = nullptr;

};

#endif // MAINWINDOW_H
