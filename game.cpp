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

    if(gameobject[Xfoc][Yfoc].getFocused()){   // Object selectionné




        char MovType = unite[getIndexUnit(m,t)].getTypeMovement();
        int MP = unite[getIndexUnit(m,t)].getMP();

        int terrainID = window->getMapObject(m,t).getId();

        std::cout << "terrain ID : " << terrainID << std::endl;

        gameobject[Xfoc][Yfoc].setPosX(m);
        gameobject[Xfoc][Yfoc].setPosY(t);
        if((m!=Xfoc || t!=Yfoc) && gameobject[m][t].getId()!=200){
             gameobject[m][t]=gameobject[Xfoc][Yfoc];
             gameobject[Xfoc][Yfoc] = *new Gameobject((int) Xfoc,(int) Yfoc,444);}

        gameobject[m][t].setFocused(false);
        window->redraw();

    }
    else if (gameobject[m][t].getId()==200) {

        gameobject[m][t].setFocused(true);
        Xfoc=m;
        Yfoc=t;
    }
}



void Game::start(MainWindow &wind)
{
    window = &wind ;
    Infantry inf(0,9,200,true);
    Infantry inf2(20,9,200,false);

    unite.push_back(inf);
    unite.push_back(inf2);


    //std::cout << "i1 et i2 :" << getIndexUnit(0,9) << getIndexUnit(20,9) << std::endl; // FONCTIONNE
    gameobject[0][9]= inf;
    gameobject[20][9]= inf2;



    window->redraw();
}



int Game::getIndexUnit(int x, int y)
{
    for (int i=0; i<((int)unite.size()); i++){
        if (unite[i].getPosX()==x && unite[i].getPosY()==y){
            return i;
        }
    }
    return NULL;
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

Gameobject Game::getgameobject(int x, int y)
{
    return gameobject[x][y];

}

