#ifndef PLAIN_H
#define PLAIN_H
#include "terrain.h"

class Plain : public Terrain
{
public:
    Plain(int x, int y, int type);
};

#endif // PLAIN_H
