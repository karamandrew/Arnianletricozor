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
    int getDamageDone(Unite a, Unite d);
    int getmapId(int x, int y);
    Unite* getUnite(int x, int y);
    void calculatePosAccessible(int Xfoc, int Yfoc, int indexUnit, int mp);
    bool isThereAnotherUnite(int x, int y);
    void setMapObjectfalse();
    void setTurn();
    void turnChange();
    void setUnitefocusedfalse();
    int attack(Unite* a, Unite* d);
    int calculDegat(Unite* u, Unite* v);
    Unite* Enemyclose(Unite* unit);
    ~Game();
private:
    Game();
    static Game gInstance;
    MainWindow *window;
    vector<Unite*> unite;
    //vector<Unite*> unite;
    int Xfoc=-1;
    int Yfoc=-1;
    bool activeTurn=true;


};
#endif // GAME_H
