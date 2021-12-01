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

bool HumanPlayer::validPromotion(char promotion, std::shared_ptr<ChessPieces> target) {
    if((identifier==0 && (promotion == 'p'|| promotion == 'r'|| promotion == 'n'|| promotion == 'b'|| promotion == 'q'))
        || (identifier==1 && (promotion == 'P'|| promotion == 'R'|| promotion == 'N'|| promotion == 'B'|| promotion == 'Q'))) {
        if(promotion== 'p'||promotion=='P') {

        } else if(promotion== 'r'||promotion=='R') {
            std::shared_ptr<ChessPieces> newPiece = std::make_shared<Rook>(target.get()->pos, identifier, false);
            target.swap(newPiece);
        } else if(promotion== 'n'||promotion=='N') {
            std::shared_ptr<ChessPieces> newPiece = std::make_shared<Knight>(target.get()->pos, identifier, false);
            target.swap(newPiece);
        } else if(promotion== 'b'||promotion=='B') {
            std::shared_ptr<ChessPieces> newPiece = std::make_shared<Bishop>(target.get()->pos, identifier, false);
            target.swap(newPiece);
        } else if(promotion== 'q'||promotion=='Q') {
            std::shared_ptr<ChessPieces> newPiece = std::make_shared<Queen>(target.get()->pos, identifier, false);
            target.swap(newPiece);
        }
        return true;
    } 
    return false;
}

bool HumanPlayer::tryMakeMove(Move m, const Board & board) {
    Position from = m.from;
    Position to = m.to;
    std::shared_ptr<ChessPieces> targetPiece = this->getPieceAt(from);
    std::vector<PossibleMove> allPossibleMoves = targetPiece.get()->getPossibleMoves(board);
    for(auto possMove : allPossibleMoves) {
        if(possMove.to == to) {
            if(m.isPromotion) {
                if(!validPromotion(m.promotionType,targetPiece)) {
                    return false;
                }
            } else if(m.kingSideCastle) {
                // move rook
            } else if(m.queenSideCastle) {
                // move rook
            } else if(m.enPassant) {
                // remove opponent pawn
            }
            movePiece(from, to);
        }
    }
}

