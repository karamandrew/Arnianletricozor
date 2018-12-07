#ifndef VILLE_H
#define VILLE_H
#include "building.h"


class Ville : public Building
{
public:
    Ville(int x, int y, int id, bool team);
};

#endif // VILLE_H
