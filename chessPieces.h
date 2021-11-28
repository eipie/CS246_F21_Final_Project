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
    Position pos;
    char icon;
    ChessPieces(Position p, int identifier, bool isFirstMove=true);
    virtual std::shared_ptr<std::vector<Position>> getPossibleMoves() = 0;
};
#endif