#include "unite.h"

Unite::Unite(int x, int y, int Id, bool team, int prix, int pointaction, char deplacementype): Gameobject (x, y, Id), m_pointaction(pointaction), m_prix(prix), m_team(team), m_deplacementype(deplacementype)
{

}

int Unite::getPointaction()
{
    return m_pointaction;
}

char Unite::getTypeMovement()
{
    return m_deplacementype;
}
