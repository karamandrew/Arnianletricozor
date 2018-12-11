#ifndef UNITE_H
#define UNITE_H
#include "gameobject.h"

class Unite : public Gameobject
{
public:
    Unite(int x, int y, int Id, bool team, int prix, int MP, char deplacementype);
    int getMP();
    void setTurn(bool turn);
    bool isTurn();
    bool isTeam();
    void receiveDamage(int dmg);
    int getVie();
    char getTypeMovement(); // Si fonctions redéfinies dans les classes filles -> ajouté virtual ici
private:
    int m_MP;
    int m_vie=10;
    int m_prix;
    bool m_team;
    char m_deplacementype;
    bool m_turn=true;
};

#endif // UNITE_H
