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
    bool isAttackable();
    void setAttackable(bool set);
    void receiveDamage(double dmg);
    int getVie();
    void setVie(int impact);
    char getTypeMovement(); // Si fonctions redéfinies dans les classes filles -> ajouté virtual ici
    int getPrix();

    bool isFusionnable();
    void setFusionnable(bool set);
    int arrondirDegat(double deg);



private:
    int m_MP;
    int m_vie=10;
    int m_prix;
    bool m_attackable=false;
    bool m_team;
    char m_deplacementype;
    bool m_turn=true;

    bool m_fusionnable = false;
};

#endif // UNITE_H
