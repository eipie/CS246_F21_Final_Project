#ifndef Queen_H
#define Queen_H
#include "chessPieces.h"
class Queen : public ChessPieces {
    public:
    Queen(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<ChessPieces> clone( bool needToCheckSelfCheck) override;
    Queen(const Queen &piece,  bool needToCheckSelfCheck);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif