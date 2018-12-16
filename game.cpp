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
#include "pos.h"
#include <thread>
#include <chrono>

Game Game::gInstance;

Game::Game(){
}

Game &Game::Instance()
{
    return gInstance;
}

void Game::start(MainWindow &wind)
{
    window = &wind;
    window->setFixedSize(1400,865);
    window->createMapObjects();
    giveBuildingsPtCapture();

    turnChange();

}


///////////////////////////////////////// MOUSE ACTIVATION

int Game::getXCoordinate(QMouseEvent *e)
{
    float x = floorf(e->x()/40);
    return static_cast<int>(x-7);
}

int Game::getYCoordinate(QMouseEvent *e)
{
    float y = floorf(e->y()/40);
    return static_cast<int>(y-1);
}

void Game::mouseLeftPressed(int x, int y)
{
    attack(x,y);
    move(x,y);
    selectUnits(x,y);
}

void Game::mouseRightPressed(int x, int y)
{
    showInfo(x,y);
}

void Game::attack(int x, int y)
{
    int indexUnit = getIndexUnit(x,y);
    int indexUnitFoc = -1;

    if( indexUnit != -1 && !unite[indexUnit]->isFocused()){    // TEST FOCUSED PAS NECESSAIRE
        if(unite[indexUnit]->isAttackable()){

            for(Unite* a: unite){
                if (a->isFocused()){
                    indexUnitFoc = getIndexUnit(a->getPosX(),a->getPosY());
                 }
            }

            if (indexUnitFoc != -1){  // COMBAT

                unite[indexUnit]->receiveDamage(calculDegat(unite[indexUnitFoc],unite[indexUnit])); // Attaque
                unite[indexUnitFoc]->receiveDamage(calculDegat(unite[indexUnit],unite[indexUnitFoc])); // Contre-attaque
                unite[indexUnitFoc]->setTurn(false);

                if(unite[indexUnit]->getVie()<=0){
                    delete unite[indexUnit];
                    unite.erase(unite.begin() + getIndexUnit(unite[indexUnit]->getPosX(), unite[indexUnit]->getPosY()));
                }

                if(unite[indexUnitFoc]->getVie()<=0){
                    delete unite[indexUnitFoc];
                    unite.erase(unite.begin() + getIndexUnit(unite[indexUnitFoc]->getPosX(), unite[indexUnitFoc]->getPosY()));
                 }
                 checkEndGame();
                 setUnitefalse();
            }
        }

        window->redraw();
    }
}


void Game::move(int x, int y)
{
    int indexUnitFoc = getIndexUnit(Xfoc,Yfoc);
    if ( x >= 0 && x < 21 && y >= 0 && y < 17
         &&  indexUnitFoc != -1
         && unite[indexUnitFoc]->isFocused()
         && window->getMapObject(x,y).isAccessible() )  {

        unite[indexUnitFoc]->setPosX(x);
        unite[indexUnitFoc]->setPosY(y);

        setMapObjectfalse();

        if (Enemyclose(unite[indexUnitFoc])){
            window->redraw();
            unite[indexUnitFoc]->setTurn(false);
            return;
        }

        unite[indexUnitFoc]->setFocused(false);
        unite[indexUnitFoc]->setTurn(false);
    }

    else if ( x>=0 && x < 21 && y >= 0 && y < 17
         && indexUnitFoc != -1
         && getIndexUnit(x,y) != -1
         && unite[getIndexUnit(x,y)]->isFusionnable()) {

         fusion(unite[indexUnitFoc],unite[getIndexUnit(x,y)]);
         unite[getIndexUnit(x,y)]->setFusionnable(false);
    }

    else if (getIndexUnit(x,y) != -1) {
        setUnitefalse();
        setMapObjectfalse();
        if(unite[getIndexUnit(x,y)]->isTurn()){
            unite[getIndexUnit(x,y)]->setFocused(true);

            calculatePosAccessible( x, y, getIndexUnit(x,y), unite[getIndexUnit(x,y)]->getMP()+1);

            Xfoc = x;
            Yfoc = y;
        }
    }
    else {
        setMapObjectfalse();
        setUnitefalse();
    }
    window->redraw();
}

void Game::selectUnits(int x, int y){
    int IDmap = getmapId(x,y);

    if (getIndexUnit(x,y) == -1){

        if ( IDmap == 39 && activeTurn == true){
            // Créatio unités terrestre orange
            diaBuyTerreOS = new DialogBuyTerre(window);
            diaBuyTerreOS->show();
            diaBuyTerreOS->getInfo( x,y, true);
        }

        if ( IDmap == 40 && activeTurn == true){
            // Création unités aériennes orange
            diaBuyAirOS = new DialogBuyAir(window);
            diaBuyAirOS->show();
            diaBuyAirOS->getInfo( x,y, true);
        }

        if ( IDmap == 44 && activeTurn == false){
            // Création unités terrestres bleues
            diaBuyTerreBM = new DialogBuyTerre(window);
            diaBuyTerreBM->show();
            diaBuyTerreBM->getInfo( x,y, false);
        }

        if (IDmap == 45 && activeTurn == false){
            // Création unités aériennes bleues
            diaBuyAirBM = new DialogBuyAir(window);
            diaBuyAirBM->show();
            diaBuyAirBM->getInfo( x,y, false);
        }
    }
}


