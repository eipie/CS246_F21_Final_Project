#include "knight.h"
#include "position.h"

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
std::shared_ptr<std::vector<Position>> Knight::getPossibleMoves() {

}