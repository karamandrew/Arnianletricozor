#include "game.h"
#include <iostream>
#include "math.h"
#include "infantry.h"
#include "gameobject.h"
#include "unite.h"

Game Game::gInstance;

Game::Game(){

}

Game::~Game(){
    for(Unite* u : unite) {
        delete u;
    }
}

Game &Game::Instance()
{
    return gInstance;
}

void Game::move(QMouseEvent *e)
{
    float x = floorf(e->x()/40);
    float y = floorf(e->y()/40);
    int m = (int)x-7;
    int t = (int)y-2;

    if ( m >= 0 && m < 21 && t >= 0 && t < 17
         && getIndexUnit(Xfoc,Yfoc) != -1
         && unite[getIndexUnit(Xfoc,Yfoc)]->isFocused()
         && window->getMapObject(m,t).isAccessible() )  {  // Unité selectionné

        unsigned int indexUnitFoc = (int)getIndexUnit(Xfoc,Yfoc);

        unite[indexUnitFoc]->setPosX(m);
        unite[indexUnitFoc]->setPosY(t);
        unite[indexUnitFoc]->setFocused(false);
        for (int i=0; i<21; i++){
            for (int j=0; j<17; j++){
                window->getMapObject(i,j).setAccessible(false);
            }
        }
    }

    else if (getIndexUnit(m,t) != -1) {
        unite[getIndexUnit(m,t)]->setFocused(true);

        calculatePosAccessible(m,t, getIndexUnit(m,t), unite[getIndexUnit(m,t)]->getMP()+1);

        Xfoc = m;
        Yfoc = t;
    }

    window->redraw();
}



void Game::start(MainWindow &wind)
{
    window = &wind;
    window->setFixedSize(1200,760);

    Infantry *inf = new Infantry(14,12,200,true);
    Infantry *inf2 = new Infantry(20,9,200,false);
    Infantry *inf3 = new Infantry(2,2,200,true);

    unite.push_back(inf);
    unite.push_back(inf2);
    unite.push_back(inf3);

    window->createMapObjects();

    window->redraw();
}



int Game::getIndexUnit(int x, int y)
{
    for (unsigned int i=0; i<unite.size(); i++){
        if (unite[i]->getPosX()==x && unite[i]->getPosY()==y){
            return static_cast<int>(i);
        }
    }
    return -1;
}
class Pos{
public:
    int x;
    int y;
};

Pos operator+(Pos const& a, Pos const& b){
    Pos n;
    n.x = a.x + b.x;
    n.y = a.y + b.y;
    return n;
}

// Pos{1,2} + Pos{3,4}

void Game::calculatePosAccessible(int currentX, int currentY, int indexUnit, int mp){

    if (mp == 0 || !(0 <= currentX && currentX < 21 && 0 <= currentY && currentY < 17)){
        return;
    }

    char MovType = unite[indexUnit]->getTypeMovement();
    int mpleft = mp;
    int around[4][3];

    window->getMapObject(currentX,currentY).setAccessible(true);

    around[0][0] = getMalusMove(MovType, getmapId(currentX-1, currentY));
    around[0][1] = currentX-1;
    around[0][2] = currentY;

    around[1][0] = getMalusMove(MovType, getmapId(currentX+1, currentY));
    around[1][1] = currentX+1;
    around[1][2] = currentY;

    around[2][0] = getMalusMove(MovType, getmapId(currentX, currentY-1));
    around[2][1] = currentX;
    around[2][2] = currentY-1;

    around[3][0] = getMalusMove(MovType, getmapId(currentX, currentY+1));
    around[3][1] = currentX;
    around[3][2] = currentY+1;

    if(around[0][0] <= mpleft){
        calculatePosAccessible(around[0][1], around[0][2], indexUnit, mpleft-around[0][0]);
    }

    if(around[1][0] <= mpleft){
        calculatePosAccessible(around[1][1], around[1][2], indexUnit, mpleft-around[1][0]);
    }

    if(around[2][0] <= mpleft){
        calculatePosAccessible(around[2][1], around[2][2], indexUnit, mpleft-around[2][0]);
    }

    if(around[3][0] <= mpleft){
        calculatePosAccessible(around[3][1], around[3][2], indexUnit, mpleft-around[3][0]);
    }
}

int Game::getmapId(int x, int y){

    if (!(0 <= x && x < 21 && 0 <= y && y < 17)){
        //std::cerr << "getMapId out of the map" << std::endl;
        return -1;
    }
    else {
        return window->getMapObject(x, y).getId();
    }

}

int Game::getMalusMove(char moveType, int terrainID){
    if (moveType == 'f'){
        switch (terrainID) {
            case 1 : return 1 ;
            case 2 : return 2 ;
            case 3 : return 1 ;
            case 4 ... 14 : return 2 ;
            case 15 ... 25 : return 1 ;
            case 26 ... 27 : return 1 ;
            case 28 :return 1000 ;  // LAKE
            case 29 ... 32 : return 1 ;
            case 33 :return 1000 ;  // REEF
            case 101 ... 110 : return 1000 ; // PIPE

            case 34 ... 36 : return 1 ;
            case 43 ... 45 : return 1 ;
            case 38 ... 40 : return 1 ;
            //default: std::cout << "Type inconnu" <<  std::endl; break;
        }
    }
    else if (moveType == 't') {
        switch (terrainID) {
            case 1 : return 1 ;
            case 2 : return 1000 ; // Mountain
            case 3 : return 2 ;
            case 4 ... 14 : return 1000 ; // River
            case 15 ... 25 : return 1 ;
            case 26 ... 27 :return 1 ;
            case 28 :return 1000 ;  // LAKE
            case 29 ... 32 :return 1 ;
            case 33 :return 1000 ;  // REEF
            case 101 ... 110 :return 1000 ; // PIPE

            case 34 ... 36 : return 1 ;
            case 43 ... 45 : return 1 ;
            case 38 ... 40 : return 1 ;
            //default: std::cout << "Type inconnu" <<  std::endl; break;
        }
    }
    else if (moveType == 'a'){
        switch (terrainID) {
            case 1 : return 1 ;
            case 2 : return 1 ;
            case 3 : return 1 ;
            case 4 ... 14 : return 1 ;
            case 15 ... 25 : return 1 ;
            case 26 ... 27 :return 1 ;
            case 28 :return 1 ;
            case 29 ... 32 :return 1 ;
            case 33 :return 1;
            case 101 ... 110 :return 1 ;

            case 34 ... 36 : return 1 ;
            case 43 ... 45 : return 1 ;
            case 38 ... 40 : return 1 ;
            //default: std::cout << "Type inconnu" <<  std::endl; break;
        }
    }

    //std::cerr << "Error : getMalusMove : wrong MoveType" << std::endl;
    return 0;
}

Unite* Game::getUnite(int x, int y){
    int a = getIndexUnit(x,y);
    if(a == -1)
        throw invalid_argument("la fin des haricots");
    return unite[a];
}

