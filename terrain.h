#ifndef TERRAIN_H
#define TERRAIN_H
#include <string>
#include "gameobject.h"
#include "unite.h"

using namespace std;

class Terrain : public Gameobject
{
public:
    Terrain(int x, int y, int Id, int def);
    int getDefense();
private:
    int m_defense;
};

#endif // TERRAIN_H
