#ifndef POSITION_H
#define POSITION_H
struct Position
{
    int x;
    int y;
    bool operator==(Position p) const{
        return (x==p.x && y==p.y);
    }
    bool operator<(const Position& p) const { 
        return (x < p.x) || (x==p.x && y < p.y); 
    }
    Position& operator=(const Position& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
};

#endif