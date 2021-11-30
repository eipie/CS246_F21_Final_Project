#ifndef Knight_H
#define Knight_H
#include "chessPieces.h"
class Knight : public ChessPieces {
    public:
    Knight(Position p, int identifier, bool isFirstMove=true);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif