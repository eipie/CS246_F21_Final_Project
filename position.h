#ifndef POSITION_H
#define POSITION_H
struct Position
{
    int x;
    int y;
    bool operator==(Position p) {
        return (x==p.x && y==p.y);
    }
};

#endif