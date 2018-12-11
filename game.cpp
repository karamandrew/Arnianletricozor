#include "game.h"
#include <iostream>
#include "math.h"

#include "gameobject.h"
#include "unite.h"
#include "infantry.h"
#include "mech.h"
#include "recon.h"
#include "antiair.h"
#include "tank.h"
#include "mdtank.h"
#include "megatank.h"
#include "neotank.h"
#include "bcopter.h"
#include "fighter.h"
#include "bomber.h"



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

    std::cout << " La pos est : " << m << t << std::endl;

    if ( m >= 0 && m < 21 && t >= 0 && t < 17
         && getIndexUnit(Xfoc,Yfoc) != -1
         && unite[getIndexUnit(Xfoc,Yfoc)]->isFocused()
         && window->getMapObject(m,t).isAccessible() )  {  // Unité selectionné

        unsigned int indexUnitFoc = (int)getIndexUnit(Xfoc,Yfoc);

        unite[indexUnitFoc]->setPosX(m);
        unite[indexUnitFoc]->setPosY(t);
        if (isThereEnemyclose(unite[indexUnitFoc])){
            std::cout << " Ennemi a cote " << std::endl;
        }
        unite[indexUnitFoc]->setFocused(false);
        unite[indexUnitFoc]->setTurn(false);
        setMapObjectfalse();
    }

    else if (getIndexUnit(m,t) != -1) {
        setUnitefocusedfalse();
        setMapObjectfalse();
        if(unite[getIndexUnit(m,t)]->isTurn()){
            unite[getIndexUnit(m,t)]->setFocused(true);

            calculatePosAccessible( m, t, getIndexUnit(m,t), unite[getIndexUnit(m,t)]->getMP()+1);

            Xfoc = m;
            Yfoc = t;
        }
    }

    window->redraw();
}

void Game::start(MainWindow &wind)
{
    window = &wind;
    window->setFixedSize(1200,760);

    // Blue Moon

    Infantry *bminf = new Infantry( 10, 0, 200, false);
    Mech *bmmech = new Mech( 11, 0, 201, false);
    Recon *bmrecon = new Recon( 12, 0, 202, false);
    Antiair *bmantiair = new Antiair( 13, 0, 203, false);
    Tank *bmtank = new Tank( 14, 0, 204, false);
    MdTank *bmmdtank = new MdTank( 15, 0, 205, false);
    MegaTank *bmmegatank = new MegaTank( 10, 1, 206, false);
    NeoTank *bmneotank = new NeoTank( 11, 1, 207, false);
    BCopter *bmbcopter = new BCopter( 12, 1, 208, false);
    Fighter *bmfighter = new Fighter( 13, 1, 209, false);
    Bomber *bmbomber = new Bomber( 14, 1, 210, false);

    // Orange

    Infantry *osinf = new Infantry( 0, 15, 300, true);
    Mech *osmech = new Mech( 1, 15, 301, true);
    Recon *osrecon = new Recon( 2, 15, 302, true);
    Antiair *osantiair = new Antiair( 3, 15, 303, true);
    Tank *ostank = new Tank( 4, 15, 304, true);
    MdTank *osmdtank = new MdTank( 5, 15, 305, true);
    MegaTank *osmegatank = new MegaTank( 0, 14, 306, true);
    NeoTank *osneotank = new NeoTank( 1, 14, 307, true);
    BCopter *osbcopter = new BCopter( 2, 14, 308, true);
    Fighter *osfighter = new Fighter( 3, 14, 309, true);
    Bomber *osbomber = new Bomber( 4, 14, 310, true);




    unite.push_back(bminf);
    unite.push_back(bmmech);
    unite.push_back(bmrecon);
    unite.push_back(bmantiair);
    unite.push_back(bmtank);
    unite.push_back(bmmdtank);
    unite.push_back(bmmegatank);
    unite.push_back(bmneotank);
    unite.push_back(bmbcopter);
    unite.push_back(bmfighter);
    unite.push_back(bmbomber);

    unite.push_back(osinf);
    unite.push_back(osmech);
    unite.push_back(osrecon);
    unite.push_back(osantiair);
    unite.push_back(ostank);
    unite.push_back(osmdtank);
    unite.push_back(osmegatank);
    unite.push_back(osneotank);
    unite.push_back(osbcopter);
    unite.push_back(osfighter);
    unite.push_back(osbomber);
    turnChange();

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

    if(around[0][0] <= mpleft && !isThereAnotherUnite(around[0][1], around[0][2])){
        calculatePosAccessible(around[0][1], around[0][2], indexUnit, mpleft-around[0][0]);
    }

    if(around[1][0] <= mpleft && !isThereAnotherUnite(around[1][1], around[1][2])){
        calculatePosAccessible(around[1][1], around[1][2], indexUnit, mpleft-around[1][0]);
    }

    if(around[2][0] <= mpleft && !isThereAnotherUnite(around[2][1], around[2][2])){
        calculatePosAccessible(around[2][1], around[2][2], indexUnit, mpleft-around[2][0]);
    }

    if(around[3][0] <= mpleft && !isThereAnotherUnite(around[3][1], around[3][2])){
        calculatePosAccessible(around[3][1], around[3][2], indexUnit, mpleft-around[3][0]);
    }
}

