#include "king.h"
#include "position.h"
#include "board.h"

King::King(Position p, int identifier, bool isFirstMove) 
    : ChessPieces(p, identifier, isFirstMove), isInCheck{false}{
    if(identifier==1) {
        icon='K';
    } else {
        icon='k';
    }
}
// King (v|h|d *1)
//      +1v || -1v || +1h || -1h
//      +1v+1h || +1v-1h || -1v+1h || -1v-1h
// *castling*
std::vector<PossibleMove> King::getPossibleMoves(const Board & board) {

}