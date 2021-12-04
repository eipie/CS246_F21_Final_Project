#ifndef King_H
#define King_H
#include "chessPieces.h"
class King : public ChessPieces {
    bool isKingNextToKing(Position candidate, const Board & board);
    bool Kingsidecastle(const Board & board);
    bool Queensidecastle(const Board & board);
    public:
    King(Position p, int identifier, bool isFirstMove=true);
    std::shared_ptr<ChessPieces> clone( bool needToCheckSelfCheck) override;
    King(const King &piece,  bool needToCheckSelfCheck);
    std::vector<PossibleMove> getPossibleMoves(const Board & board) override;
};

#endif