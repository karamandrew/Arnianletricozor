#ifndef INFANTRY_H
#define INFANTRY_H
#include "unite.h"

class Infantry : public Unite
{
public:
    Infantry(int x, int y, int Id, bool team);
};

#endif // INFANTRY_H
