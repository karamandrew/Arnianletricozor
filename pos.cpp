#include "pos.h"

Pos::Pos()
{
    setX(-1);
    setY(-1);
}

void Pos::setX(int x)
{
    m_x=x;
}

int Pos::getX() const&
{
    return m_x;
}

void Pos::setY(int y)
{
    m_y=y;
}

int Pos::getY() const&
{
    return m_y;
}

Pos operator+(Pos const& a, Pos const& b){
    Pos n;
    n.setX(a.getX() + b.getX());
    n.setY(a.getY() + b.getY());
    return n;
}



bool operator==(Pos const& a, Pos const& b){
    if(a.getX()==b.getX() && a.getY()==b.getY()){
        return true;
    }
    else{
        return false;
    }
}

int operator-(Pos const& a, Pos const& b){
    int difx=0;
    int dify=0;

    if(a.getX()>b.getX()){
        difx=a.getX()-b.getX();
    }
    else{
        difx=b.getX()-a.getX();
    }
    if(a.getY()>b.getY()){
        dify=a.getY()-b.getY();
    }
    else{
        dify=b.getY()-a.getY();
    }

    return difx+dify;
}

