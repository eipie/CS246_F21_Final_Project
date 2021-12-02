#ifndef Pawn_H
#define Pawn_H
#include "chessPieces.h"
class Pawn : public ChessPieces {
    void addEnPassantIfPoss(Position to, Position captureLoc, std::vector<PossibleMove> & possMoves, const Board & board);
    public:
    Pawn(Position p, int identifier, bool isFirstMove=true);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif