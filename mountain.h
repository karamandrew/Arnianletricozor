#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include "terrain.h"

class Mountain : public Terrain
{
public:
    Mountain(int x, int y);
    int getPointmouv(Unite u);
};

#endif // MOUNTAIN_H
