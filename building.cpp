#include "building.h"


Building::Building(int x, int y, int type, bool team): Gameobject (x,y,type)
{
    m_team=team;
}
