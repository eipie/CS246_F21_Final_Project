#ifndef King_H
#define King_H
#include "chessPieces.h"
class King : public ChessPieces {
    public:
    bool isInCheck;
    King(Position p, int identifier, bool isFirstMove=true);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif