#include "bishop.h"
#include "position.h"
#include "board.h"

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
std::vector<PossibleMove> Bishop::getPossibleMoves(const Board & board) {
    std::vector<PossibleMove> possMoves;
    int x =pos.x;
    int y =pos.y;
    // check up right
    int j = y + 1;
    for(int i=x+1; i<=8; i++) {
        Position candidate{i,j};
        int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);
        if (j > 8) {break;}
        if(tryAddResult==-1||tryAddResult==1) {
            break;
        }
        ++j;
    }
    // check up left
    int k = y + 1;
    for(int i=x-1; i>=1; i--) {
        if (k > 8) {break;}
        Position candidate{i,k};
        int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);
        if(tryAddResult==-1||tryAddResult==1) {
            break;
        }
        ++k;
    }

    // check down left
    int p = y - 1;
    for(int i=x-1; i>=1; i--) {
        if (p < 1) {break;}
        Position candidate{i,p};
        int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);
        if(tryAddResult==-1||tryAddResult==1) {
            break;
        }
        --p;
    }
    // check down right
    int q = y - 1;
    for(int i=x+1; i<=8; i++) {
        if (q < 1) {break;}
        Position candidate{i,q};
        int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);
        if(tryAddResult==-1||tryAddResult==1) {
            break;
        }
        --q;
    }
    return possMoves;
}