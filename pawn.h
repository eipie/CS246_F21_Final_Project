#ifndef Pawn_H
#define Pawn_H
#include "chessPieces.h"
class Pawn : public ChessPieces {
    void addEnPassantIfPoss(Position to, Position captureLoc, std::vector<PossibleMove> & possMoves, const Board & board);
    public:
    Pawn(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<ChessPieces> clone( bool needToCheckSelfCheck) override;
    Pawn(const Pawn &piece,  bool needToCheckSelfCheck);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif