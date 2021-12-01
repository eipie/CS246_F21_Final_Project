#include "board.h"
#include "move.h"
// #include "boardSetup.h"
#include "player.h"
#include <iostream>

Board::Board(std::vector<std::shared_ptr<Player>> players) 
    : players{players}{}



void Board::makeAMove(Position from, Position to, int currentPlayer) {
    if (players[currentPlayer].get()->getPieceCharAt(from) != ' ') {
        removePiece(to);
        // std::cout << "current player is: "<< currentPlayer << std::endl;
        players[currentPlayer].get()->movePiece(from, to);
    } else {
        // error, player moving the piece does not own the piece
    }
    
}

void Board::removePiece(Position p) {
    for(auto player: players) {
       player.get()->removePieces(p);
    }
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

// dummy return value
bool Board::isBoardSetupValid() const{
    return true;
}

