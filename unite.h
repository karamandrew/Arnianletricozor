#ifndef UNITE_H
#define UNITE_H
#include "gameobject.h"

class Unite : public Gameobject
{
public:
    Unite(int x, int y, int type, bool team, int prix, int pointaction, char deplacementype);
    int getPointaction();
private:
    int m_pointaction;
    int m_vie=10;
    int m_prix;
    bool m_team;
    char m_deplacementype;
};

#endif // UNITE_H
