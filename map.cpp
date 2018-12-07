#include "map.h"
#include "game.h"
#include <QPainter>
#include <iostream>
#include <QMouseEvent>
#include "plain.h"
#include "mountain.h"
#include "gameobject.h"
#include "wood.h"
#include "river.h"
#include "road.h"
#include "bridge.h"
#include "shoal.h"
#include "reef.h"
#include "pipe.h"
#include "lake.h"
#include "city.h"
#include "base.h"
#include "airport.h"


Map::Map(QWidget *parent ) : QWidget(parent)
{

}

void Map::paintEvent(QPaintEvent *event)
{
    Game& game=Game::Instance();
    QPainter painter(this);
    for(int i=0 ;i<21;i++){
        int m=i+7;
        for (int j=0; j <17 ;j++){
           int t = j+2;
           QPixmap pictureMap((mapObject[j][i].getDirectory()).c_str()); //c_str permet de régler un probleme de string pour qpixmap
           painter.drawPixmap(m*40,t*40,40,40,pictureMap);

           if ( game.getIndexUnit(i,j) != 444 ){
               //QPixmap pictureUnits((game.getgameobject(i,j).getDirectory()).c_str());
               QPixmap pictureUnits((game.getUnite(i,j).getDirectory().c_str()));
               painter.drawPixmap(m*40,t*40,40,40,pictureUnits);
           }

        }

    }
}

void Map::mousePressEvent(QMouseEvent *m)
{

    if(m->buttons() == Qt::LeftButton){

        Game& game=Game::Instance();
        game.move(m);
    }
}


void Map::setmapobject()
{   // Game& game=Game::Instance();

    int bitse[17][21] =
 {{104,102,102,102,102,102,108,3,1,2,18,15,15,34,1,1,1,2,30,30,33},
{101,34,1,1,1,2,1,18,15,15,34,1,1,3,1,3,1,1,1,3,30},
{101,2,1,3,2,18,15,35,1,1,1,3,1,1,1,1,43,15,19,1,2},
{109,2,34,15,15,34,1,1,2,2,2,2,2,3,1,44,23,1,21,19,1},
{4,4,8,3,1,1,1,2,2,2,2,34,2,1,34,25,44,1,3,21,34},
{2,34,5,1,1,1,2,2,34,2,2,2,2,3,1,16,1,1,1,1,3},
{3,1,26,1,3,2,2,1,16,3,2,2,34,1,3,16,34,1,3,2,7},
{1,18,26,1,1,2,34,3,16,1,1,3,1,1,18,20,1,1,7,4,9},
{36,20,5,3,1,3,18,15,24,15,15,15,22,15,20,3,1,3,5,18,36},
{7,4,9,1,1,18,20,1,1,3,1,1,16,3,34,2,1,1,26,20,1},
{9,2,3,1,34,16,3,1,34,2,2,3,16,1,2,2,3,1,26,1,3},
{3,1,1,1,1,16,1,3,2,2,2,2,34,2,2,1,1,1,5,34,2},
{34,19,3,1,39,23,34,1,2,34,2,2,2,2,1,1,1,3,10,4,4},
{1,21,19,1,25,39,1,3,2,2,2,2,2,1,1,34,15,15,34,2,107},
{2,1,21,15,38,1,1,1,1,3,1,1,1,35,15,20,2,3,1,2,101},
{29,3,1,1,1,3,1,3,1,1,34,15,15,20,1,2,1,1,1,34,101},
{33,29,29,2,1,1,1,34,15,15,20,2,1,3,110,102,102,102,102,102,106}};


    for(int i=0; i<17; i++){
        for(int j=0; j<21; j++){
            switch(bitse[i][j]){

            // Terrains

                case 1 :            mapObject[i][j]= *new Plain(i,j); break;
                case 2 :            mapObject[i][j]= *new Mountain(i,j); break;
                case 3 :            mapObject[i][j]= *new Wood(i,j); break;
                case 4 ... 14 :     mapObject[i][j]= *new River(i,j, bitse[i][j]); break;
                case 15 ... 25 :    mapObject[i][j]= *new Road(i,j, bitse[i][j]); break;
                case 26 ... 27 :    mapObject[i][j]= *new Bridge(i,j, bitse[i][j]); break;
                case 28 :           mapObject[i][j]= *new Lake(i,j, bitse[i][j]); break;
                case 29 ... 32 :    mapObject[i][j]= *new Shoal(i,j, bitse[i][j]); break;
                case 33 :           mapObject[i][j]= *new Reef(i,j); break;
                case 101 ... 110 :  mapObject[i][j]= *new Pipe(i,j, bitse[i][j]); break;


             // Buildings

                // City
                case 34 : mapObject[i][j]= *new Ville(i,j, bitse[i][j], 0); break; //Neutral
                case 38 : mapObject[i][j]= *new Ville(i,j, bitse[i][j], 0); break; // Orange
                case 43 : mapObject[i][j]= *new Ville(i,j, bitse[i][j], 0); break; // Blue
                // Base
                case 35 : mapObject[i][j]= *new Base(i,j, bitse[i][j], 0); break; //Neutral
                case 39 : mapObject[i][j]= *new Base(i,j, bitse[i][j], 0); break; // Orange
                case 44 : mapObject[i][j]= *new Base(i,j, bitse[i][j], 0); break; // Blue
                // Airport
                case 36 : mapObject[i][j]= *new Airport(i,j, bitse[i][j], 0); break; //Neutral
                case 40 : mapObject[i][j]= *new Airport(i,j, bitse[i][j], 0); break; // Orange
                case 45 : mapObject[i][j]= *new Airport(i,j, bitse[i][j], 0); break;  // Blue

            }
;
        }
    }
}

void Map::redraw()
{
    this->repaint();
}

Gameobject Map::getmapObject(int i, int j)
{
    return mapObject[j][i]; // INVERSE CAR TABLEAU INVERSE
};


