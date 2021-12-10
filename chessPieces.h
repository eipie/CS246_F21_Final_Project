#ifndef CHESSPIECES_H
#define CHESSPIECES_H
#include <memory>
#include <vector>
#include "position.h"
#include "board.h"
#include "possibleMove.h"

extern int HIGHER_BOUND;

class ChessPieces {
    // 0:black; 1:white;
    protected:
    // return 0: if candidate is empty, add success
    // return 1: if candidate is enemy, add success
    // return -1: if candidate is currentPlayer's piece, add fail;
    int tryAddNextMoveCandidate(const Board & board, std::vector<PossibleMove> & possibleMove, Position candidate);
    bool withinBound(Position candidate);
    bool isCurrentPlayerKingInCheckAfterMove(Move newMove, const Board & board);
    bool isCurrentPlayerKingInCheckAfterMove(PossibleMove newMove, const Board & board);

    public:
    int ownerIdentifier;
    bool isFirstMove=true;
    bool checkOpponent;
    bool availableForEnPassant = false;
    bool needCheckSelfCheck = true;
    Position pos;
    char icon;
    int weight = 0;
    ChessPieces(Position p, int identifier, bool isFirstMove=true);
    ChessPieces(const ChessPieces &chessPieces,  bool needToCheckSelfCheck);
    // helper for copy constructor
    virtual std::shared_ptr<ChessPieces> clone( bool needToCheckSelfCheck) =0;
    virtual std::vector<PossibleMove> getPossibleMoves(const Board & board) = 0;
    void setPos(const Position newPos);
    // change isFirstMove to false if true; special case for Pawn
    void afterFirstMove();
};
#endif