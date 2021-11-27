#ifndef Knight_H
#define Knight_H
#include "chessPieces.h"
class Knight : public ChessPieces {
    public:
    Knight(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<std::vector<Position>> getPossibleMoves() override;
};

#endif