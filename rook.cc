#include "rook.h"
#include "position.h"

Rook::Rook(Position p, int identifier, bool isFirstMove) : ChessPieces(p, identifier, isFirstMove){
    if(identifier==1) {
        icon='R';
    } else {
        icon='r';
    }
}
// Rook (v|h *n)
//      +nv || -nv || +nh || -nh
// *castling*
std::shared_ptr<std::vector<Position>> Rook::getPossibleMoves() {
    std::shared_ptr<std::vector<Position>> possMoves;
    int x =pos.x;
    int y =pos.y;
    for(int i = 0; i <= 8; i++) {
        if(i!=x) {
            Position candidate{i,y};
            possMoves.get()->push_back(candidate);
        }
    }
    for(int i = 0; i <= 8; i++) {
        if(i!=y) {
            Position candidate{x,i};
            possMoves.get()->push_back(candidate);
        }
    }
    return possMoves;
}