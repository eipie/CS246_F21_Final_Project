#include "king.h"
#include "position.h"
#include "board.h"
#include "move.h"

King::King(Position p, int identifier, bool isFirstMove) 
    : ChessPieces(p, identifier, isFirstMove){
    if(identifier==1) {
        icon='K';
    } else {
        icon='k';
    }
}

std::shared_ptr<ChessPieces> King::clone() {
    return std::shared_ptr<ChessPieces>(new King(*this));
}
King::King(const King &piece) : ChessPieces(piece){
    
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
    checkOpponent=false;
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

    // ****
    // CAN"T CASTLE OUT OF CHECK
    // ****
    if(!board.ifInCheck(ownerIdentifier)) {
        if (Kingsidecastle(board)) {
            Position newKCastle;
            newKCastle.y = pos.y;
            newKCastle.x = 7;
            tryAddNextMoveCandidate(board, possMoves, newKCastle);
            possMoves.end()->kingSideCastle=true;
            Position rookF{8,pos.y};
            Position rookT{6,pos.y};
            possMoves.end()->rookFrom=rookF;
            possMoves.end()->rookTo=rookT;
        }
        if (Queensidecastle(board)) {
            Position newKCastle;
            newKCastle.y = pos.y;
            newKCastle.x = 3;
            tryAddNextMoveCandidate(board, possMoves, newKCastle);
            possMoves.end()->kingSideCastle=true;
            Position rookF{1,pos.y};
            Position rookT{4,pos.y};
            possMoves.end()->rookFrom= rookF;
            possMoves.end()->rookTo=rookT;
        }
    }
    return possMoves;
}


bool King::Queensidecastle(const Board & board) {
    for(int i = 2; i <= 4; i++) {
        Position shouldBeEmpty;
        shouldBeEmpty.x=i;
        shouldBeEmpty.y = pos.y;
        if(!board.isEmpty(shouldBeEmpty)) {
            return false;
        }
    }
    char rookChar;
    if(ownerIdentifier==1) {
        rookChar = 'R';
    } else {
        rookChar = 'r';
    }
    //white king
    if (this->isFirstMove) {
        if (board.getPieceCharAt(Position{1, pos.y}) != rookChar) {
            return false;
        }
        if (!((board.getPieceAt(Position{1, pos.y}))->isFirstMove)) { //???
            return false;
        }
        Move newMove;
        newMove.from = Position{5, pos.y};
        newMove.to = Position{4, pos.y};
        if (isCurrentPlayerKingInCheckAfterMove(newMove, board)) {
            return false;
        }
        newMove.to = Position{3, 1};
        if (isCurrentPlayerKingInCheckAfterMove(newMove, board)) {
            return false;
        }
        return true;
    } 
    return false;
}



bool King::Kingsidecastle(const Board & board) {
    for(int i = 6; i <= 7; i++) {
        Position shouldBeEmpty;
        shouldBeEmpty.x=i;
        shouldBeEmpty.y = pos.y;
        if(!board.isEmpty(shouldBeEmpty)) {
            return false;
        }
    }
    char rookChar;
    if(ownerIdentifier==1) {
        rookChar = 'R';
    } else {
        rookChar = 'r';
    }
    //white king
    if (this->isFirstMove) {
        if (board.getPieceCharAt(Position{8, pos.y}) != rookChar) {
            return false;
        }
        if (!((board.getPieceAt(Position{8, pos.y}).get())->isFirstMove)) { //???
            return false;
        }
        Move newMove;
        newMove.from = Position{5, pos.y};
        newMove.to = Position{6, pos.y};
        if (isCurrentPlayerKingInCheckAfterMove(newMove, board)) {
            return false;
        }
        newMove.to = Position{7, pos.y};
        if (isCurrentPlayerKingInCheckAfterMove(newMove, board)) {
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