bool Game::isThereAnotherUnite(int x, int y)
{
    for(Unite* u : unite) {
        if (u->getPosX()==x && u->getPosY()==y){
            return true;
        }
    }
    return false;
}

void Game::setMapObjectfalse(){
    for (int i=0; i<21; i++){
        for (int j=0; j<17; j++){
          window->getMapObject(i,j).setAccessible(false);
        }
    }
}

void Game::setUnitefocusedfalse()
{
    for(Unite* u : unite) {
        u->setFocused(false);
    }
}

bool Game::isThereEnemyclose(Unite* unit)
{
    if(getIndexUnit(unit->getPosX()-1, unit->getPosY())!=-1){
        if(unite[getIndexUnit(unit->getPosX()-1, unit->getPosY())]->isTeam()!=unit->isTeam()){
            return true;
        }
    }
    else if(getIndexUnit(unit->getPosX()+1, unit->getPosY())!=-1){
        if(unite[getIndexUnit(unit->getPosX()+1, unit->getPosY())]->isTeam()!=unit->isTeam()){
            return true;
        }
    }
    else if(getIndexUnit(unit->getPosX(), unit->getPosY()+1)!=-1){
        if(unite[getIndexUnit(unit->getPosX(), unit->getPosY()+1)]->isTeam()!=unit->isTeam()){
            return true;
        }
    }
    else if(getIndexUnit(unit->getPosX(), unit->getPosY()-1)!=-1){
        if(unite[getIndexUnit(unit->getPosX(), unit->getPosY()-1)]->isTeam()!=unit->isTeam()){
            return true;
        }
    }
        return false;
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
            //default: std::cout << "Type inconnu (f) " <<  std::endl; break;
        }
    }

    else if (moveType == 'b'){
        switch (terrainID) {
            case 1 : return 1 ;
            case 2 : return 1 ;
            case 3 : return 1 ;
            case 4 ... 14 : return 1 ;
            case 15 ... 25 : return 1 ;
            case 26 ... 27 : return 1 ;
            case 28 :return 1000 ;  // LAKE
            case 29 ... 32 : return 1 ;
            case 33 :return 1000 ;  // REEF
            case 101 ... 110 : return 1000 ; // PIPE

            case 34 ... 36 : return 1 ;
            case 43 ... 45 : return 1 ;
            case 38 ... 40 : return 1 ;
            //default: std::cout << "Type inconnu (f) " <<  std::endl; break;
        }
    }

    else if (moveType == 'w'){
        switch (terrainID) {
            case 1 : return 2 ;
            case 2 : return 1000 ; //MOUNTAIN
            case 3 : return 3 ;
            case 4 ... 14 : return 1000 ; //RIVER
            case 15 ... 25 : return 1 ;
            case 26 ... 27 : return 1 ;
            case 28 :return 1000 ;  // LAKE
            case 29 ... 32 : return 1 ;
            case 33 :return 1000 ;  // REEF
            case 101 ... 110 : return 1000 ; // PIPE

            case 34 ... 36 : return 1 ;
            case 43 ... 45 : return 1 ;
            case 38 ... 40 : return 1 ;
            //default: std::cout << "Type inconnu (f) " <<  std::endl; break;
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
            //default: std::cout << "Type inconnu (t) " <<  std::endl; break;
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
            //default: std::cout << "Type inconnu (a) " <<  std::endl; break;
        }
    }

    //std::cerr << "Error : getMalusMove : wrong MoveType" << std::endl;
    return 0;
}

void Game::turnChange(){
    activeTurn=!activeTurn;
    for(Unite* u : unite) {
        if(activeTurn){
            if(u->isTeam()){
                u->setTurn(false);
            }
            else{
                u->setTurn(true);
            }
        }
        else{
            if(!u->isTeam()){
                u->setTurn(false);
            }
            else{
                u->setTurn(true);
            }
        }
    }
    window->redraw();
}

Unite* Game::getUnite(int x, int y){
    int a = getIndexUnit(x,y);
    if(a == -1)
        throw invalid_argument("la fin des haricots");
    return unite[a];
}
