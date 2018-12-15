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

Map::Map(QWidget *parent) : QWidget(parent)
{

}

void Map::paintEvent(QPaintEvent *event)
{
    Game& game = Game::Instance();
    QPainter painter(this);

    QPixmap accessible(":/Res/Animations/Misc.png");
    QPixmap focused(":/Res/Animations/Focused.png");
    QPixmap attackable(":/Res/Animations/swords.png");
    QPixmap fusionnable(":/Res/Animations/coeur.svg");

    for(int i=0 ;i<21;i++){
        int m = i+7;
        for (int j=0; j<17; j++){
           int t = j+1;
           QPixmap pictureMap(mapObject[i][j]->getDirectory().c_str());
           painter.drawPixmap(m*40, t*40, 40, 40, pictureMap);

           if (mapObject[i][j]->isAccessible()) {
               painter.drawPixmap(m*40, t*40, 40, 40, accessible);
           }

           if (game.getIndexUnit(i,j) != -1) {
               QPixmap pictureUnits(game.getUnite(i,j)->getDirectory().c_str());
               painter.drawPixmap(m*40,t*40,40,40,pictureUnits);

               if (!game.getUnite(i,j)->isTurn() && !game.getUnite(i,j)->isAttackable()) {
                   QRect *rect = new QRect(m*40,t*40,40,40);
                   painter.fillRect(*rect, QBrush(QColor(100,100,100,155)));
               }

               if (game.getUnite(i,j)->isFocused()) {
                   painter.drawPixmap(m*40, t*40, 40, 40, focused);
               }

               if (game.getUnite(i,j)->isAttackable()) {
                   painter.drawPixmap(m*40, t*40, 40, 40, attackable);
               }
               if (game.getUnite(i,j)->isFusionnable()){
                   painter.drawPixmap(m*40, t*40, 40, 40, fusionnable);
               }
           }
        }
    }
}

void Map::mousePressEvent(QMouseEvent *m)
{
    Game& game = Game::Instance();

    if(m->buttons() == Qt::LeftButton){
        game.mouseLeftPressed(game.getXCoordinate(m),game.getYCoordinate(m));
    }

    if(m->buttons() == Qt::RightButton){
        game.mouseRightPressed(game.getXCoordinate(m),game.getYCoordinate(m));
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

    for(int i=0; i<21; i++){
        for(int j=0; j<17; j++){
            switch(bitse[j][i]){

            // Terrains

                case 1 :            mapObject[i][j] = new Plain(i,j); break;
                case 2 :            mapObject[i][j] = new Mountain(i,j); break;
                case 3 :            mapObject[i][j] = new Wood(i,j); break;
                case 4 ... 14 :     mapObject[i][j] = new River(i,j, bitse[j][i]); break;
                case 15 ... 25 :    mapObject[i][j] = new Road(i,j, bitse[j][i]); break;
                case 26 ... 27 :    mapObject[i][j] = new Bridge(i,j, bitse[j][i]); break;
                case 28 :           mapObject[i][j] = new Lake(i,j, bitse[j][i]); break;
                case 29 ... 32 :    mapObject[i][j] = new Shoal(i,j, bitse[j][i]); break;
                case 33 :           mapObject[i][j] = new Reef(i,j); break;
                case 101 ... 110 :  mapObject[i][j] = new Pipe(i,j, bitse[j][i]); break;


             // Buildings

                // City
                case 34 : mapObject[i][j] = new Ville(i,j, bitse[j][i]); break; //Neutral
                case 38 : mapObject[i][j] = new Ville(i,j, bitse[j][i]); break; // Orange
                case 43 : mapObject[i][j] = new Ville(i,j, bitse[j][i]); break; // Blue
                // Base
                case 35 : mapObject[i][j] = new Base(i,j, bitse[j][i]); break; //Neutral
                case 39 : mapObject[i][j] = new Base(i,j, bitse[j][i]); break; // Orange
                case 44 : mapObject[i][j] = new Base(i,j, bitse[j][i]); break; // Blue
                // Airport
                case 36 : mapObject[i][j] = new Airport(i,j, bitse[j][i]); break; //Neutral
                case 40 : mapObject[i][j] = new Airport(i,j, bitse[j][i]); break; // Orange
                case 45 : mapObject[i][j] = new Airport(i,j, bitse[j][i]); break;  // Blue
            }
        }
    }
}

void Map::redraw()
{
    this->repaint();
}

Terrain& Map::getmapObject(int i, int j)
{
    if( !(0 <= i && i < 21 && 0 <= j && j < 17) ){
        throw std::invalid_argument("getmapObject out of the tab");
    }
    else {
        return *mapObject[i][j];
    }

}

Map::~Map() {
    for(int i=0 ;i<21;i++){
            for (int j=0; j<17; j++){
                delete &getmapObject(i,j);
            }
   }
}
