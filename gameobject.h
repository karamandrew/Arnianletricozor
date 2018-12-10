#ifndef Gameobject_H
#define Gameobject_H

#include <QPainter>
#include <iostream>
#include <string>
using namespace std;

class Gameobject
{
public:
    Gameobject(int initX,int initY,int ID) ;
    Gameobject() ;
    int getPosX() const;
    void setPosX(int value);
    int getPosY() const;
    void setPosY(int value);
    int getId() const;
    bool isFocused() const;
    void setFocused(bool value);
    bool isAccessible() const;
    void setAccessible(bool value);
    string getDirectory() const;

private:
    int m_posX;
    int m_posY;
    int m_ID;
    string m_directory;
    bool focused;
    QPixmap picture();
    int m_direction;
    bool m_accessible;
};
#endif // Gameobject_H
