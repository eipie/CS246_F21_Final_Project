#include "board.h"
#include "move.h"
#include "player.h"
#include "chessPieces.h"
#include <iostream>

Board::Board(std::vector<std::shared_ptr<Player>> players) 
    : players{players}{}

Board::Board(const Board &board, bool needToCheckSelfCheck) {
    std::vector<std::shared_ptr<Player>> copyPlayers;
    for(auto player:board.players) {
        std::shared_ptr<Player> copiedPlayer = player.get()->clone(needToCheckSelfCheck);
        copyPlayers.emplace_back(copiedPlayer);
    }
    players = copyPlayers;
}

// -1 if failed;
// 0 if normal move, no printout;
// 1 if check
// 2 if checkmate
// 3 if stalemate
int Board::makeAMove(Move m, int currentPlayer) {
    
    if (players[currentPlayer].get()->tryMakeMove(m,*this)) {
        // enPassantAvailabilityCorrect(players[currentPlayer].get()->getPieceAt(m.to), m.from, m.to);
        // check if checked opponent
        int opponent;
        if(currentPlayer==white) {
            opponent = black;
        } else {
            opponent = white;
        }
        // ***checkopponent
        auto checkResult = putInCheck(opponent);
        auto oppAllPossMove = getPlayerPossibleMoves(opponent);
        bool oppNoPossMove =true;
        for(auto chessPiecePair: oppAllPossMove) {
            if(chessPiecePair.second.get() != nullptr&&chessPiecePair.second.get()->size()!=0) {
                oppNoPossMove=false;
                break;
            }
        }
        auto currAllPossMove = getPlayerPossibleMoves(currentPlayer);
        bool currNoPossMove =true;
        for(auto chessPiecePair: currAllPossMove) {
            if(chessPiecePair.second.get()->size()!=0|| chessPiecePair.second.get() != nullptr) {
                currNoPossMove=false;
                break;
            }
        }
        
        if(checkResult.size() != 0) {
            // opponent in check
            if(oppNoPossMove) {
                // checkmate
                return 2;
            }
            players[opponent].get()->isInCheck=true;
            return 1;
        } else if((oppNoPossMove||currNoPossMove) && 
        !(players[opponent].get()->isInCheck) && !(players[currentPlayer].get()->isInCheck)) { // also they are not in check
            // stalemate
            return 3;
        }
        for(auto player:players) {
            player.get()->isInCheck=false;
        }
        return 0;
    } else {
        // Move is illegal
        return -1;
    }
}

void Board::makeAMoveWithoutCheck(Position from, Position to, int identifier) {
    players[identifier].get()->movePiece(from, to, *this);
}

void Board::disableAllEnPassant() {
    for(auto player : players) {
        player.get()->disableAllEnPassant();
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
        removePiece(p,0);
    } else {
        players[0].get()->addPiece( p,  c);
        removePiece(p,1);
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
            } else {
                return ' ';
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
std::vector<std::shared_ptr<ChessPieces>> Board::putInCheck(int identifier) const{
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
            // std::cout<< currentPiece.get()->icon << "can capture " << identifier << " king" << std::endl;
            opponentPieceThatCheck.emplace_back(currentPiece);
        }
    }
    return opponentPieceThatCheck;

}


std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> Board::getPlayerPossibleMoves (int idenfitier) const {
    std::map<Position, std::shared_ptr<ChessPieces>> playerPieces = players[idenfitier].get()->playerPieces;
    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> playerAllPossMoves;
    for(auto pieceSet: playerPieces) {
        std::shared_ptr<ChessPieces> currentPiece = pieceSet.second;
        // std::vector<PossibleMove> piecePossMoves = currentPiece.get()->getPossibleMoves(*this);
        auto piecePossMoves = std::make_shared<std::vector<PossibleMove>>(currentPiece.get()->getPossibleMoves(*this));
        currentPiece.get()->pos.x = pieceSet.first.x;
        currentPiece.get()->pos.y = pieceSet.first.y;
        // std::cout << "storing... " << currentPiece.get()->pos.x << "|" << currentPiece.get()->pos.y << std::endl;
        playerAllPossMoves[currentPiece]  = piecePossMoves;
    }
    return playerAllPossMoves;
}

bool Board::noPawnFirstLastRow() const {
    Position p{1, 1};
    for (int i = 1; i <= 8; ++i) {
        std::vector<int> row = {1, 8};
        for(int j:row) {
            p.x = i;
            p.y = j;
            if (getPieceCharAt(p) == 'p' || getPieceCharAt(p) == 'P') {
               return true;
            }
        }
    }
    return false;
}

// One black kings, one white king
// No pawns in first or last row
// Neither king is in check
bool Board::isBoardSetupValid() const {
    for(auto player: players) {
       if (player.get()->countKing() != 1) {
           std::cout << "king" << std::endl;
           return false;
       }
    }
    if (noPawnFirstLastRow()) {
        std::cout << "pawn" << std::endl;
       return false;
    }
    if (putInCheck(0).size()!=0) { //check for black
    std::cout << "b check" << std::endl;
        return false;
    }
    if (putInCheck(1).size()!=0) { //check for white
    std::cout << "w check" << std::endl;
        return false;
    }
    return true;
}

bool Board::ifInCheck(int identifier) const{
    return players[identifier].get()->isInCheck;
}

