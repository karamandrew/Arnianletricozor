#ifndef MAP_H
#define MAP_H
#include <QWidget>
#include"gameobject.h"
class Map : public QWidget{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = 0) ;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void setmapobject();
    void redraw();
    Gameobject& getmapObject(int i, int j);
    ~Map();
private:
    Gameobject  *mapObject[21][17];

};
#endif // MAP_H
