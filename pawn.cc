#include "pawn.h"
#include "position.h"

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
        availableForEnPassant = true;
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
std::shared_ptr<std::vector<Position>> Pawn::getPossibleMoves() {

}