void Game::showInfo(int x, int y){

    // INFOS TERRAINS
    int mapID = getmapId(x,y);
    string terrainType;

    switch(mapID){

    // Terrains
    case 1 :  terrainType = "Plain"; break;
    case 2 :  terrainType = "Mountain"; break;
    case 3 :  terrainType = "Wood";  break;
    case 4 ... 14 : terrainType = " River"; break;
    case 15 ... 25 :  terrainType = "Road" ; break;
    case 26 ... 27 : terrainType = "Bridge" ; break;
    case 28 :      terrainType = "Sea" ; break;
    case 29 ... 32 :  terrainType  = "Shoal"; break;
    case 33 : terrainType = "Reef" ; break;
    case 101 ... 110 :  terrainType = "Pipe"; break;

    // City
    case 34 : terrainType = "Neutral city"; break; //Neutral
    case 38 : terrainType = "Orange Star city"; break; // Orange
    case 43 : terrainType =  "Blue Moon city"; break; // Blue
    // Base
    case 35 : terrainType = "Neutral Base" ; break; //Neutral
    case 39 : terrainType = "Orange Star Base"; break; // Orange
    case 44 : terrainType = "Blue Moon Base"; break; // Blue
    // Airport
    case 36 : terrainType = "Neutral Airport"; break; //Neutral
    case 40 : terrainType = "Orange Star Airport"; break; // Orange
    case 45 : terrainType = "Blue Moon Airport"; break;  // Blue

    }

    int PtDefense = window->getMapObject(x,y).getDefense();
    int PtCapture = window->getMapObject(x,y).getPtCapture();

    // Infos unités

    bool team = false;
    bool unit = false;
    int viesUnit = 0;
    int indexUnit = getIndexUnit(x,y);
    int indexUnitFoc = -1;

    for (Unite* u : unite){
        if ( u->isFocused()){
            indexUnitFoc = getIndexUnit(u->getPosX(),u->getPosY());
        }
    }

    bool attackable = false;
    int degats = 0;

    if (indexUnit != -1 ) {

        unit = true;
        team = unite[indexUnit]->isTeam();
        viesUnit = unite[indexUnit]->getVie();

        if ( unite[indexUnit]->isAttackable() && indexUnitFoc != -1 ){

            attackable = true;
            degats = calculDegat(unite[indexUnitFoc],unite[indexUnit]);

        }
    }

    bool update = false;

    window->updateInfoPos(terrainType, PtDefense, PtCapture, unit, team, viesUnit, attackable, degats, update);
}


///////////////////////////////////   IA



void Game::iA(bool team)
{
    if(!team){
        while(moneyTeamF>=1000){
        iAcreateUnit(team);
        iAmoveUnit(team);
        }
    }
    else{
        while(moneyTeamT>=1000){
        iAcreateUnit(team);
        iAmoveUnit(team);
        }
    }
    turnChange();
}

