#include "chessPieces.h"
#include "position.h"
#include "move.h"
#include <iostream>
ChessPieces::ChessPieces(Position p, int identifier, bool isFirstMove) 
    : ownerIdentifier{identifier}, isFirstMove{isFirstMove}, pos{p}{}

ChessPieces::ChessPieces(const ChessPieces &chessPieces) {
    pos = chessPieces.pos;
    icon = chessPieces.icon;
    isFirstMove = chessPieces.isFirstMove;
    checkOpponent  = chessPieces.checkOpponent;
    availableForEnPassant = chessPieces.availableForEnPassant;
    ownerIdentifier = chessPieces.ownerIdentifier;
}

void ChessPieces::afterFirstMove() {
    if(isFirstMove) {
        isFirstMove = false;
    }
}

bool ChessPieces::withinBound(Position candidate) {
    return candidate.x <= 8 && candidate.y <= 8 && candidate.x >=1 && candidate.y >=1;
}

// -1 if could not add candidate as possmove because current player's piece is at location
// -2 if
int ChessPieces::tryAddNextMoveCandidate(const Board & board, std::vector<PossibleMove> & possibleMove, Position candidate) {
    char returnKey = -1;
    if(withinBound(candidate)) {
        const char noCapture = ' ';
        const char currentPlayerPiece = ' ';
        if(board.isEmpty(candidate)) {
            // Move possPossMove{pos, candidate};
            PossibleMove newPossMove;
            newPossMove.capture = noCapture;
            newPossMove.to = candidate;
            if(!isCurrentPlayerKingInCheckAfterMove(newPossMove,board)) {   
                if((icon == 'p'||icon=='P') && (candidate.y == 8 || candidate.y == 1)) {
                    newPossMove.isPromotion=true;
                    if(ownerIdentifier==1) {
                        newPossMove.promotionType='Q';
                    } else{
                        newPossMove.promotionType='q';
                    }
                } 
                possibleMove.emplace_back(newPossMove);
                returnKey = 0;
            } else {
                returnKey = -2;
            }
            
        } else {
            char pieceResult = board.isOpponentPiece(candidate, ownerIdentifier);
            if(pieceResult == currentPlayerPiece) {
                return returnKey;
            } else {
                // Move possPossMove{pos, candidate};
                PossibleMove newPossMove;
                newPossMove.capture = pieceResult;
                newPossMove.to = candidate;
                if(!isCurrentPlayerKingInCheckAfterMove(newPossMove,board)) {
                    if((icon == 'p'||icon=='P') && (candidate.y == 8 || candidate.y == 1)) {
                        newPossMove.isPromotion=true;
                        if(ownerIdentifier==1) {
                            newPossMove.promotionType='Q';
                        } else{
                            newPossMove.promotionType='q';
                        }
                    }
                    if(pieceResult=='K'||pieceResult=='k') {
                        checkOpponent = true;
                    }    
                    possibleMove.emplace_back(newPossMove);
                    returnKey = 1;
                } else {
                    returnKey = -2;
                }
            }
        }
    }
/* 
    // if((icon == 'p'||icon=='P') && (candidate.y == 8 || candidate.y == 1))
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
    } */
    return returnKey;
}

bool ChessPieces::isCurrentPlayerKingInCheckAfterMove(Move newMove, const Board & board) {
    if(!(withinBound(newMove.from) && withinBound(newMove.to))) {
        // error
        throw;
    }
    // **Make a copy of the board
    Board newBoard(board);
    newBoard.makeAMoveWithoutCheck(newMove.from, newMove.to, ownerIdentifier);
    // newBoard.makeAMove(newMove, ownerIdentifier);
    return (newBoard.putInCheck(ownerIdentifier).size()!=0);
}

bool ChessPieces::isCurrentPlayerKingInCheckAfterMove(PossibleMove possMove, const Board & board) {
    int opponentIdentifier;
    if(ownerIdentifier==1) {
        opponentIdentifier=0;
    } else {
        opponentIdentifier=1;
    }
    if(!(withinBound(possMove.to))) {
        // error
        throw;
    }
    // **Make a copy of the board
    Board newBoard(board);
    if(possMove.kingSideCastle || possMove.queenSideCastle) {
        // std::cout << "we are here!" << std::endl;
        newBoard.makeAMoveWithoutCheck(possMove.rookFrom, possMove.rookTo, ownerIdentifier);
    } 
    if(possMove.enPassant) { 
        // remove opponent pawn
        newBoard.removePiece(possMove.enPassantLoc, opponentIdentifier);
    } 
    // Move m(pos, possMove.to);
    newBoard.makeAMoveWithoutCheck(pos, possMove.to, ownerIdentifier);
    // .(m, ownerIdentifier);
    return (newBoard.putInCheck(ownerIdentifier).size()!=0);
}