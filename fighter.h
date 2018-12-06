#ifndef FIGHTER_H
#define FIGHTER_H
#include"unite.h"

class Fighter : public Unite
{
public:
    Fighter(int x, int y, int type, bool team);
};

#endif // FIGHTER_H
