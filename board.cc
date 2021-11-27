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