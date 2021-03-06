#ifndef ROOK_H
#define ROOK_H
#include "chessPieces.h"
class Rook : public ChessPieces {
    public:
    Rook(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<ChessPieces> clone( bool needToCheckSelfCheck) override;
    Rook(const Rook &piece, bool needToCheckSelfCheck);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif