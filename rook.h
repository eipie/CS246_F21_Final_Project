#ifndef ROOK_H
#define ROOK_H
#include "chessPieces.h"
class Rook : public ChessPieces {
    public:
    Rook(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<std::vector<Position>> getPossibleMoves() override;
};

#endif