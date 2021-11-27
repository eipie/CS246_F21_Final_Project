#include "chessGame.h"
#include "player.h"
#include "move.h"
#include "board.h"
// #include  "boardSetup.h"

ChessGame::ChessGame() {
    std::shared_ptr<Player> playerOne = std::make_shared<Player>(1);
    std::shared_ptr<Player> playerTwo = std::make_shared<Player>(0);
    players.emplace_back(playerTwo);
    players.emplace_back(playerOne);
    board = std::make_shared<Board>(players);
    // populate board
    board.get()->resetBoard();
}

void ChessGame::newRound() {
    board.get()->resetBoard();
}

// check if the current user move is valid
bool ChessGame::isMoveValid(Move nextMove) {
    // dummy variable
    return true;
}

void ChessGame::makeAMove(Move nextMove) {
    if (isMoveValid(nextMove)) {
        board.get()->makeAMove(nextMove.from, nextMove.to);
        board.get()->changePlayer();
    }
}


/* // Basic check: check if piece hit enemy piece(stop&capture), pop all consequtive moves
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
} */