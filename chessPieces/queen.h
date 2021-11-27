#ifndef Queen_H
#define Queen_H
#include "chessPieces.h"
class Queen : public ChessPieces {
    public:
    Queen(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<std::vector<Position>> getPossibleMoves() override;
};

#endif