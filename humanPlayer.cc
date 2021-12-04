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
HumanPlayer::HumanPlayer(const HumanPlayer &humanPlayer,  bool needToCheckSelfCheck) : Player(humanPlayer, needToCheckSelfCheck){}
std::shared_ptr<Player> HumanPlayer::clone( bool needToCheckSelfCheck){
    // std::cout << "copying Human" << std::endl;
    return std::shared_ptr<Player>(new HumanPlayer(*this, needToCheckSelfCheck));
}

bool HumanPlayer::tryMakeMove(Move m, Board & board) {
    Position from = m.from;
    Position to = m.to;
    std::shared_ptr<ChessPieces> targetPiece = this->getPieceAt(from);
    
    std::vector<PossibleMove> allPossibleMoves = targetPiece.get()->getPossibleMoves(board);
    // std::cout << "king status " <<allPossibleMoves.end()->kingSideCastle << std::endl;
    
    for(auto possMove : allPossibleMoves) {
        // std::cout << possMove.kingSideCastle << std::endl;
        if(possMove.to == to) {
            // std::cout << "piece move " << std::endl;
            if(possMove.kingSideCastle || possMove.queenSideCastle) {
                // std::cout << "queen castle" << std::endl;
                movePiece(possMove.rookFrom, possMove.rookTo, board);
            } 
            if(possMove.enPassant) { 
                // remove opponent pawn
                board.removePiece(possMove.enPassantLoc, opponentIdentifier);
            } 
             if(m.isPromotion) {
                bool checkPromotionResult = tryDoPawnPromotion(m.promotionType,targetPiece.get()->pos, targetPiece.get()->ownerIdentifier, board);
                // std::cout << "After promotion" <<targetPiece.get()->icon << std::endl;
                if(!checkPromotionResult) {
                    return false;
                }
            } 
/*             if(m.isPromotion) {
                ChessPieces * newPtr = tryDoPawnPromotion(m.promotionType,targetPiece.get());
                
                std::cout << "After promotion" <<targetPiece.get()->icon << std::endl;
                if(newPtr!=nullptr) {
                    return false;
                }
                this->getPieceAt(from).reset(newPtr);
            }  */
            enPassantAvailabilityCorrect(board.getPieceAt(from), board, from, to);
            movePiece(from, to, board);
            return true;
        }
    }
    return false;
}
