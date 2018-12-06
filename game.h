#ifndef GAME_H
#define GAME_H
#include "mainwindow.h"


class Game{
public:
    static Game& Instance();
    void move(QMouseEvent *e);
    void start(MainWindow &wind);
    int getplaceunit(int x, int y);
    Gameobject getgameobject(int x,int y);
private:
    Game();
    static Game gInstance;
    MainWindow *window;
    vector<Gameobject> units;
    Gameobject gameobject[21][21];
    int Xfoc=0;
    int Yfoc=0;
};
#endif // GAME_H
