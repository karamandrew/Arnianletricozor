#ifndef GAME_H
#define GAME_H
#include "mainwindow.h"
#include "unite.h"


class Game{
public:
    static Game& Instance();
    void move(QMouseEvent *e);
    void start(MainWindow &wind);
    int getIndexUnit(int x, int y);
    int getMalusMove(char moveType, int terrainID);

    Unite getUnite(int x, int y);
    void calculatePosAccessible(int Xfoc, int Yfoc, int indexUnit);
private:
    Game();
    static Game gInstance;
    MainWindow *window;
    vector<Unite> unite;
    int Xfoc=0;
    int Yfoc=0;


};
#endif // GAME_H
