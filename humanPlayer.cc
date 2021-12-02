#include "humanPlayer.h"
#include "possibleMove.h"
#include "board.h"
#include "chessPieces.h"
#include "pawn.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"

HumanPlayer::HumanPlayer(int identifier, int currentScore) : Player{identifier, currentScore}{}
void HumanPlayer::copyPlayer(const Player &player) {

}

bool HumanPlayer::tryMakeMove(Move m, Board & board) {
    Position from = m.from;
    Position to = m.to;
    std::shared_ptr<ChessPieces> targetPiece = this->getPieceAt(from);
    std::vector<PossibleMove> allPossibleMoves = targetPiece.get()->getPossibleMoves(board);
    for(auto possMove : allPossibleMoves) {
        if(possMove.to == to) {
            if(possMove.kingSideCastle || possMove.queenSideCastle) {
                movePiece(possMove.rookFrom, possMove.rookTo);
            } 
            if(possMove.enPassant) { 
                // remove opponent pawn
                board.removePiece(possMove.enPassantLoc, opponentIdentifier);
            } 
            if(m.isPromotion) {
                if(!tryDoPawnPromotion(m.promotionType,targetPiece)) {
                    return false;
                }
            } 
            movePiece(from, to);
            return true;
        }
    }
}

