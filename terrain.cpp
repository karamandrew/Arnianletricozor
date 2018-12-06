#include "terrain.h"

Terrain::Terrain(int x, int y, int type, int pointmouv) : Gameobject (x, y, type)
{
    m_pointmouv=pointmouv;
}

int Terrain::getPointmouv(Unite u)
{
    return m_pointmouv;
}
