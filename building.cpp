#include "building.h"


Building::Building(int x, int y, int Id, bool team): Gameobject ( x, y, Id)
{
    m_team = team;
}
