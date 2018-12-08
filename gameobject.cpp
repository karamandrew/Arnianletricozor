#include <QPainter>
#include "gameobject.h"


Gameobject::Gameobject(int x, int y, int ID): m_posX(x), m_posY(y), m_ID(ID), focused(false), m_accessible(false)
{
    switch(m_ID){
    case(1): m_directory=":/Res/Terrains/plain.gif"; break;
    case(2): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/wood.gif"; break;
    case(4): m_directory=":/Res/Terrains/hriver.gif"; break;
    case(5): m_directory=":/Res/Terrains/vriver.gif"; break;
    case(7): m_directory=":/Res/Terrains/esriver.gif"; break;
    case(8): m_directory=":/Res/Terrains/swriver.gif"; break;
    case(9): m_directory=":/Res/Terrains/wnriver.gif"; break;
    case(10): m_directory=":/Res/Terrains/neriver.gif"; break;
    case(15): m_directory=":/Res/Terrains/hroad.gif"; break;
    case(16): m_directory=":/Res/Terrains/vroad.gif"; break;
    case(18): m_directory=":/Res/Terrains/esroad.gif"; break;
    case(19): m_directory=":/Res/Terrains/swroad.gif"; break;
    case(20): m_directory=":/Res/Terrains/wnroad.gif"; break;
    case(21): m_directory=":/Res/Terrains/neroad.gif"; break;
    case(22): m_directory=":/Res/Terrains/eswroad.gif"; break;
    case(23): m_directory=":/Res/Terrains/swnroad.gif"; break;
    case(24): m_directory=":/Res/Terrains/wneroad.gif"; break;
    case(25): m_directory=":/Res/Terrains/nesroad.gif"; break;
    case(26): m_directory=":/Res/Terrains/hbridge.gif"; break;
    case(29): m_directory=":/Res/Terrains/hshoal.gif"; break;
    case(30): m_directory=":/Res/Terrains/hshoaln.gif"; break;
    case(33): m_directory=":/Res/Terrains/reef.gif"; break;
    case(34): m_directory=":/Res/Terrains/neutralcity.gif"; break;
    case(35): m_directory=":/Res/Terrains/neutralbase.gif"; break;
    case(36): m_directory=":/Res/Terrains/neutralairport.gif"; break;
    case(38): m_directory=":/Res/Terrains/orangestarcity.gif"; break;
    case(39): m_directory=":/Res/Terrains/orangestarbase.gif";break;
    case(40): m_directory=":/Res/Terrains/orangestarairport.gif";break;
    case(43): m_directory=":/Res/Terrains/bluemooncity.gif";break;
    case(44): m_directory=":/Res/Terrains/bluemoonbase.gif";break;
    case(45): m_directory=":/Res/Terrains/bluemoonairport.gif";break;
    case(101): m_directory=":/Res/Terrains/vpipe.gif"; break;
    case(102): m_directory=":/Res/Terrains/hpipe.gif"; break;
    case(104): m_directory=":/Res/Terrains/espipe.gif"; break;
    case(106): m_directory=":/Res/Terrains/wnpipe.gif"; break;
    case(107): m_directory=":/Res/Terrains/npipeend.gif"; break;
    case(108): m_directory=":/Res/Terrains/epipeend.gif"; break;
    case(109): m_directory=":/Res/Terrains/spipeend.gif"; break;
    case(110): m_directory=":/Res/Terrains/wpipeend.gif"; break;


    case(200): m_directory=":/Res/Units/geinfantry.gif"; break; // Unit

    default: std::cout << "Type inconnu, ID : "<< m_ID <<  std::endl; break;
    }
}
Gameobject::Gameobject()
{
}

string Gameobject::getDirectory() const{
    return m_directory;
}

int Gameobject::getPosX() const
{
    return m_posX;
}

int Gameobject::getPosY() const
{
    return m_posY;
}

void Gameobject::setPosX(int value)
{
    m_posX = value;
}

void Gameobject::setPosY(int value)
{
    m_posY = value;
}

int Gameobject::getId() const
{
    return m_ID;
}

bool Gameobject::getFocused() const
{
    return focused;
}

void Gameobject::setFocused(bool value)
{
    focused = value;
}

bool Gameobject::isAccessible() const {
    return m_accessible;
}

void Gameobject::setAccessible(bool value){
    m_accessible = value;
}





