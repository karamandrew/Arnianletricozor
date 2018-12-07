#include "unite.h"

Unite::Unite(int x, int y, int Id, bool team, int prix, int MP, char deplacementype): Gameobject (x, y, Id), m_MP(MP), m_prix(prix), m_team(team), m_deplacementype(deplacementype)
{

}

int Unite::getMP()
{
    return m_MP;
}

char Unite::getTypeMovement()
{
    return m_deplacementype;
}
