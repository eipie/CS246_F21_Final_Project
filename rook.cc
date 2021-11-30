#include "rook.h"
#include "position.h"
// #include "possibleMove.h"

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
std::vector<PossibleMove> Rook::getPossibleMoves(const Board & board) {
    std::vector<PossibleMove> possMoves;
    int x =pos.x;
    int y =pos.y;
    // check right
    for(int i=x+1; i<=8; i++) {
        Position candidate{i,y};
        int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);
        if(tryAddResult==-1||tryAddResult==1) {
            break;
        }
    }
    // check backwards
    for(int i=y-1; i>=1; i--) {
        Position candidate{x,i};
        int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);
        if(tryAddResult==-1||tryAddResult==1) {
            break;
        }
    }

    // check left
    for(int i=x-1; i>=1; i--) {
        Position candidate{i,y};
        int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);
        if(tryAddResult==-1||tryAddResult==1) {
            break;
        }
    }
    // check forward
    for(int i=y+1; i<=8; i++) {
        Position candidate{x,i};
        int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);
        if(tryAddResult==-1||tryAddResult==1) {
            break;
        }
    }
    return possMoves;
}