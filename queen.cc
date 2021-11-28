#include "queen.h"
#include "position.h"

Queen::Queen(Position p, int identifier, bool isFirstMove) : ChessPieces(p, identifier, isFirstMove){
    if(identifier==1) {
        icon='Q';
    } else {
        icon='q';
    }
}

// Queen (v|h|d *n)
//      +nv || -nv || +nh || -nh
//      +nv+nh || +nv-nh || -nv+nh || -nv-nh
std::shared_ptr<std::vector<Position>> Queen::getPossibleMoves() {

}