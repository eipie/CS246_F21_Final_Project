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


bool King::isKingNextToKing(Position candidate, const Board & board) {
    // check all surrounding 8 squares, make sure it is not original position
    // -1 0 1
    std::vector<int> change = {-1,0,1};
    for(int x:change) {
        for(int y:change) {
            Position neighbour;
            neighbour.x=x+candidate.x;
            neighbour.y=y+candidate.y;
            if(!(neighbour==candidate)&&!(neighbour==pos)) {
                char ifKing = board.getPieceCharAt(neighbour);
                if(ifKing=='k' || ifKing == 'K') {
                    return true;
                }
            }
        }
    }
    return false;
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
/*     if((board.getPieceCharAt(Position{x+2, y})==('k'||'K'))|| ) {

    } */
    if(!isKingNextToKing(candidate, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate);
    }
    

    // check left
    candidate.x = x-1;
    candidate.y= y;
    // Position candidate{x-1,y};
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



// first detect special case
    // bool isCastleAndValid();
        // Detect castling (1&&2)
        // 1. check if move is castling
        // ifCastling(Move nextMove);
            // if white(capital letter), then legal castling 
            // move e1 g1
            // move e1 c1
            //  else if black (lower case letter), then legal castling
            // move e8 g8
            // move e8 c8
            // AND
            // if getPieceCharAt(ex) == 'K'/'k' based on the current player's color
            // AND
            // if getPieceCharAt(ax||hx) == 'R'/'r' based on the current player's color
        // 2. check if castling is allowed
            // AND
            // if king isFirstMove==true
            // AND
            // if King isInCheck==false
            // AND
            // if rook at Position ax||hx isFirstMove=true;
            // AND
            // getPieceCharAt(fx) and (gx) are ' ' (empty)
            // AND
            // Move newMove;
            // newMove.from = ex
            // newMove.to = fx || dx
            // isCurrentPlayerKingInCheckAfterMove(newMove) == false
            // AND
            // Move rookMove; // create new Position from and to for Rook
            // moves.emplace(nextMove);
            // moves.emplace(rookMove);
            // isCurrentPlayerKingInCheckAfterMove(vector<Move> moves) == false;
        // 3. finally move both King and Rook
            // move Board.makeAMove Rook
        // return true;