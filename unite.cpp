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

void Unite::receiveDamage(double dmg)
{
    m_vie-=dmg;
    if (m_vie <0) m_vie=0;
    m_vie=floor(m_vie);

}

int Unite::getVie()
{
    return m_vie;
}

char Unite::getTypeMovement()
{
    return m_deplacementype;
}

Unite::~Unite()
{
    delete this;
}
