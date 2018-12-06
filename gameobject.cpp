#include <QPainter>
#include "gameobject.h"


Gameobject::Gameobject(int x, int y, int type): m_posX(x), m_posY(y), m_type(type), focused(false)
{
    switch(type){
    case(1): m_directory=":/Res/Terrains/sea.gif"; break;
    case(2): m_directory=":/Res/Terrains/plain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    // case(7): m_directory=":/Res/Units/geinfantry.gif"; break;
    case(7): m_directory=":/Res/Terrains/esriver.gif"; break;
    case(8): m_directory=":/Res/Terrains/swriver.gif"; break;
    case(9): m_directory=":/Res/Terrains/wnriver.gif"; break;
    case(10): m_directory=":/Res/Terrains/enriver.gif"; break;
    case(15): m_directory=":/Res/Terrains/nesriver.gif"; break;
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
        /*
    case(92): m_directory=":/Res/Terrains/blackholebase.gif"; break;
    case(95): m_directory=":/Res/Terrains/blackholehq.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
    case(3): m_directory=":/Res/Terrains/mountain.gif"; break;
        */
    default: std::cout << "Type inconnu"; break;
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

void Gameobject::setPosY(int value)
{
    m_posY = value;
}

int Gameobject::getId() const
{
    return m_type;
}

bool Gameobject::getFocused() const
{
    return focused;
}

void Gameobject::setFocused(bool value)
{
    focused = value;
}

void Gameobject::setPosX(int value)
{
    m_posX = value;
}



