#include "unite.h"
#include <cmath>
Unite::Unite(int x, int y, int Id, bool team, int prix, int MP, char deplacementype): Gameobject (x, y, Id), m_MP(MP), m_prix(prix), m_team(team), m_deplacementype(deplacementype)
{

}

int Unite::getMP()
{
    return m_MP;
}

void Unite::setTurn(bool turn)
{
    m_turn = turn;
}

bool Unite::isTurn()
{
    return m_turn;
}

bool Unite::isTeam()
{
    return m_team;
}

bool Unite::isAttackable()
{
    return m_attackable;
}

void Unite::setAttackable(bool set)
{
    m_attackable=set;
}

void Unite::receiveDamage(double dmg)
{
    m_vie-= dmg;
    if(m_vie<0){
        m_vie=0;
    }
}

int Unite::getVie()
{
    return m_vie;
}

void Unite::setVie(int impact){
    m_vie += impact;
    if (m_vie > 10) { m_vie = 10;}
}

int Unite::getPrix(){
    return m_prix;
}

char Unite::getTypeMovement()
{
    return m_deplacementype;
}

bool Unite::isFusionnable(){
    return m_fusionnable;
}

void Unite::setFusionnable(bool set){
    m_fusionnable = set;
}


