#ifndef CHESSPIECES_H
#define CHESSPIECES_H
#include <memory>
#include <vector>
#include "position.h"
#include "board.h"
#include "possibleMove.h"
class ChessPieces {
    // 0:black; 1:white;
    int ownerIdentifier;
    protected:
    bool isFirstMove;
    // return 0: if candidate is empty, add success
    // return 1: if candidate is enemy, add success
    // return -1: if candidate is currentPlayer's piece, add fail;
    int tryAddNextMoveCandidate(const Board & board, std::vector<PossibleMove> & possibleMove, Position candidate);

    public:
    // void makingAMove(Position form, Position to);
    // if(isFirstMove==true);
            // all pieces except Pawn:
            // change isFirstMove=false;
            // for Pawn:
            // 1) to.y-from.y == 1
            //      change isFirstMove=false;
            // 1) to.y-from.y == 2;
            //      change isFirstMove=false;
    // else 
    //      do nothing
    Position pos;
    char icon;
    ChessPieces(Position p, int identifier, bool isFirstMove=true);
    virtual std::vector<PossibleMove> getPossibleMoves(const Board & board) = 0;
    
    // change isFirstMove to false if true; special case for Pawn
    virtual void afterFirstMove();

    
};
#endif