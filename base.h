#ifndef BASE_H
#define BASE_H
#include"building.h"


class Base : public Building
{
public:
    Base(int x, int y, int type, bool team);
};

#endif // BASE_H
