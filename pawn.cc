#include "pawn.h"
#include "position.h"
#include "board.h"

Pawn::Pawn(Position p, int identifier, bool isFirstMove) : ChessPieces(p, identifier, isFirstMove){
    if(identifier==1) {
        icon='P';
    } else {
        icon='p';
    }
}

void Pawn::afterFirstMove() {
    if(isFirstMove) { 
        isFirstMove = false;
        availableForEnPassant = true; //should consider if it has moved two squares or one??
    } else {
        availableForEnPassant = false;
    }
}
// Pawn
// ** En passant must be available, or else -1v +1v can't do it!
// if (caputreCase: enemy piece +-1v+1h)
//      +1v+1h || -1v+1h
// else if (captureCase: -1v || +1v)
//      +1v+1h || -1v+1h    <- capture = Position pos
// else if (firstMove)
//      +1v || +2v
// else
//      +1v 
//      
// *promotion*
std::vector<PossibleMove> Pawn::getPossibleMoves(const Board & board) {
    std::vector<PossibleMove> possMoves;
    int x = pos.x;
    int y = pos.y;
    Position candidate1{x, y+2};
    Position candidate2{x, y+1};
    Position candidate3{x+1, y+1};
    Position candidate4{x-1, y+1};
    if (isFirstMove && board.getPieceCharAt(candidate1) == ' ') {
        tryAddNextMoveCandidate(board, possMoves, candidate1);
    }
    if (board.getPieceCharAt(candidate2) == ' ') {
        tryAddNextMoveCandidate(board, possMoves, candidate2);
    }
    if (!(board.isEmpty(candidate3)) && board.isOpponentPiece(candidate3, ownerIdentifier)) {
        tryAddNextMoveCandidate(board, possMoves, candidate3);
    }
    if (!(board.isEmpty(candidate4)) && board.isOpponentPiece(candidate4, ownerIdentifier)) {
        tryAddNextMoveCandidate(board, possMoves, candidate4);
    }
}