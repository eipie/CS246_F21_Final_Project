#include "board.h"
#include "move.h"
// #include "boardSetup.h"
#include "player.h"
#include "chessPieces.h"
#include <iostream>

Board::Board(std::vector<std::shared_ptr<Player>> players) 
    : players{players}{}

Board::Board(const Board &board) {
    std::vector<std::shared_ptr<Player>> copyPlayers;
    for(auto player:board.players) {
        std::shared_ptr<Player> copiedPlayer = std::make_shared<Player>(*player.get());
        copyPlayers.emplace_back(copiedPlayer);
    }
    players = copyPlayers;
}

bool Board::makeAMove(Move m, int currentPlayer) {
    if (players[currentPlayer].get()->tryMakeMove(m,*this)) {
        if(currentPlayer==1) {
            removePiece(m.to, 0);
        } else {
            removePiece(m.to, 1);
        }
        enPassantAvailabilityCorrect(players[currentPlayer].get()->getPieceAt(m.to), m.from, m.to);
        // check if checked opponent
        int opponent;
        if(currentPlayer==white) {
            opponent = black;
        } else {
            opponent = white;
        }
        auto allPossMove = getPlayerPossibleMoves(opponent);
            bool noPossMove =true;
            for(auto chessPiecePair: allPossMove) {
                if(chessPiecePair.second.get()->size()!=0) {
                    noPossMove=false;
                    break;
                }
        }
        // ***checkopponent
        auto checkResult = putInCheck(opponent);
        if(checkResult.size() != 0) {
            /* // ***see if surrounding square will also be in check
            auto checkMateResult = players[opponent].get()->kingEscapeTrap(*this);
            if(checkMateResult.size()==0) {
                // opponent checkmate; opponent loses
            } */
            // opponent in check
            if(noPossMove) {
                // checkmate
            }
            players[opponent].get()->isInCheck=true;
        } else if(noPossMove) {
            // stallmate
        }
        return true;
    } else {
        // Move is illegal
        return false;
    }
}

void Board::enPassantAvailabilityCorrect(std::shared_ptr<ChessPieces> pieceToBeMoved, Position from, Position to) {
    for(auto player : players) {
            player.get()->disableAllEnPassant();
    }
    if((pieceToBeMoved.get()->icon=='p' || pieceToBeMoved.get()->icon=='P') && (abs(from.y-to.y)==2)) {
        if(abs(from.y-to.y)==2) {
            pieceToBeMoved.get()->availableForEnPassant=true;
        } 
    }
}

void Board::removePiece(Position p, int currentPlayer) {
    players[currentPlayer].get()->removePieces(p);
}

void Board::resetBoard() {
    for(auto player: players) {
       player.get()->resetAllPieces();
    }
}

void Board::addPiece(Position p, char c) {
    if(isupper(c)) {
        players[1].get()->addPiece( p,  c);
    } else {
        players[0].get()->addPiece( p,  c);
    }
}

bool Board::isEmpty(Position target) const{
    return getPieceCharAt(target)==' ';
}

char Board::isOpponentPiece(Position target, int identifier) const{
    auto result = getPieceCharAt(target);
    if(!isEmpty(target)) {
        if(identifier==white) {
            if(islower(result)){
                return result;
            } else {
                return ' ';
            }
        } else {
            if(isupper(result)) {
                return result;
            }
        }
    }
    return ' ';
}


// return ' ' if not find 
char Board::getPieceCharAt(Position p) const{
    char c = ' ';
    for(auto player: players) {
       c = player.get()->getPieceCharAt(p);
       if (c!=' ') {
           break;
       }
    }
    return c;
}

// return nullptr if not found
std::shared_ptr<ChessPieces> Board::getPieceAt(Position p) const {
    std::shared_ptr<ChessPieces> c = nullptr;
    for(auto player: players) {
       c = player.get()->getPieceAt(p);
       if (c!=nullptr) {
           break;
       }
    }
    return c;
}

// return a list of pieces in opponent that can put identifier's pieces in check
std::vector<std::shared_ptr<ChessPieces>> Board::putInCheck(int identifier) {
    std::vector<std::shared_ptr<ChessPieces>> opponentPieceThatCheck;
    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> playerPossibleMoves;
    std::map<Position, std::shared_ptr<ChessPieces>> playerPieces;
    if(identifier==black) {
        playerPossibleMoves = getPlayerPossibleMoves(white);
        playerPieces = players[white].get()->playerPieces;
    } else {
        playerPossibleMoves = getPlayerPossibleMoves(black);
        playerPieces = players[black].get()->playerPieces;
    }

    for(auto pieceSet: playerPieces) {
        auto currentPiece = pieceSet.second;
        if(currentPiece.get()->checkOpponent) {
            opponentPieceThatCheck.emplace_back(currentPiece);
        }
    }
    return opponentPieceThatCheck;

}


std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> Board::getPlayerPossibleMoves(int idenfitier) {
    std::map<Position, std::shared_ptr<ChessPieces>> playerPieces = players[idenfitier].get()->playerPieces;
    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> playerAllPossMoves;
    for(auto pieceSet: playerPieces) {
        std::shared_ptr<ChessPieces> currentPiece = pieceSet.second;
        // std::vector<PossibleMove> piecePossMoves = currentPiece.get()->getPossibleMoves(*this);
        auto piecePossMoves = std::make_shared<std::vector<PossibleMove>>(currentPiece.get()->getPossibleMoves(*this));
        playerAllPossMoves[currentPiece]  = piecePossMoves;
    }
    return playerAllPossMoves;
}

// dummy return value
bool Board::isBoardSetupValid() const{
    return true;
}

bool Board::ifInCheck(int identifier) const{
    return players[identifier].get()->isInCheck;
}

