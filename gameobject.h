#ifndef Gameobject_H
#define Gameobject_H

#include <QPainter>
#include <iostream>
#include <string>
#include <pos.h>
using namespace std;

class Gameobject
{
public:
    Gameobject(int initX,int initY,int ID) ;
    Gameobject() ;

    void setPosX(int value);
    void setPosY(int value);
    void setId(int impact);
    void setFocused(bool value);
    void setAccessible(bool value);
    void setDirectory();

    int getPosX() const;
    int getPosY() const;
    int getId() const;

    bool isFocused() const;
    bool isAccessible() const;

    string getDirectory() const;
    Pos getPos();

private:
    int m_posX;
    int m_posY;
    int m_ID;
    int m_direction;

    bool focused;
    bool m_accessible;

    Pos pos;
    string m_directory;
};
#endif // Gameobject_H
