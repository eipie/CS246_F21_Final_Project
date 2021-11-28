#include "bishop.h"
#include "position.h"

Bishop::Bishop(Position p, int identifier, bool isFirstMove) : ChessPieces(p, identifier, isFirstMove){
    if(identifier==1) {
        icon='B';
    } else {
        icon='b';
    }
}
// Bishop (v|h|d *1)
//      +1v || -1v || +1h || -1h
//      +1v+1h || +1v-1h || -1v+1h || -1v-1h
// *castling*
std::shared_ptr<std::vector<Position>> Bishop::getPossibleMoves() {

}