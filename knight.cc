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

}