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
    int t = (int)y-1;


    if ( m >= 0 && m < 21 && t >= 0 && t < 17
         && getIndexUnit(Xfoc,Yfoc) != -1
         && unite[getIndexUnit(Xfoc,Yfoc)]->isFocused()
         && window->getMapObject(m,t).isAccessible() )  {  // Unité selectionné

        unsigned int indexUnitFoc = (int)getIndexUnit(Xfoc,Yfoc);

        unite[indexUnitFoc]->setPosX(m);
        unite[indexUnitFoc]->setPosY(t);

        setMapObjectfalse();
        if (Enemyclose(unite[indexUnitFoc])){
            std::cout << " Ennemi a cote " << std::endl;
            window->redraw();
            unite[indexUnitFoc]->setTurn(false);
            return;
        }
       // indexUnitFoc = (int)getIndexUnit(Xfoc,Yfoc);
        unite[indexUnitFoc]->setFocused(false);
        unite[indexUnitFoc]->setTurn(false);
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

void Game::selectUnits(QMouseEvent *e){

    float x = floorf(e->x()/40);
    float y = floorf(e->y()/40);
    int m = (int)x-7;
    int t = (int)y-1;
    int IDmap = getmapId(m, t);

    std::cout << " Test pour capture " << window->getMapObject(m,t).getPtCapture() << std::endl;

    if (getIndexUnit(m,t) == -1){

        if ( IDmap == 39 && activeTurn == true){
            // Créatio unités terrestre orange
            diaBuyTerreOS = new DialogBuyTerre(window);
            diaBuyTerreOS->show();
            diaBuyTerreOS->getInfo( m, t, true);
        }

        if ( IDmap == 40 && activeTurn == true){
            // Création unités aériennes orange
            diaBuyAirOS = new DialogBuyAir(window);
            diaBuyAirOS->show();
            diaBuyAirOS->getInfo( m, t, true);
        }

        if ( IDmap == 44 && activeTurn == false){
            // Création unités terrestres bleues
            diaBuyTerreBM = new DialogBuyTerre(window);
            diaBuyTerreBM->show();
            diaBuyTerreBM->getInfo( m, t, false);
        }

        if (IDmap == 45 && activeTurn == false){
            // Création unités aériennes bleues
            diaBuyAirBM = new DialogBuyAir(window);
            diaBuyAirBM->show();
            diaBuyAirBM->getInfo( m, t, false);
        }
    }
}


void Game::start(MainWindow &wind)
{
    window = &wind;
    window->setFixedSize(1400,865);
    window->createMapObjects();

    //Infantry *osinf = new Infantry( 13, 13, 300, true); unite.push_back(osinf);
    //Infantry *bminf = new Infantry( 12, 12, 200, false); unite.push_back(bminf);
    turnChange();  // NE PAS ENLEVER PERMET DE SET UP LA MONEY DES TEAM

    giveBuildingsPtCapture();


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

    double Game::calculDegat(Unite* u, Unite* v)
    {
        double B = attackChart(u,v);
        double A_HP = u->getVie();
        double D_TR = window->getMapObject(v->getPosX(), v->getPosY()).getDefense();
        double D_HP = v->getVie();
        if (v->getTypeMovement()=='a'){
            D_TR=0;
        }
        std::cerr << (B * ( A_HP / 10 ) * ( ( 100 - D_TR * D_HP) / 100 ))/10 << std::endl;
        return  (B *( A_HP / 10 ) * ( ( 100 - D_TR * D_HP) / 100 ))/10 ;

        //return attack(u, v) * u->getVie()/10*(100-window->getMapObject(v->getPosX(), v->getPosY()).getDefense()*v->getVie())/100;

        /*Damage = B * A_HP / 10 * (100 - D_TR * D_HP) / 100

Damage est exprimé sur 100, on doit donc diviser par 10 pour obtenir le nombre de points de vie.
B, dépend des unités en jeu, (voir la matrice dans Damage Chart),
A_HP, un entier entre 1 et 10, Points de vie de l'attaquant,
D_TR, un entier entre 0 et 4, Points de défense lié au terrain (voir Terrain Chart) (toujours zéro pour les unités aériennes),
D_HP, un entier entre 1 et 10, Points de vie du défenseur.*/

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
        //std::cerr << "getMapId out of the map" << std::endl;
        return -1;
    }
    else {
        return window->getMapObject(x, y).getId();
    }

}

void Game::turnChange(){
    //RESET TOUTES LES UNITES SELECTIONEE ET LES DALLES SELECTIONNEEs
    for(Unite* u: unite){
        u->setAttackable(false);
        u->setFocused(false);
    }
    setMapObjectfalse();
    capture(activeTurn);
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
    window->redraw();
}

void Game::capture(bool turn){
    for(Unite* u: unite){
        int IDu = u->getId();
        int x = u->getPosX();
        int y = u->getPosY();
        int mapId = getmapId(x,y);
        int impact = u->getVie();
        int Ptrestant;
        if ( IDu == 200 || IDu == 201 || IDu == 300 || IDu == 301 ){ // INfantry or mech
            if (turn) { // tour des oranges
                if ( mapId == 34 || mapId == 35 || mapId == 36 ){
                    window->getMapObject(x,y).setPtCapture(-impact);
                    Ptrestant = window->getMapObject(x,y).getPtCapture();
                    if ( Ptrestant <= 0 ) { window->getMapObject(x,y).setId(+4); window->getMapObject(x,y).setPtCapture(20); }
                    std::cout << "hello" << std::endl;
                }
                if ( mapId == 43 || mapId == 44 || mapId == 45) {
                    window->getMapObject(x,y).setPtCapture(-impact);
                    Ptrestant = window->getMapObject(x,y).getPtCapture();
                    if ( Ptrestant <= 0 ) { window->getMapObject(x,y).setId(-5); window->getMapObject(x,y).setPtCapture(20); }
                }
            }
            else { // tour des bleus
                if ( mapId == 34 || mapId == 35 || mapId == 36 ){
                     window->getMapObject(x,y).setPtCapture(-impact);
                     Ptrestant = window->getMapObject(x,y).getPtCapture();
                     if ( Ptrestant <= 0 ) { window->getMapObject(x,y).setId(+9); window->getMapObject(x,y).setPtCapture(20);}
                    }
                if ( mapId == 38 || mapId == 39 || mapId == 40 ){
                     window->getMapObject(x,y).setPtCapture(-impact);
                     Ptrestant = window->getMapObject(x,y).getPtCapture();
                     if ( Ptrestant <= 0 ) { window->getMapObject(x,y).setId(+5); window->getMapObject(x,y).setPtCapture(20); }
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
        throw invalid_argument("la fin des haricots");
    return unite[a];
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
    case (200): switch (d){
        case (200) : return 55;
        case (201) : return 45;
        case (202) : return 12;
        case (203) : return 5;
        case (204) : return 5;
        case (205) : return 1;
        case (206) : return 1;
        case (207) : return 1;
        case (208) : return 7;
        case (209) : return 0;
        case (210) : return 0;
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

void Game::attack(QMouseEvent *e)
{
    float x = floorf(e->x()/40);
    float y = floorf(e->y()/40);
    int m = (int)x-7;
    int t = (int)y-1;

    if(getIndexUnit(m,t)!=-1 && !unite[getIndexUnit(m,t)]->isFocused()){
        if(unite[getIndexUnit(m,t)]->isAttackable()){

            for(Unite* a: unite){
                if (a->isFocused()){

                    std::cout << "Point de vie unite attaquee avant " <<unite[getIndexUnit(m,t)]->getVie() << std::endl;
                    unite[getIndexUnit(m,t)]->receiveDamage(calculDegat(a,unite[getIndexUnit(m,t)]));  //attaque
                    std::cout << "Point de vie unite attaquee apres " <<unite[getIndexUnit(m,t)]->getVie() << std::endl;

                    std::cout << "Point de vie unite qui attaque avant " <<a->getVie() << std::endl;
                    a->receiveDamage(calculDegat(unite[getIndexUnit(m,t)],a));  //contreattaque
                    std::cout << "Point de vie unite qui attaque apres " <<a->getVie() << std::endl;

                    a->setTurn(false);

                    if(unite[getIndexUnit(m,t)]->getVie()<=0){
                        delete unite[getIndexUnit(m,t)];
                        unite.erase(unite.begin() + getIndexUnit(unite[getIndexUnit(m,t)]->getPosX(), unite[getIndexUnit(m,t)]->getPosY()));
                        window->redraw();
                    }
                    for(Unite* set:unite){
                        set->setAttackable(false);
                        set->setFocused(false);
                    }
                    window->redraw();
                    return;
                }
                else if(a->isFocused() && a->isTeam()==activeTurn){
                    for(Unite* set:unite){
                        set->setAttackable(false);
                        set->setTurn(false);
                        set->setFocused(false);
                    }
                    window->redraw();
                }
            }
        }
    }
    else{
        for(Unite* a: unite){
            if(a->isAttackable()){
                for(Unite* b: unite){
                    b->setFocused(false);
                }
            }
            a->setAttackable(false);
        }
    }
}
