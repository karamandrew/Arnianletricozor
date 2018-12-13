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
    int getPtCapture();
    void setPtCapture(int impact);
private:
    int m_defense;
    int m_PtCapture = 0;
};

#endif // TERRAIN_H
