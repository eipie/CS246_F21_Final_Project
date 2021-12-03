#ifndef Bishop_H
#define Bishop_H
#include "chessPieces.h"
class Bishop : public ChessPieces {
    public:
    Bishop(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<ChessPieces> clone() override;
    Bishop(const Bishop &piece);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif