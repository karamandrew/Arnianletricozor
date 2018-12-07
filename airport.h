#ifndef AIRPORT_H
#define AIRPORT_H
#include"building.h"


class Airport : public Building
{
public:
    Airport(int x, int y, int Id, bool team);
};

#endif // AIRPORT_H
