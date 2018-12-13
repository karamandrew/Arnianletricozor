#ifndef BUILDING_H
#define BUILDING_H
#include"terrain.h"


class Building : public Terrain
{

public:
    Building(int x, int y, int Id, int defense, bool team);
    //void impact();

private:
    //int m_ptCapture=20;
    int m_team;
};

#endif // BUILDING_H
