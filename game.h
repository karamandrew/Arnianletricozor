#ifndef GAME_H
#define GAME_H
#include "mainwindow.h"
#include "unite.h"

#include "dialogbuyterre.h"
#include "dialogbuyair.h"


class Game{
public:
    static Game& Instance();

    void move(QMouseEvent *e);
    void selectUnits(QMouseEvent *e);
    void attack(QMouseEvent *e);

    void start(MainWindow &wind);

    int getIndexUnit(int x, int y);
    int getMalusMove(char moveType, int terrainID);
    int getmapId(int x, int y);
    Unite* getUnite(int x, int y);
    bool isThereAnotherUnite(int x, int y);

    void setMapObjectfalse();
    void setTurn();
    void setUnitefocusedfalse();

    void calculatePosAccessible(int Xfoc, int Yfoc, int indexUnit, int mp);
    int attackChart(Unite* a, Unite* d);
    double calculDegat(Unite* u, Unite* v);
    bool Enemyclose(Unite* unit);
    void turnChange();



    void createUnit(int x, int y, char type, bool team, int unitWanted);
    void updateMoneyTeam(bool team);
    void setMoney(bool team, int impact);

    ~Game();

private:

    Game();
    static Game gInstance;

    MainWindow *window;

    vector<Unite*> unite;

    int Xfoc = -1;
    int Yfoc = -1;

    bool activeTurn=false;

    int moneyTeamF = 0;  // Blue
    int moneyTeamT = 0; // Orange

    DialogBuyTerre *diaBuyTerreOS;
    DialogBuyAir *diaBuyAirOS;
    DialogBuyTerre *diaBuyTerreBM;
    DialogBuyAir *diaBuyAirBM;



};
#endif // GAME_H
