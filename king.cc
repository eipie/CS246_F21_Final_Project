#include "king.h"
#include "position.h"
#include "board.h"
#include "move.h"

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
    std::vector<int> change = {-1,0,1};
    for(int x_change:change) {
        for(int y_change:change) {
            Position candidate;
            candidate.x=x+x_change;
            candidate.y=y+y_change;
            if(!(candidate==pos)) {
                if(!isKingNextToKing(candidate, board)) {
                    tryAddNextMoveCandidate(board, possMoves, candidate);
                }
            }
        }
    }
    if (Kingsidecastle(board)) {
        tryAddNextMoveCandidate(board, possMoves, pos_king_w);
    }
    if (Queensidecatle(board)) {
        
    }
}


bool King::Queensidecastle(const Board & board) {
    //white king
    if (board.getPieceCharAt(Position{5, 1}) == 'K') {
        if (!isFirstMove) {
            return false;
        }
        if (board.getPieceCharAt(Position{1, 1}) != 'R') {
            return false;
        }
        if (!((board.getPieceAt(Position{1, 1}))->isFirstMove)) { //???
            return false;
        }
        Move newMove;
        newMove.from = Position{5, 1};
        newMove.to = Position{4, 1};
        if (isCurrentPlayerKingInCheckAfterMove(newMove)) {
            return false;
        }
        newMove.to = Position{3, 1};
        if (isCurrentPlayerKingInCheckAfterMove(newMove)) {
            return false;
        }
        Move rookMove; 
        rookMove.from = Position{1, 1}; 
        rookMove.to = Position{4, 1}; // create new Position from and to for Rook
        if (isCurrentPlayerKingInCheckAfterMove(rookMove)) {
            return false;
        }
        return true;
    } 
    //black king
    else if (board.getPieceCharAt(Position{5, 8}) == 'k') {
                if (!isFirstMove) {
            return false;
        }
        if (board.getPieceCharAt(Position{1, 8}) != 'r') {
            return false;
        }
        if (!((board.getPieceAt(Position{1, 1}))->isFirstMove)) { //???
            return false;
        }
        Move newMove;
        newMove.from = Position{5, 8};
        newMove.to = Position{4, 8};
        if (isCurrentPlayerKingInCheckAfterMove(newMove)) {
            return false;
        }
        newMove.to = Position{3, 8};
        if (isCurrentPlayerKingInCheckAfterMove(newMove)) {
            return false;
        }
        Move rookMove; 
        rookMove.from = Position{1, 8}; 
        rookMove.to = Position{4, 8}; // create new Position from and to for Rook
        if (isCurrentPlayerKingInCheckAfterMove(rookMove)) {
            return false;
        }
        return true;
    }
    return false;
}



bool Kingsidecatle(const Board & board) {
    //white king
    if (board.getPieceCharAt(Position{5, 1}) == 'K') {
        if (!isFirstMove) {
            return false;
        }
        if (board.getPieceCharAt(Position{8, 1}) != 'R') {
            return false;
        }
        if (!((board.getPieceAt(Position{8, 1}))->isFirstMove)) { //???
            return false;
        }
        Move newMove;
        newMove.from = Position{5, 1};
        newMove.to = Position{6, 1};
        if (isCurrentPlayerKingInCheckAfterMove(newMove)) {
            return false;
        }
        newMove.to = Position{7, 1};
        if (isCurrentPlayerKingInCheckAfterMove(newMove)) {
            return false;
        }
        Move rookMove; 
        rookMove.from = Position{8, 1}; 
        rookMove.to = Position{6, 1}; // create new Position from and to for Rook
        if (isCurrentPlayerKingInCheckAfterMove(rookMove)) {
            return false;
        }
        return true;
    } 
    //black king
    else if (board.getPieceCharAt(Position{5, 8}) == 'k') {
                if (!isFirstMove) {
            return false;
        }
        if (board.getPieceCharAt(Position{8, 8}) != 'r') {
            return false;
        }
        if (!((board.getPieceAt(Position{8, 8}))->isFirstMove)) { //???
            return false;
        }
        Move newMove;
        newMove.from = Position{5, 8};
        newMove.to = Position{6, 8};
        if (isCurrentPlayerKingInCheckAfterMove(newMove)) {
            return false;
        }
        newMove.to = Position{7, 8};
        if (isCurrentPlayerKingInCheckAfterMove(newMove)) {
            return false;
        }
        Move rookMove; 
        rookMove.from = Position{8, 8}; 
        rookMove.to = Position{6, 8}; // create new Position from and to for Rook
        if (isCurrentPlayerKingInCheckAfterMove(rookMove)) {
            return false;
        }
        return true;
    }
    return false;
}


/*bool King::ifCastling(Move nextMove, const Board & board) {
    Position from = nextMove.from;
    Position to = nextMove.to;
    Position rook1{1, 1};
    Position rook2{8, 1};
    Position rook3{1, 8};
    Position rook4{8, 8};
    if (board.getPieceCharAt(from) == 'K') {
        if (isFirstMove && 
        ((to.x == 7 && to.y == 1 && board.getPieceCharAt(rook2) == 'R') || 
        (to.x == 3 && to.y == 1 && board.getPieceCharAt(rook1) == 'R'))) {
            return true;
        }
    } else if (board.getPieceCharAt(from) == 'k') {
        if (isFirstMove && 
        ((to.x == 7 && to.y == 8 && board.getPieceCharAt(rook4) == 'r') || 
        (to.x == 3 && to.y == 8 && board.getPieceCharAt(rook3) == 'r'))) {
            return true;
        }       
    }
    return false;
}

bool King::CastlingisAllowed(Move nextMove, const Board & board) {
    Position from = nextMove.from;
    if(isFirstMove && (!isInCheck))  {

    }
    return false;
    // getPieceAt()
}*/

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

//bool isCastleAndValid(Move nextMove, const Board & board) {
  //  return ifCastling(nextMove, board) && CastlingisAllowed(nextMove, board);
//}


/* 
    // horizontal moves:
    // check right
    Position candidate1{x+1,y};
    if(!isKingNextToKing(candidate1, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate1);
    }
    // check left
    Position candidate2{x-1,y};
    if(!isKingNextToKing(candidate2, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate2);
    }
    // check up
    Position candidate3{x,y+1};
    if(!isKingNextToKing(candidate3, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate3);
    }

    // check down
    Position candidate4{x,y-1};
    if(!isKingNextToKing(candidate4, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate4);
    }
    //diagonal moves:
    // check up right
    Position candidate5{x+1,y+1};
    if(!isKingNextToKing(candidate5, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate5);
    }
    // check up left
    Position candidate6{x-1,y+1};
    if(!isKingNextToKing(candidate6, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate6);
    }
    // check down left
    Position candidate7{x-1,y+1};
    if(!isKingNextToKing(candidate7, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate7);
    }
    // check down right
    Position candidate8{x-1,y+1};
    if(!isKingNextToKing(candidate8, board)) {
        tryAddNextMoveCandidate(board, possMoves, candidate8);
    }
    // find all castling if possible
    // emplace
    return possMoves;   
}
 */