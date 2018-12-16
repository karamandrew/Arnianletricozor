#ifndef GAME_H
#define GAME_H
#include "mainwindow.h"
#include "unite.h"
#include "dialogbuyterre.h"
#include "dialogbuyair.h"
#include "bluemoonwin.h"
#include "orangestarwin.h"
#include "dialognewgame.h"


class Game{

public:

    static Game& Instance();

    void mouseLeftPressed(int x,int y);
    void mouseRightPressed(int x, int y);
    void start(MainWindow &wind);
    void setgameType(int type);
    void turnChange();
    void createUnit(int x, int y, char type, bool team, int unitWanted);
    void endGame();
    void restart(int gameType);

    int getXCoordinate(QMouseEvent *e);
    int getYCoordinate(QMouseEvent *e);

    int getIndexUnit(int x, int y);

    Unite* getUnite(int x, int y);

    ~Game();

private:

    Game();

    void move(int x, int y);
    void selectUnits(int x, int y);
    void attack(int x, int y);
    void setMapObjectfalse();
    void setUnitefalse();
    void calculatePosAccessible(int Xfoc, int Yfoc, int indexUnit, int mp);
    void iA();
    void iAcreateUnit();
    void iAmoveUnit();
    void updateMoneyTeam(bool team);
    void setMoney(bool team, int impact);
    void capture(bool turn);
    void giveBuildingsPtCapture();
    void cureUnit(bool turn);
    void fusion(Unite* u1, Unite* u2);
    void checkEndGame();
    void showInfo(int x, int y);
    void victoireBleu();
    void victoireOrange();

    int getMalusMove(char moveType, int terrainID);
    int getmapId(int x, int y);
    int attackChart(Unite* a, Unite* d);
    int calculDegat(Unite* u, Unite* v);

    bool isThereAnotherUnite(int x, int y, int indexUnitFoc);
    bool Enemyclose(Unite* unit);
    bool capturableIDbuilding(int x, int y);

    static Game gInstance;
    MainWindow *window;
    vector<Unite*> unite;

    int Xfoc = -1;
    int Yfoc = -1;
    int moneyTeamF = 0;  // Blue Moon
    int moneyTeamT = 0; // Orange Star
    int m_gameType = 1;

    bool activeTurn =false;

    DialogBuyTerre *diaBuyTerreOS = nullptr;
    DialogBuyAir *diaBuyAirOS = nullptr;
    DialogBuyTerre *diaBuyTerreBM = nullptr;
    DialogBuyAir *diaBuyAirBM = nullptr;
    BlueMoonWin *diaWinBlue = nullptr;
    OrangeStarWin *diaWinOrange = nullptr;
    DialogNewGame *diaNewGame = nullptr;

};
#endif // GAME_H

