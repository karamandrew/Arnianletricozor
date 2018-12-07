#include "terrain.h"

Terrain::Terrain(int x, int y, int Id, int pointmouv) : Gameobject (x, y, Id)
{
    m_pointmouv=pointmouv;
}

int Terrain::getPointmouv(Unite u)
{
    return m_pointmouv;
}
