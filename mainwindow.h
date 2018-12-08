#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QMainWindow>
#include"gameobject.h"
#include "map.h"
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
    Gameobject& getMapObject(int i, int j);

private:
    Ui::MainWindow *ui;
    Map *map;

};

#endif // MAINWINDOW_H
