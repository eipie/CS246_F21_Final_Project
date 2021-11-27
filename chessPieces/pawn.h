#ifndef Pawn_H
#define Pawn_H
#include "chessPieces.h"
class Pawn : public ChessPieces {
    public:
    Pawn(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<std::vector<Position>> getPossibleMoves() override;
};

#endif