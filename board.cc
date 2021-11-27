#include "board.h"
#include "move.h"
#include "boardSetup.h"
#include "player.h"
#include "chessPieces.h"
Board::Board(std::shared_ptr<std::vector<std::shared_ptr<Player>>> players, BoardSetup boardSetup) 
    : players{players}, currentPlayer{boardSetup.init_player} {}

void Board::changePlayer() {
    if(currentPlayer==0) {
        currentPlayer=1;
    } else {
        currentPlayer=0;
    }
}

// Basic check: check if piece hit enemy piece(stop&capture), pop all consequtive moves
//              check if piece hit own piece, pop all current the following moves.
// Check if move [player]'s piece from [from] to [to] will cause enemy piece be able to capture [player]'s king

std::shared_ptr<std::vector<Position>> Board::getAllPossibleMoves(Move nextMove) {
    std::shared_ptr<std::vector<Position>> possMoves;
    Position from = nextMove.from;
    auto playerPieces = players.get()->at(currentPlayer).get()->playerPieces;
    auto pair = playerPieces.find(from);
    if(pair!=playerPieces.end()) {
        std::shared_ptr<ChessPieces> piece = pair->second;
        auto possMoves = piece.get()->getPossibleMoves();
    } else {
        // error, no piece at given location
    }
}

void Board::makeAMove(Move nextMove) {

}
