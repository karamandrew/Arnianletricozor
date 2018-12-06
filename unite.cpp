#include "unite.h"

Unite::Unite(int x, int y, int type, bool team, int prix, int pointaction, char deplacementype): Gameobject (x, y, type), m_pointaction(pointaction), m_prix(prix), m_team(team), m_deplacementype(deplacementype)
{

}

int Unite::getPointaction()
{
    return m_pointaction;
}
