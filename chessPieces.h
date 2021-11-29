#ifndef CHESSPIECES_H
#define CHESSPIECES_H
#include <memory>
#include <vector>
#include "position.h"
class ChessPieces {
    // 0:black; 1:white;
    int ownerIdentifier;
    bool isFirstMove;
    
    // std::shared_ptr<std::vector<Position>> possibleMoves;
    public:
    // void makingAMove(Position form, Position to);
    // if(isFirstMove==true);
            // all pieces except Pawn:
            // change isFirstMove=false;
            // for Pawn:
            // 1) to.y-from.y == 1
            //      change isFirstMove=false;
            // 1) to.y-from.y == 2;
            //      change isFirstMove=false;
    // else 
    //      do nothing
    Position pos;
    char icon;
    ChessPieces(Position p, int identifier, bool isFirstMove=true);
    virtual std::shared_ptr<std::vector<Position>> getPossibleMoves() = 0;
};
#endif