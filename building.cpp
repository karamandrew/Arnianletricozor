#include "building.h"


Building::Building(int x, int y, int Id, int defense, bool team): Terrain ( x, y, Id, defense)
{
    m_team = team;
}
