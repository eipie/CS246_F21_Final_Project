#ifndef King_H
#define King_H
#include "chessPieces.h"
class King : public ChessPieces {
    public:
    King(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<std::vector<Position>> getPossibleMoves() override;
};

#endif