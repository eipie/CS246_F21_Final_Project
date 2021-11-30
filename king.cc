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
    std::vector<PossibleMove> possMoves;
    int x =pos.x;
    int y =pos.y;
    // horizontal moves:
    // check right
    Position candidate{x+1,y};
    // if ther is no king at the following:
    // (x+2, y), (x+2, y+1), (x+2, y-1)
    // then:
    int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);

    // check left
    Position candidate{x-1,y};
    // if ther is no king at the following:
    // (x-2, y), (x-2, y+1), (x-2, y-1)
    // then:
    int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);

    // check up
    Position candidate{x,y+1};
    // if ther is no king at the following:
    // (x, y+2), (x-1, y+2), (x+1, y+2)
    // then:
    int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);

    // check down
    Position candidate{x,y-1};
    // if ther is no king at the following:
    // (x, y-2), (x-1, y-2), (x+1, y-2)
    // then:
    int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);

    //diagonal moves:
    // check up right
    Position candidate{x+1,y+1};
    // if ther is no king at the following:
    // (x+2, y), (x+2, y+1), (x+2, y+2), (x+1, y+2), (x, y+2)
    // then:
    int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);

    // check up left
    Position candidate{x-1,y+1};
    // if ther is no king at the following:
    // (x-2, y), (x-2, y+1), (x-2, y+2), (x-1, y+2), (x, y+2)
    // then:
    int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);

    // check down left
    Position candidate{x-1,y+1};
    // if ther is no king at the following:
    // (x-2, y), (x-2, y-1), (x-2, y-2), (x-1, y-2), (x, y-2)
    // then:
    int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);

    // check down right
    Position candidate{x-1,y+1};
    // if ther is no king at the following:
    // (x, y-2), (x+1, y-2), (x+2, y-2), (x+2, y-1), (x+2, y)
    // then:
    int tryAddResult = tryAddNextMoveCandidate(board, possMoves, candidate);

    return possMoves;   
}