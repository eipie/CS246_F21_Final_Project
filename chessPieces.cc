#include "chessPieces.h"
#include "position.h"
#include "move.h"
ChessPieces::ChessPieces(Position p, int identifier, bool isFirstMove) 
    : ownerIdentifier{identifier}, isFirstMove{isFirstMove}, pos{p}{}

void ChessPieces::afterFirstMove() {
    if(isFirstMove) {
        isFirstMove = false;
    }
}

bool ChessPieces::withinBound(Position candidate) {
    return candidate.x <= 8 && candidate.y <= 8 && candidate.x >=1 && candidate.y >=1;
}

int ChessPieces::tryAddNextMoveCandidate(const Board & board, std::vector<PossibleMove> & possibleMove, Position candidate) {
    char returnKey = -1;
    if(withinBound(candidate)) {
        const char noCapture = ' ';
        const char currentPlayerPiece = ' ';
        if(board.isEmpty(candidate)) {
            PossibleMove newPossMove;
            newPossMove.capture = noCapture;
            newPossMove.to = candidate;
            possibleMove.emplace_back(newPossMove);
            returnKey = 0;
        } else {
            char pieceResult = board.isOpponentPiece(candidate, ownerIdentifier);
            if(pieceResult == currentPlayerPiece) {
                return returnKey;
            } else {
                if(pieceResult=='K'||pieceResult=='k') {
                    checkOpponent = true;
                }
                PossibleMove newPossMove;
                newPossMove.capture = pieceResult;
                newPossMove.to = candidate;
                possibleMove.emplace_back(newPossMove);
                returnKey = 1;
            }
        }
    }
    // check if Pawn is eligable for Promotion
    if((returnKey==1 || returnKey == 0) && (icon == 'p'||icon=='P')) {
        if(candidate.y == 8 || candidate.y == 1) {
            possibleMove.end()->isPromotion=true;
            // assign default promotionType [mainly for computerPlayer]
            if(ownerIdentifier==1) {
                possibleMove.end()->promotionType='Q';
            } else{
                possibleMove.end()->promotionType='q';
            }
        }
    }
    return returnKey;
}

bool ChessPieces::isCurrentPlayerKingInCheckAfterMove(Move newMove, const Board & board) {
    if(!(withinBound(newMove.from) && withinBound(newMove.to))) {
        // error
        throw;
    }
    // **Make a copy of the board
    Board newBoard = board;
    newBoard.makeAMove(newMove, ownerIdentifier);
    return (newBoard.putInCheck(ownerIdentifier).size()==0);
}