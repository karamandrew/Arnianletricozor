#ifndef POS_H
#define POS_H

class Pos
{

public:
    Pos();

    void setX(int x);
    int getX() const&;

    void setY(int y);
    int getY() const&;


private:
    int m_x;
    int m_y;

};
    Pos operator+(Pos const& a, Pos const& b);
    int operator-(Pos const& a, Pos const& b);
    bool operator==(Pos const& a, Pos const& b);

#endif // POS_H
