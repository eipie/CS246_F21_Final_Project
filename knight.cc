#include "knight.h"
#include "position.h"
#include "board.h"

Knight::Knight(Position p, int identifier, bool isFirstMove) : ChessPieces(p, identifier, isFirstMove){
    if(identifier==1) {
        icon='N';
    } else {
        icon='n';
    }
}

// Knight 
//      +1v+2h || +2v+1h || -1v+2h || -2v+1h
//      +1v-2h || +2v-1h || -1v-2h || -2v-1h
std::vector<PossibleMove> Knight::getPossibleMoves(const Board & board) {
    checkOpponent=false;
    std::vector<PossibleMove> possMoves;
    int x =pos.x;
    int y =pos.y;
    Position candidate1{x+1, y+2};
    Position candidate2{x+2, y+1};
    Position candidate3{x+2, y-1};
    Position candidate4{x+1, y-2};
    Position candidate5{x-1, y+2};
    Position candidate6{x-2, y+1};
    Position candidate7{x-2, y-1};
    Position candidate8{x-1, y-2};
    // (if x+1 <= 8 && y+2 <= 8) ?????
    tryAddNextMoveCandidate(board, possMoves, candidate1);
    tryAddNextMoveCandidate(board, possMoves, candidate2);
    tryAddNextMoveCandidate(board, possMoves, candidate3);
    tryAddNextMoveCandidate(board, possMoves, candidate4);
    tryAddNextMoveCandidate(board, possMoves, candidate5);
    tryAddNextMoveCandidate(board, possMoves, candidate6);
    tryAddNextMoveCandidate(board, possMoves, candidate7);
    tryAddNextMoveCandidate(board, possMoves, candidate8);
}