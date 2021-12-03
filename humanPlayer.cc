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
#include <iostream>

HumanPlayer::HumanPlayer(int identifier, int currentScore) : Player{identifier, currentScore}{}
HumanPlayer::HumanPlayer(const HumanPlayer &humanPlayer) : Player(humanPlayer){}
std::shared_ptr<Player> HumanPlayer::clone(){
    std::cout << "copying Human" << std::endl;
    return std::shared_ptr<Player>(new HumanPlayer(*this));
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
            enPassantAvailabilityCorrect(board.getPieceAt(to), board, from, to);
            movePiece(from, to);
            return true;
        }
    }
}

