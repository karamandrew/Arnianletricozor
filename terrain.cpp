#include "terrain.h"

Terrain::Terrain(int x, int y, int Id, int def) : Gameobject (x, y, Id)
{
    m_defense=def;
}

