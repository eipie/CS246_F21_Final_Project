#ifndef Pawn_H
#define Pawn_H
#include "chessPieces.h"
class Pawn : public ChessPieces {
    public:
    bool availableForEnPassant;
    virtual void afterFirstMove() override;
    Pawn(Position p, int identifier, bool isFirstMove=true);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif