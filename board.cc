#include "board.h"
#include "move.h"
// #include "boardSetup.h"
#include "player.h"

Board::Board(std::vector<std::shared_ptr<Player>> players) 
    : players{players}, currentPlayer{1} {}

void Board::changePlayer() {
    if(currentPlayer==0) {
        currentPlayer=1;
    } else {
        currentPlayer=0;
    }
}

void Board::makeAMove(Position from, Position to) {
    removePiece(to);
    players.at(currentPlayer).get()->movePiece(from, to);
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

// return ' ' if not find 
char Board::getPieceCharAt(Position p) {
    char c;
    for(auto player: players) {
       c = player.get()->getPieceCharAt(p);
       if (c!=' ') {
           break;
       }
    }
    return c;
}

// dummy return value
bool Board::isBoardSetupValid() {
    return true;
}