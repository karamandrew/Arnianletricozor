#include "terrain.h"

Terrain::Terrain(int x, int y, int Id, int def) : Gameobject (x, y, Id)
{
    m_defense=def;
}

int Terrain::getDefense()
{
    return m_defense;
}
int Terrain::getPtCapture(){
    return  m_PtCapture;
}
void Terrain::setPtCapture(int impact){
    m_PtCapture += impact;
}

