#ifndef LAKE_H
#define LAKE_H
#include "terrain.h"

class Lake : public Terrain
{
public:
    Lake(int x, int y, int type);
};

#endif // LAKE_H
