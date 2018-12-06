#ifndef MAP_H
#define MAP_H
#include <QWidget>
#include"Gameobject.h"
class Map : public QWidget{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = 0) ;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void setgameobject();
    void redraw();
    Gameobject getmapObject(int i, int j);
private:
    Gameobject mapObject[11][11];

};
#endif // MAP_H
