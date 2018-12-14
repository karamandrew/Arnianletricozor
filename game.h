#ifndef GAME_H
#define GAME_H
#include "mainwindow.h"
#include "unite.h"

#include "dialogbuyterre.h"
#include "dialogbuyair.h"

#include "bluemoonwin.h"
#include "orangestarwin.h"


class Game{
public:
    static Game& Instance();

    int getXCoordinate(QMouseEvent *e);
    int getYCoordinate(QMouseEvent *e);
    void mouseLeftPressed(int x,int y);
    void mouseRightPressed(int x, int y);

    void move(int x, int y);
    void selectUnits(int x, int y);
    void attack(int x, int y);

    void start(MainWindow &wind);

    int getIndexUnit(int x, int y);
    int getMalusMove(char moveType, int terrainID);
    int getmapId(int x, int y);
    Unite* getUnite(int x, int y);
    bool isThereAnotherUnite(int x, int y, int indexUnitFoc);

    void setgameType(int type);
    void setMapObjectfalse();
    void setTurn();
    void setUnitefocusedfalse();

    void calculatePosAccessible(int Xfoc, int Yfoc, int indexUnit, int mp);
    int attackChart(Unite* a, Unite* d);
    double calculDegat(Unite* u, Unite* v);
    bool Enemyclose(Unite* unit);
    void turnChange();

    void iA();
    void iAcreateUnit();
    void iAmoveUnit();
    bool capturableIDbuilding(int x, int y);
    void createUnit(int x, int y, char type, bool team, int unitWanted);
    void updateMoneyTeam(bool team);
    void setMoney(bool team, int impact);

    void capture(bool turn);

    void giveBuildingsPtCapture();

    void cureUnit(bool turn);

    void fusion(Unite* u1, Unite* u2);

    void checkEndGame(bool turn);

    void showInfo(int x, int y);

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

    DialogBuyTerre *diaBuyTerreOS = nullptr;
    DialogBuyAir *diaBuyAirOS = nullptr;
    DialogBuyTerre *diaBuyTerreBM = nullptr;
    DialogBuyAir *diaBuyAirBM = nullptr;

    BlueMoonWin *diaWinBlue = nullptr;
    OrangeStarWin *diaWinOrange = nullptr;

    int m_gameType = 1;



};
#endif // GAME_H

