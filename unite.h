#ifndef UNITE_H
#define UNITE_H
#include "gameobject.h"

class Unite : public Gameobject
{
public:
    Unite(int x, int y, int Id, bool team, int prix, int MP, char deplacementype);
    int getMP();
    char getTypeMovement(); // Si fonctions redéfinies dans les classes filles -> ajouté virtual ici
private:
    int m_MP;
    int m_vie=10;
    int m_prix;
    bool m_team;
    char m_deplacementype;
};

#endif // UNITE_H