void Game::iAcreateUnit(bool team)
{
    srand(time(NULL));
    bool adversaires = false;
    for (Unite* u : unite){
        if (u->isTeam()!=team){
            adversaires = true;
        }
    }
    for(int x=0 ;x<21;x++){
        for (int y=0; y<17; y++){
            if (((!team && getmapId(x,y) ==45)||(team && getmapId(x,y)==40)) && !isThereAnotherUnite(x,y,-1)) { //aéroport
                if (((!team && moneyTeamF>=22000)||(team && moneyTeamT>=22000)) && adversaires) {if(!team) {Bomber *osbomber = new Bomber( x, y, 210, team); unite.push_back(osbomber);} if(team){Bomber *bmbomber = new Bomber( x, y, 310, team); unite.push_back(bmbomber);} setMoney(team, -22000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if (((!team && moneyTeamF>=20000)||(team && moneyTeamT>=20000)) && adversaires) {if(!team) {Fighter *osfighter = new Fighter( x, y, 209, team); unite.push_back(osfighter);} if(team){Fighter *bmfighter = new Fighter( x, y, 309, team); unite.push_back(bmfighter);} setMoney(team, -20000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if (((!team && moneyTeamF>=9000)||(team && moneyTeamT>=9000)) && adversaires ) {if(!team) {BCopter *osbcopter = new BCopter( x, y, 208, team); unite.push_back(osbcopter);} if(team) {BCopter *bmbcopter = new BCopter( x, y, 308, team); unite.push_back(bmbcopter);} setMoney(team, -9000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else {return;}
            }
            if (((!team && getmapId(x,y) ==44)||(team && getmapId(x,y)==39)) && !isThereAnotherUnite(x,y,-1)) { //Base
                int randNum = (rand() % 3) + 1;
                if (((!team && moneyTeamF>=28000)||(team && moneyTeamT>=28000)) && adversaires) {if(!team) {MegaTank *osmegatank = new MegaTank( x, y, 206, team); unite.push_back(osmegatank);}if(team){MegaTank *bmmegatank = new MegaTank( x, y, 306, team); unite.push_back(bmmegatank);} setMoney(team, -28000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if (((!team && moneyTeamF>=22000)||(team && moneyTeamT>=22000)) && adversaires) {if(!team) {NeoTank *osneotank = new NeoTank( x, y, 207, team); unite.push_back(osneotank);}if(team) {NeoTank *bmneotank = new NeoTank( x, y, 307, team); unite.push_back(bmneotank);} setMoney(team, -22000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if (((!team && moneyTeamF>=16000)||(team && moneyTeamT>=16000)) && adversaires) {if(!team) {MdTank *osmdtank = new MdTank( x, y, 205, team); unite.push_back(osmdtank);}if(team) {MdTank *bmmdtank = new MdTank( x, y, 305, team); unite.push_back(bmmdtank);} setMoney(team, -16000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if (((!team && moneyTeamF>=8000)||(team && moneyTeamT>=8000)) && adversaires) {if(!team) {Antiair *osantiair = new Antiair( x, y, 203, team); unite.push_back(osantiair);}if(team) {Antiair *bmantiair = new Antiair( x, y, 303, team); unite.push_back(bmantiair);}setMoney(team, -8000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if (((!team && moneyTeamF>=7000)||(team && moneyTeamT>=7000)) && adversaires) {if(!team) {Tank *ostank = new Tank( x, y, 204, team); unite.push_back(ostank);}if(team){Tank *bmtank = new Tank( x, y, 304, team); unite.push_back(bmtank);} setMoney(team, -7000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if (((!team && moneyTeamF>=4000)||(team && moneyTeamT>=4000)) && adversaires) {if(!team) {Recon *osrecon = new Recon( x, y, 202, team); unite.push_back(osrecon);}if(team){Recon *bmrecon = new Recon( x, y, 302, team); unite.push_back(bmrecon);} setMoney(team, -4000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if (((!team && moneyTeamF>=3000)||(team && moneyTeamT>=3000)) && randNum==3) {if(!team) {Mech *osmech = new Mech( x, y, 201, team); unite.push_back(osmech);}if(team){Mech *bmmech = new Mech( x, y, 301, team); unite.push_back(bmmech);} setMoney(team, -3000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else if ((!team && moneyTeamF>=1000)||(team && moneyTeamT>=1000)) {if(!team) {Infantry *osinf = new Infantry( x, y, 200, team); unite.push_back(osinf);}if(team){Infantry *bminf = new Infantry( x, y, 300, team); unite.push_back(bminf);} setMoney(team, -1000);window->redraw();std::this_thread::sleep_for (std::chrono::microseconds(500000));}
                else {return;}
            }
        }
    }
}

void Game::iAmoveUnit(bool team)
{
    vector<Pos> coordinateB;
    Pos capturablebuild;
    for(int x=0 ;x<21;x++){
        for (int y=0; y<17; y++){
            if(capturableIDbuilding(x,y,team)){
                capturablebuild.setX(x);
                capturablebuild.setY(y);
                coordinateB.push_back(capturablebuild);
            }
        }
    }

    for(Unite* u: unite){
        if(u->isTeam()==team && u->isTurn()){

            Pos closest;
            Pos posChosed;

            int dist=100;
            int i=-1;

            if(u->getId()==200 || u->getId()==201 || u->getId()==300 || u->getId()==301){

                //std::cout<<closest.getX()<<" "<<closest.getY()<<std::endl;

                for(Pos c: coordinateB){
                    if(dist>u->getPos()-c){
                            dist=u->getPos()-c;
                            closest=c;
                    }
                }
                for(Pos c: coordinateB){
                    i++;
                    if(closest==c){
                        break;
                    }
                }

                //if ( closest.getX() != u->getPosX() && closest.getY() != u->getPosY()) {

                coordinateB.erase(coordinateB.begin()+i);
                move(u->getPosX(), u->getPosY());
                std::this_thread::sleep_for (std::chrono::microseconds(300000));
                for (int i=0; i<21; i++){
                    for (int j=0; j<17; j++){
                        if(window->getMapObject(i,j).isAccessible()){
                            if(window->getMapObject(i,j).getPos()-closest<dist){
                                dist=window->getMapObject(i,j).getPos()-closest;
                                posChosed=window->getMapObject(i,j).getPos();
                            }
                        }
                    }
                }
                //std::cout<<posChosed.getX()<<" "<<posChosed.getY()<<std::endl;
                move(posChosed.getX(), posChosed.getY());
                std::this_thread::sleep_for (std::chrono::microseconds(300000));

                //}

            }
            else{
                move(u->getPosX(), u->getPosY());
                std::this_thread::sleep_for (std::chrono::microseconds(300000));
                for (int i=0; i<21; i++){
                    for (int j=0; j<17; j++){
                        if(window->getMapObject(i,j).isAccessible()){
                            for (Unite* e: unite){
                                if(e->isTeam()!=team){
                                if(e->getPos() - window->getMapObject(i,j).getPos() < dist){

                                    dist = e->getPos() - window->getMapObject(i,j).getPos();
                                    closest=e->getPos();
                                    std::cout<<closest.getX()<<" "<<closest.getY()<<std::endl;
                                }
                                else if(e->getPos()-window->getMapObject(i,j).getPos()==1){
                                    if(calculDegat(u,e)>calculDegat(u,unite[getIndexUnit(closest.getX(),closest.getY())])){
                                        closest=e->getPos();
                                    }
                            }
                            if(window->getMapObject(i,j).getPos()-closest<=dist){
                                dist=window->getMapObject(i,j).getPos()-closest;
                                posChosed=window->getMapObject(i,j).getPos();
                            }
                            }
                            }
                        }
                    }
                }
                move(posChosed.getX(), posChosed.getY());
                std::this_thread::sleep_for (std::chrono::microseconds(500000));
                if(Enemyclose(u)){
                    u->setFocused(true);
                    attack(closest.getX(),closest.getY());
                    std::this_thread::sleep_for (std::chrono::microseconds(2000000));
                }
                std::this_thread::sleep_for (std::chrono::microseconds(300000));
                // + if fussionnable -> fusion + chaud montrer que y a fusion !

            }
        }
    }
}

bool Game::capturableIDbuilding(int x, int y, bool team)
{
    if (getmapId(x,y) == 34 || getmapId(x,y) == 35 || getmapId(x,y) == 36 || (!team && (getmapId(x,y) == 38 || getmapId(x,y) == 39 || getmapId(x,y) == 40)) || (team && (getmapId(x,y) == 43 || getmapId(x,y) == 44 || getmapId(x,y) == 45))) {
        return true;
    }
    return false;
}

/////////////////////// FONCTIONNALITES JEU


void Game::fusion(Unite* u1, Unite* u2){
    int bonusLife = u1->getVie();
    int indexu1 = getIndexUnit(u1->getPosX(),u1->getPosY());
    delete u1;
    unite.erase(unite.begin() + indexu1);

    u2->setVie(bonusLife);
    setMapObjectfalse();
    window->redraw();

}

void Game::createUnit(int x, int y, char type, bool team, int unitWanted){

    if ( getIndexUnit(x,y) == -1){

    if ( team == true && activeTurn == true){
        if ( type == 't'){
            if ( unitWanted == 1 && moneyTeamT >= 1000 ) { Infantry *osinf = new Infantry( x, y, 300, true); unite.push_back(osinf); setMoney(true, -1000); }
            if ( unitWanted == 2 && moneyTeamT >= 3000 ) { Mech *osmech = new Mech( x, y, 301, true); unite.push_back(osmech); setMoney(true, -3000); }
            if ( unitWanted == 3 && moneyTeamT >= 4000 ) { Recon *osrecon = new Recon( x, y, 302, true); unite.push_back(osrecon); setMoney(true, -4000); }
            if ( unitWanted == 4 && moneyTeamT >= 8000 ) { Antiair *osantiair = new Antiair( x, y, 303, true); unite.push_back(osantiair); setMoney(true, -8000); }
            if ( unitWanted == 5 && moneyTeamT >= 7000 ) { Tank *ostank = new Tank( x, y, 304, true); unite.push_back(ostank); setMoney(true, -7000); }
            if ( unitWanted == 6 && moneyTeamT >= 16000) { MdTank *osmdtank = new MdTank( x, y, 305, true); unite.push_back(osmdtank); setMoney(true, -16000); }
            if ( unitWanted == 7 && moneyTeamT >= 28000) { MegaTank *osmegatank = new MegaTank( x, y, 306, true); unite.push_back(osmegatank); setMoney(true, -28000); }
            if ( unitWanted == 8 && moneyTeamT >= 22000) { NeoTank *osneotank = new NeoTank( x, y, 307, true); unite.push_back(osneotank); setMoney(true, -22000); }
        }
        if ( type == 'a'){
            if ( unitWanted == 1 && moneyTeamT >= 9000 ) { BCopter *osbcopter = new BCopter( x, y, 308, true); unite.push_back(osbcopter); setMoney(true, -9000); }
            if ( unitWanted == 2 && moneyTeamT >= 20000) { Fighter *osfighter = new Fighter( x, y, 309, true); unite.push_back(osfighter); setMoney(true, -20000); }
            if ( unitWanted == 3 && moneyTeamT >= 22000) { Bomber *osbomber = new Bomber( x, y, 310, true); unite.push_back(osbomber); setMoney(true, -22000); }
        }
    }
    if ( team == false && activeTurn == false){
        if ( type == 't'){
            if ( unitWanted == 1 && moneyTeamF >= 1000 ) { Infantry *bminf = new Infantry( x, y, 200, false); unite.push_back(bminf); setMoney(false, -1000); }
            if ( unitWanted == 2 && moneyTeamF >= 3000 ) { Mech *bmmech = new Mech( x, y, 201, false); unite.push_back(bmmech); setMoney(false, -3000); }
            if ( unitWanted == 3 && moneyTeamF >= 4000 ) { Recon *bmrecon = new Recon( x, y, 202, false); unite.push_back(bmrecon); setMoney(false, -4000); }
            if ( unitWanted == 4 && moneyTeamF >= 8000 ) { Antiair *bmantiair = new Antiair( x, y, 203, false); unite.push_back(bmantiair); setMoney(false, -8000); }
            if ( unitWanted == 5 && moneyTeamF >= 7000 ) { Tank *bmtank = new Tank( x, y, 204, false); unite.push_back(bmtank); setMoney(false, -7000); }
            if ( unitWanted == 6 && moneyTeamF >= 16000) { MdTank *bmmdtank = new MdTank( x, y, 205, false); unite.push_back(bmmdtank); setMoney(false, -16000); }
            if ( unitWanted == 7 && moneyTeamF >= 28000) { MegaTank *bmmegatank = new MegaTank( x, y, 206, false); unite.push_back(bmmegatank); setMoney(false, -28000); }
            if ( unitWanted == 8 && moneyTeamF >= 22000) { NeoTank *bmneotank = new NeoTank( x, y, 207, false); unite.push_back(bmneotank); setMoney(false, -22000); }
        }
        if ( type == 'a'){
            if ( unitWanted == 1 && moneyTeamF >= 9000 ) { BCopter *bmbcopter = new BCopter( x, y, 208, false); unite.push_back(bmbcopter); setMoney(false, -9000); }
            if ( unitWanted == 2 && moneyTeamF >= 20000) { Fighter *bmfighter = new Fighter( x, y, 209, false); unite.push_back(bmfighter); setMoney(false, -20000); }
            if ( unitWanted == 3 && moneyTeamF >= 22000) { Bomber *bmbomber = new Bomber( x, y, 210, false); unite.push_back(bmbomber); setMoney(false, -22000); }
        }
    }
    }
    window->redraw();
}


void Game::giveBuildingsPtCapture(){
    for(int i=0 ;i<21;i++){
        for (int j=0; j<17; j++){
            int IDmap = getmapId(i,j);
            if ( IDmap == 34 || IDmap == 35 || IDmap == 36 || IDmap == 38 || IDmap == 39 || IDmap == 40 || IDmap == 43 || IDmap == 44 || IDmap == 45){
                window->getMapObject(i,j).setPtCapture(20);
            }
       }
    }
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

    if(around[0][0] <= mpleft && !isThereAnotherUnite(around[0][1], around[0][2], indexUnit)){
        calculatePosAccessible(around[0][1], around[0][2], indexUnit, mpleft-around[0][0]);
    }

    if(around[1][0] <= mpleft && !isThereAnotherUnite(around[1][1], around[1][2], indexUnit)){
        calculatePosAccessible(around[1][1], around[1][2], indexUnit, mpleft-around[1][0]);
    }

    if(around[2][0] <= mpleft && !isThereAnotherUnite(around[2][1], around[2][2], indexUnit)){
        calculatePosAccessible(around[2][1], around[2][2], indexUnit, mpleft-around[2][0]);
    }

    if(around[3][0] <= mpleft && !isThereAnotherUnite(around[3][1], around[3][2], indexUnit)){
        calculatePosAccessible(around[3][1], around[3][2], indexUnit, mpleft-around[3][0]);
    }
}

bool Game::isThereAnotherUnite(int x, int y, int indexUnitFoc)
{
    for(Unite* u : unite) {
        if (u->getPosX()==x && u->getPosY()==y){
            if ( indexUnitFoc != -1 && unite[indexUnitFoc]->getId() ==  u->getId() && unite[indexUnitFoc]->getVie() < 10 && u->getVie() < 10 ) {
                if(u->getPosX()!=unite[indexUnitFoc]->getPosX() && u->getPosY()!=unite[indexUnitFoc]->getPosY()){
                    u->setFusionnable(true);
                }
            }
            return true;
        }
    }
    return false;
}

void Game::setgameType(int type)
{
    m_gameType=type;
}

void Game::setMapObjectfalse(){
    for (int i=0; i<21; i++){
        for (int j=0; j<17; j++){
          window->getMapObject(i,j).setAccessible(false);
        }
    }
}

void Game::setUnitefalse()
{
    for(Unite* u : unite) {
        u->setFocused(false);
        u->setFusionnable(false);
        u->setAttackable(false);
    }
}

int Game::calculDegat(Unite* u, Unite* v)
    {
        double B = attackChart(u,v);
        double A_HP = u->getVie();
        double D_TR = window->getMapObject(v->getPosX(), v->getPosY()).getDefense();
        double D_HP = v->getVie();
        if (v->getTypeMovement()=='a'){
            D_TR=0;
        }
        double degats = (B *( A_HP / 10 ) * ( ( 100 - D_TR * D_HP) / 100 ))/10;

        int domagearrondi = 0;
        if(degats > 1 && degats <9.5){
            while(degats >1){
                degats -= 1;
                domagearrondi+=1;
                if(degats >=0.5 && degats <1){
                    domagearrondi+=1;
                }
            }
        }
        else if(degats <0.5){
            domagearrondi=0;
        }
        else if(0.5 <= degats && degats <=1){
            domagearrondi=1;
        }
        else{
            domagearrondi=10;
        }

        return  domagearrondi ;
}

bool Game::Enemyclose(Unite* unit)
{
    int i=0;
    if(getIndexUnit(unit->getPosX()-1, unit->getPosY())!=-1){
        if(unite[getIndexUnit(unit->getPosX()-1, unit->getPosY())]->isTeam()!=unit->isTeam()){
            unite[getIndexUnit(unit->getPosX()-1, unit->getPosY())]->setAttackable(true);
            i++;
        }
    }
    if(getIndexUnit(unit->getPosX()+1, unit->getPosY())!=-1){
        if(unite[getIndexUnit(unit->getPosX()+1, unit->getPosY())]->isTeam()!=unit->isTeam()){
            unite[getIndexUnit(unit->getPosX()+1, unit->getPosY())]->setAttackable(true);
            i++;
        }
    }
    if(getIndexUnit(unit->getPosX(), unit->getPosY()+1)!=-1){
        if(unite[getIndexUnit(unit->getPosX(), unit->getPosY()+1)]->isTeam()!=unit->isTeam()){
            unite[getIndexUnit(unit->getPosX(), unit->getPosY()+1)]->setAttackable(true);
            i++;
        }
    }
    if(getIndexUnit(unit->getPosX(), unit->getPosY()-1)!=-1){
        if(unite[getIndexUnit(unit->getPosX(), unit->getPosY()-1)]->isTeam()!=unit->isTeam()){
            unite[getIndexUnit(unit->getPosX(), unit->getPosY()-1)]->setAttackable(true);
            i++;
        }
    }
    if (i==0) {
        return false;
    }
    return true;
}

int Game::getmapId(int x, int y){

    if (!(0 <= x && x < 21 && 0 <= y && y < 17)){
        return -1;
    }
    else {
        return window->getMapObject(x, y).getId();
    }

}

void Game::turnChange(){

    setUnitefalse();
    setMapObjectfalse();

    capture(activeTurn);
    cureUnit(activeTurn);
    activeTurn=!activeTurn;
    updateMoneyTeam(activeTurn);
    window->updateTurn(activeTurn);
    for(Unite* u : unite) {
        if(activeTurn){
            if(u->isTeam()){
                u->setTurn(true);
            }
            else{
                u->setTurn(false);
            }
        }
        else{
            if(!u->isTeam()){
                u->setTurn(true);
            }
            else{
                u->setTurn(false);
            }
        }
    }
    if((m_gameType==2 || m_gameType==4) && !activeTurn){
        iA(false);
    }
    if(m_gameType==4 && activeTurn){
        iA(true);
    }
    window->redraw();
}


void Game::cureUnit(bool turn){
    for (Unite* u:unite){
        int x = u->getPosX();
        int y = u->getPosY();
        int unitLife = u->getVie();
        int mapId = getmapId(x,y);
        char typeMove = u->getTypeMovement();
        bool team = u->isTeam();
        int cout = u->getPrix()/10;
        if (unitLife < 10){
            if (typeMove == 'f' || typeMove == 'b' || typeMove == 't' || typeMove == 'w'){
                if ( !turn && team){ //Orange
                    if (mapId == 38 || mapId == 39){
                        u->setVie(2);
                        setMoney(true, -cout);
                    }
                }
                if ( turn && !team ) { // Bleu
                    if (mapId == 43 || mapId == 44){
                        u->setVie(2);
                        setMoney(false, -cout);
                     }
                }
            }
            if (typeMove == 'a'){
                if ( !turn && team){ //Orange
                    if (mapId == 40){
                        u->setVie(2);
                        setMoney(true,-cout);
                    }
                }
                if ( turn && !team ) { // Bleu
                    if (mapId == 45){
                        u->setVie(2);
                        setMoney(false, -cout);
                    }
               }
            }
        }
    }
}

void Game::capture(bool turn){
    for(Unite* u: unite){
        int IDu = u->getId();
        int x = u->getPosX();
        int y = u->getPosY();
        int mapId = getmapId(x,y);
        int impact = u->getVie();
        int team = u->isTeam();
        int Ptrestant;
        if ( IDu == 200 || IDu == 201 || IDu == 300 || IDu == 301 ){ // INfantry or mech
            if ( !turn && team ) { // tour des oranges
                if ( mapId == 34 || mapId == 35 || mapId == 36 ){
                    window->getMapObject(x,y).setPtCapture(-impact);
                    Ptrestant = window->getMapObject(x,y).getPtCapture();
                    if ( Ptrestant <= 0 ) { window->getMapObject(x,y).setId(+4);
                                            window->getMapObject(x,y).setPtCapture(20);
                                            checkEndGame(); }
                }
                if ( mapId == 43 || mapId == 44 || mapId == 45) {
                    window->getMapObject(x,y).setPtCapture(-impact);
                    Ptrestant = window->getMapObject(x,y).getPtCapture();
                    if ( Ptrestant <= 0 ) { window->getMapObject(x,y).setId(-5);
                                            window->getMapObject(x,y).setPtCapture(20);
                                            checkEndGame(); }
                }
            }
            if (turn && !team) { // tour des bleus
                if ( mapId == 34 || mapId == 35 || mapId == 36 ){
                     window->getMapObject(x,y).setPtCapture(-impact);
                     Ptrestant = window->getMapObject(x,y).getPtCapture();
                     if ( Ptrestant <= 0 ) { window->getMapObject(x,y).setId(+9);
                                             window->getMapObject(x,y).setPtCapture(20);
                                             checkEndGame();}
                    }
                if ( mapId == 38 || mapId == 39 || mapId == 40 ){
                     window->getMapObject(x,y).setPtCapture(-impact);
                     Ptrestant = window->getMapObject(x,y).getPtCapture();
                     if ( Ptrestant <= 0 ) { window->getMapObject(x,y).setId(+5);
                                             window->getMapObject(x,y).setPtCapture(20);
                                             checkEndGame(); }
                    }
           }
      }
   }
}

void Game::updateMoneyTeam(bool team){
    int factoT = 0;
    int factoF = 0;
    for(int i=0 ;i<21;i++){
        for (int j=0; j<17; j++){
            int IDmap = getmapId(i,j);
                if (IDmap == 38 || IDmap == 39)  {
                   factoT += 1;
                }
                if (IDmap == 43 || IDmap == 44) {
                    factoF += 1;
            }
        }
     }

    if (team){
       setMoney(team, factoT*1000);
    }
    else {
        setMoney(team, factoF*1000);
    }
}

void Game::setMoney(bool team, int impact){
    if (team){
        moneyTeamT += impact;
    }
    else{
        moneyTeamF += impact;
    }
    window->updateMoneyTeam(moneyTeamT, moneyTeamF);
}

Unite* Game::getUnite(int x, int y){
    int a = getIndexUnit(x,y);
    if(a == -1)
        throw invalid_argument("Error : getUnite");
    return unite[a];
}

bool Game::isActiveturn()
{
    return activeTurn;
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
            default: std::cout << "Type inconnu (f) " <<  std::endl; break;
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
            default: std::cout << "Type inconnu (f) " <<  std::endl; break;
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
            default: std::cout << "Type inconnu (f) " <<  std::endl; break;
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
            default: std::cout << "Type inconnu (t) " <<  std::endl; break;
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
            default: std::cout << "Type inconnu (a) " <<  std::endl; break;
        }
    }
    return 0;
}

int Game::attackChart(Unite* u, Unite* v)
{
    int a=u->getId();
    int d=v->getId();
    if(u->getId()>299){
        a-=100;
    }
    if(v->getId()>299){
        d-=100;
    }

    switch (a) {
    case (200): switch (d){ //inf
        case (200) : return 55; //inf
        case (201) : return 45; //mech
        case (202) : return 12; //recon
        case (203) : return 5; //antiair
        case (204) : return 5; //tank
        case (205) : return 1; //mdtank
        case (206) : return 1; //megatank
        case (207) : return 1; //neotank
        case (208) : return 7; //helico
        case (209) : return 0; //fighter
        case (210) : return 0; //bomber
        }
    case (201): switch (d){ //mech
        case (200) : return 65; //inf
        case (201) : return 55; //mech
        case (202) : return 85; //recon
        case (203) : return 65; //antiair
        case (204) : return 55; //tank
        case (205) : return 15; //mdtank
        case (206) : return 5; //megatank
        case (207) : return 15; //neotank
        case (208) : return 9; //helico
        case (209) : return 0; //fighter
        case (210) : return 0; //bomber
        }
    case (202): switch (d){ //recon
        case (200) : return 70; //inf
        case (201) : return 65; //mech
        case (202) : return 35; //recon
        case (203) : return 4; //antiair
        case (204) : return 6; //tank
        case (205) : return 1; //mdtank
        case (206) : return 1; //megatank
        case (207) : return 1; //neotank
        case (208) : return 12; //helico
        case (209) : return 0; //fighter
        case (210) : return 0; //bomber
        }
    case (203): switch (d){ //antiair
        case (200) : return 105; //inf
        case (201) : return 105; //mech
        case (202) : return 60; //recon
        case (203) : return 45; //antiair
        case (204) : return 25; //tank
        case (205) : return 10; //mdtank
        case (206) : return 1; //megatank
        case (207) : return 5; //neotank
        case (208) : return 120; //helico
        case (209) : return 65; //fighter
        case (210) : return 75; //bomber
        }
    case (204): switch (d){ //tank
        case (200) : return 75; //inf
        case (201) : return 70; //mech
        case (202) : return 85; //recon
        case (203) : return 65; //antiair
        case (204) : return 55; //tank
        case (205) : return 15; //mdtank
        case (206) : return 10; //megatank
        case (207) : return 15; //neotank
        case (208) : return 10; //helico
        case (209) : return 0; //fighter
        case (210) : return 0; //bomber
        }
    case (205): switch (d){ //mdtank
        case (200) : return 105; //inf
        case (201) : return 95; //mech
        case (202) : return 105; //recon
        case (203) : return 105; //antiair
        case (204) : return 85; //tank
        case (205) : return 55; //mdtank
        case (206) : return 25; //megatank
        case (207) : return 45; //neotank
        case (208) : return 12; //helico
        case (209) : return 0; //fighter
        case (210) : return 0; //bomber
        }
    case (206): switch (d){ //megatank
        case (200) : return 55; //inf
        case (201) : return 125; //mech
        case (202) : return 195; //recon
        case (203) : return 195; //antiair
        case (204) : return 180; //tank
        case (205) : return 125; //mdtank
        case (206) : return 65; //megatank
        case (207) : return 115; //neotank
        case (208) : return 22; //helico
        case (209) : return 0; //fighter
        case (210) : return 0; //bomber
        }
    case (207): switch (d){ //neotank
        case (200) : return 125; //inf
        case (201) : return 115; //mech
        case (202) : return 125; //recon
        case (203) : return 85; //antiair
        case (204) : return 105; //tank
        case (205) : return 75; //mdtank
        case (206) : return 35; //megatank
        case (207) : return 55; //neotank
        case (208) : return 22; //helico
        case (209) : return 0; //fighter
        case (210) : return 0; //bomber
        }
    case (208): switch (d){ //helico
        case (200) : return 75; //inf
        case (201) : return 75; //mech
        case (202) : return 55; //recon
        case (203) : return 25; //antiair
        case (204) : return 55; //tank
        case (205) : return 25; //mdtank
        case (206) : return 10; //megatank
        case (207) : return 20; //neotank
        case (208) : return 65; //helico
        case (209) : return 0; //fighter
        case (210) : return 0; //bomber
    }
    case (209): switch (d){ //fighter
        case (200) : return 0; //inf
        case (201) : return 0; //mech
        case (202) : return 0; //recon
        case (203) : return 0; //antiair
        case (204) : return 0; //tank
        case (205) : return 0; //mdtank
        case (206) : return 0; //megatank
        case (207) : return 0; //neotank
        case (208) : return 100; //helico
        case (209) : return 100; //fighter
        case (210) : return 55; //bomber
    }
    case (210): switch (d){ //helico
        case (200) : return 110; //inf
        case (201) : return 110; //mech
        case (202) : return 105; //recon
        case (203) : return 95; //antiair
        case (204) : return 105; //tank
        case (205) : return 95; //mdtank
        case (206) : return 35; //megatank
        case (207) : return 105; //neotank
        case (208) : return 0; //helico
        case (209) : return 0; //fighter
        case 210: return 0; //bomber
        default: return 0;
        }
    }
    return 0;
}



//////////////// FIN DU JEU

void Game::checkEndGame(){

    bool noBuildingBlue = true;
    bool noUnitBlue = true;

    bool noBuildingOrange = true;
    bool noUnitOrange = true;

    for(int i=0 ;i<21;i++){
            for (int j=0; j<17; j++){
                int mapId = getmapId(i,j);
                if ( mapId ==  43 || mapId == 44 || mapId == 45) { // Il y a un batiment bleu
                    noBuildingBlue = false;
                }
                if ( mapId == 38 || mapId == 39 || mapId == 40) {  // Il y a un batiment orange
                    noBuildingOrange = false;
                }
            }
    }

    for (Unite* u : unite){
        if ( u->isTeam()){
            noUnitOrange = false;
        }
        if ( !u->isTeam()){
            noUnitBlue = false;
        }
    }

   if ( noBuildingOrange && noUnitOrange ) { victoireBleu(); }
   if (  noBuildingBlue && noUnitBlue) { victoireOrange(); }
}

void Game::victoireOrange(){
    //endGame();
    diaWinOrange = new OrangeStarWin(window);
    diaWinOrange->show();
}

void Game::victoireBleu(){
    //endGame();
    diaWinBlue = new BlueMoonWin(window);
    diaWinBlue->show();
}

void Game::endGame(){

    int i = 0;
    for(Unite* u : unite) {
        delete u;
        unite.erase(unite.begin() + i);
        i++;
    }
    //window->getMap()->reload();
    delete diaBuyAirBM;
    delete diaBuyAirOS;
    delete diaBuyTerreBM;
    delete diaBuyTerreOS;
    delete diaWinBlue;
    delete diaWinOrange;

    setMoney(true,-moneyTeamT);
    setMoney(false,-moneyTeamF);
    window->updateInfoPos("",0,0,false,false,0,false,0,true);

    diaNewGame = new DialogNewGame(window);
    diaNewGame->show();
}

void Game::restart(int gameType){

    delete diaNewGame;

    window->createMapObjects();

    turnChange();
    giveBuildingsPtCapture();
    if (gameType == 5){
        window->close();
    }
    setgameType(gameType);

}

Game::~Game(){
    for(Unite* u : unite) {
        delete u;
    }
    delete diaBuyAirBM;
    delete diaBuyAirOS;
    delete diaBuyTerreBM;
    delete diaBuyTerreOS;
    delete diaWinBlue;
    delete diaWinOrange;
    delete diaNewGame;
}
