#include "board.h"
#include "move.h"
// #include "boardSetup.h"
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
            if(chessPiecePair.second.get()->size()!=0) {
/*                 int tox = chessPiecePair.second.get()->at(0).to.x;
                int toy = chessPiecePair.second.get()->at(0).to.y;
                int fromx = chessPiecePair.first.get()->pos.x;
                int fromy = chessPiecePair.first.get()->pos.y; */
                // std::cout << opponent << " poss " << "from: "<< fromx << "," << fromy << " | "<< tox << "," << toy << std::endl;
                oppNoPossMove=false;
                break;
            }
        }
        auto currAllPossMove = getPlayerPossibleMoves(currentPlayer);
        bool currNoPossMove =true;
        for(auto chessPiecePair: currAllPossMove) {
            if(chessPiecePair.second.get()->size()!=0) {
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
        } else if(oppNoPossMove||currNoPossMove) {
            // stallmate
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
            // std::cout<< currentPiece.get()->icon << "can capture " << identifier << " king" << std::endl;
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

