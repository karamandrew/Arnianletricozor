#ifndef BUILDING_H
#define BUILDING_H
#include"gameobject.h"


class Building : public Gameobject
{

public:
    Building(int x, int y, int type, bool team);

private:
    int m_ptCapture=20;
    int m_team;


};

#endif // BUILDING_H
