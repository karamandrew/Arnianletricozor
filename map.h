#ifndef MAP_H
#define MAP_H
#include <QWidget>
#include "gameobject.h"
#include "terrain.h"

class Map : public QWidget{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = 0) ;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void setmapobject();
    void redraw();
    Terrain& getmapObject(int i, int j);
    void reload();
    ~Map();
private:
    Terrain  *mapObject[21][17];

};
#endif // MAP_H
