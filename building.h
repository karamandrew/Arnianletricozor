#ifndef BUILDING_H
#define BUILDING_H
#include"terrain.h"

class Building : public Terrain
{

public:
    Building(int x, int y, int Id, int defense);

};

#endif // BUILDING_H
