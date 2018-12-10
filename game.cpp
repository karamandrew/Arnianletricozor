#include "game.h"
#include <iostream>
#include "math.h"
#include "infantry.h"
#include "gameobject.h"
#include "unite.h"

Game Game::gInstance=Game();
Game::Game(){}
Game &Game::Instance()
{
    return gInstance;
}

void Game::move(QMouseEvent *e)
{
    float x=floorf(e->x()/40); float y=floorf(e->y()/40);
    int m= (int)x-7; int t= (int)y-2;



    if (unite[getIndexUnit(Xfoc,Yfoc)].getFocused()){  // Unité selectionné

        int indexUnitFoc = getIndexUnit(Xfoc,Yfoc);

        if ( window->getMapObject(m,t).isAccessible() ) {

            unite[indexUnitFoc].setPosX(m); unite[indexUnitFoc].setPosY(t);
            unite[indexUnitFoc].setFocused(false);

        }


    }

    else if ( getIndexUnit(m,t) != 444) {


        unite[getIndexUnit(m,t)].setFocused(true);

        window->getMapObject(0,0).setAccessible(true);

        //calculatePosAccessible(m,t, getIndexUnit(m,t), unite[getIndexUnit(m,t)].getMP());

        Xfoc=m;
        Yfoc=t;


    }

    window->redraw();
}



void Game::start(MainWindow &wind)
{
    window = &wind ;
    Infantry inf(0,9,200,true);
    Infantry inf2(20,9,200,false);
    Infantry inf3(2,2,200,true);

    unite.push_back(inf);
    unite.push_back(inf2);
    unite.push_back(inf3);

    window->createMapObjects();

    window->redraw();
}



int Game::getIndexUnit(int x, int y)
{

    for (int i=0; i<((int)unite.size()); i++){

        if (unite[i].getPosX()==x && unite[i].getPosY()==y){
            return i;

        }
    }
    return 444;
}


void Game::calculatePosAccessible(int currentX, int currentY, int indexUnit, int mp){

         std::cout << "Heloooooo" << std::endl;

         window->getMapObject(0,0).setAccessible(true);

         // MTN ON DOIT RENDRE LES BONNES ACCESSIBLES



         /*

         if (mp==0){return;}
         char MovType = unite[indexUnit].getTypeMovement();
         int mpleft = mp;
         int around[4][3];



         window->getMapObject(currentX,currentY).setAccessible(true);

         around[0][0]=getMalusMove(MovType, getmapId(currentX-1, currentY));
         around[0][1]=currentX-1; around[0][2]=currentY;
         around[1][0]=getMalusMove(MovType, getmapId(currentX+1, currentY));
         around[1][1]=currentX+1; around[1][2]=currentY;
         around[2][0]=getMalusMove(MovType, getmapId(currentX, currentY-1));
         around[2][1]=currentX; around[2][2]=currentY-1;
         around[3][0]=getMalusMove(MovType, getmapId(currentX, currentY+1));
         around[3][1]=currentX; around[3][2]=currentY+1;
         if(!window->getMapObject(around[0][1],around[0][2]).isAccessible() && around[0][0]<=around[1][0] && around[0][0]<=around[2][0] && around[0][0]<=around[3][0] && around[0][0]<=mpleft){
             calculatePosAccessible(around[0][1], around[0][2], indexUnit, mpleft-around[0][0]);
         }
         else if(!window->getMapObject(around[1][1],around[1][2]).isAccessible() && around[1][0]<=around[0][0] && around[1][0]<=around[2][0] && around[1][0]<=around[3][0] && around[1][0]<=mpleft){
             calculatePosAccessible(around[0][1], around[0][2], indexUnit, mpleft-around[1][0]);
         }
         else if(!window->getMapObject(around[2][1],around[2][2]).isAccessible() && around[2][0]<=around[1][0] && around[2][0]<=around[0][0] && around[2][0]<=around[3][0] && around[2][0]<=mpleft){
             calculatePosAccessible(around[0][1], around[0][2], indexUnit, mpleft-around[2][0]);
         }
         else if(!window->getMapObject(around[3][1],around[3][2]).isAccessible() && around[3][0]<=mpleft){
             calculatePosAccessible(around[0][1], around[0][2], indexUnit, mpleft-around[3][0]);
         }
         else {return;}



         */
}



int Game::getmapId(int x, int y){
    return window->getMapObject(x, y).getId();
}


int Game::getMalusMove(char moveType, int terrainID){
    if (moveType == 'f'){
            switch (terrainID) {
                        case 1 : return 1 ;
                        case 2 : return 2 ;
                        case 3 : return 1 ;
                        case 4 ... 14 : return 2 ;
                        case 15 ... 25 : return 1 ;
                        case 26 ... 27 :return 1 ;
                        case 28 :return 1000 ;  // LAKE
                        case 29 ... 32 :return 1 ;
                        case 33 :return 1000 ;  // REEF
                        case 101 ... 110 :return 1000 ; // PIPE

                        case 34 ... 36 : return 1 ;
                        case 43 ... 45 : return 1 ;
                        case 38 ... 40 : return 1 ;

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

                    }

    }
    else {
        std::cout << "Error : getMalusMove : wrong MoveType" << std::endl;
        return 0;
    }
}

Unite Game::getUnite(int x, int y){
    return unite[getIndexUnit(x,y)];
}

