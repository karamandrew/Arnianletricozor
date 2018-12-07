#include "game.h"
#include <iostream>
#include "math.h"
#include "infantry.h"
#include "gameobject.h"
#include "unite.h"

Game Game::gInstance=Game();
Game::Game()
{


}
Game &Game::Instance()
{
    return gInstance;
}

void Game::move(QMouseEvent *e)
{


    if(gameobject[Xfoc][Yfoc].getFocused()){

        std::cout<<"test" << std::endl;

        float x=floorf(e->x()/40);
        float y=floorf(e->y()/40);
        int m= (int)x-7;
        int t= (int)y-2;

        int distx = abs(Xfoc-m);
        int disty = abs(Yfoc-t);

        if( distx + disty <=3){

        gameobject[Xfoc][Yfoc].setPosX(m);
        gameobject[Xfoc][Yfoc].setPosY(t);
        if((m!=Xfoc || t!=Yfoc) && gameobject[m][t].getId()!=200){
             gameobject[m][t]=gameobject[Xfoc][Yfoc];
             gameobject[Xfoc][Yfoc] = *new Gameobject((int) Xfoc,(int) Yfoc,444);}
        std::cout<< "gameobject[posXselec][posYselec]="<< gameobject[Xfoc][Yfoc].getId()  <<std::endl;


        gameobject[m][t].setFocused(false);
        window->redraw();
        }
        else{
            gameobject[Xfoc][Yfoc].setFocused(false);
        }
    }
    else{
        float x=(e->x()/40);
        float y=(e->y()/40);
        int m= (int)x-7;
        int t= (int)y-2;

        std::cout<<"test3" << std::endl;
        std::cout<<"testpos" << "x = " << x << " y = " << y << std::endl;
        std::cout<<"testpos" << "m = " << m << " t = " << t << std::endl; // OK CA FONCTIONNE BIEN

        int id = gameobject[m][t].getId();

        std::cout<<"id : " << id << std::endl;

       if( gameobject[m][t].getId()==200 ){    // If Infantry / Unite ?

            std::cout<<"test2" << std::endl;

            /*
            //char typemovement = dynamic_cast<Unite>(gameobject[m][t].getTypeMovement) ; // Tentative de cast
            //(Unite) gameobject[m][t].getTypeMovement; // Tentative 2  Elle est def dans Unite mais ça fct pas
            // for(std::vector<Unite>::Unite u = vect.begin() ; u != vect.end(); u++ )
            // FAIRE UN GET MOUVEMENT TYPE
            char typemovement = 'f';  // Infantry
            int typeterrain = 10 // Plaine
            if (typemovement == 'f' ){
                    if (typterrain == 10){
                        unite.setPtMouv(unite.getPtMouv - 1)
                        }
            }
            */

             gameobject[m][t].setFocused(true);

             Xfoc=m;
             Yfoc=t;
       }
    }
}


// AUtre version de move Incorrect

/*void Game::move(QMouseEvent *e)
{

    if(units[getplaceunit(Xfoc, Yfoc)].getFocused()){

        float x=floorf(e->x()/40);
        float y=floorf(e->y()/40);
        int m= (int)x-7;
        int t= (int)y-2;

        int distx = abs(Xfoc-m);
        int disty = abs(Yfoc-t);

        if( distx + disty <=3){

        units[getplaceunit(Xfoc, Yfoc)].setPosX(m);
        units[getplaceunit(Xfoc, Yfoc)].setPosY(t);
        if((m!=Xfoc || t!=Yfoc) && units[getplaceunit(m, t)].getId()!=7){
             units[getplaceunit(m, t)]=units[getplaceunit(Xfoc, Yfoc)];
        }

        units[getplaceunit(m, t)].setFocused(false);
        window->redraw();
        }
        else{
            units[getplaceunit(Xfoc, Yfoc)].setFocused(false);
        }
    }
    else{
        float x=(e->x()/40);
        float y=(e->y()/40);
        int m= (int)x-7;
        int t= (int)y-2;
       if( units[getplaceunit(m, t)].getId()==7 ){

             units[getplaceunit(m, t)].setFocused(true);

             Xfoc=m;
             Yfoc=t;
       }
    }
}


*/


void Game::start(MainWindow &wind)
{
    window = &wind ;
    Infantry inf(0,9,200,true);
    Infantry inf2(20,9,200,false);
    unite.push_back(inf);
    unite.push_back(inf2);


    std::cout << "i1 et i2 :" << getIndexUnit(0,9) << getIndexUnit(20,9) << std::endl; // FONCTIONNE
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


Gameobject Game::getgameobject(int x, int y)
{
    return gameobject[x][y];

}

