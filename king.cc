#include "king.h"
#include "position.h"

King::King(Position p, int identifier, bool isFirstMove) : ChessPieces(p, identifier, isFirstMove){
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
std::shared_ptr<std::vector<Position>> King::getPossibleMoves() {

}