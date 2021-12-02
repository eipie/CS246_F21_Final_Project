#include "chessGame.h"
#include "player.h"
#include "move.h"
#include "board.h"
#include "position.h"
#include "observer.h"
#include "text_display.h"
#include <iostream>
// #include  "boardSetup.h"

ChessGame::ChessGame() : currentPlayer{white} {
    std::shared_ptr<Player> playerOne = std::make_shared<Player>(1);
    std::shared_ptr<Player> playerTwo = std::make_shared<Player>(0);
    players.emplace_back(playerTwo);
    players.emplace_back(playerOne);
    board = std::make_shared<Board>(players);
    // populate board
    // board.get()->resetBoard();
    textObserver = std::make_shared<Text_Display>(this);
    observers.emplace_back(textObserver.get());
    render();
}

void ChessGame::setCurrentPlayer(int playerId) {
    currentPlayer = playerId;
}

void ChessGame::nextTurn() {
    if(currentPlayer==black) {
        currentPlayer=white;
    } else {
        currentPlayer=black;
    }
}


void ChessGame::newRound() {
    board.get()->resetBoard();
    setCurrentPlayer(white);
}

std::string ChessGame::resign() {
    if(currentPlayer==white) {
        players[black].get()->currentScore++;
        return "Black Wins!";
    } else {
        players[white].get()->currentScore++;
        return "White Wins!";
    }
}

/* std::string ChessGame::printFinalScore(std::cout out) {
    return "Final Score:\nWhite: "+players[white].get()->currentScore+'\n'+"Black: "+players[black].get()->currentScore;
}
 */


// isCurrentPlayerKingInCheckAfterMove(vector<Move> moves)
// check if king is in check after a move
// 1. Copy the current board (2 players' piece)
// 2. initate the move (loop through the vector, and do the movePiece method)
// 3. loop through enemy pieces and check if piece.possibleMove()==king position

// piece.possibleMove()

// check if the current user move is valid
bool ChessGame::isMoveValid(Move nextMove) {
    


        // check if move is promotion
        // 
        // 1. ifPromotion(Move nextMove);
        //      if(isPromotion==true);
        // 2. ifPromotionValue(Move nextMove);
        //      Position from is currentplayer's Pawn
        //      AND
        //      if nextMove.promotionType isValidType(char promotionType); (Q/R/B/N || q/r/b/n)
        //      AND
        //      if the Pawn at Position to, to.y==8||1; (depending on player color)
        //      AND
        //      isCurrentPlayerKingInCheckAfterMove(newMove) == false
        // 3. Do the promotion
        //      change pawn at Position from to type desired
        //      return true;

        // En passant/Pawn capture
        // 1. ifEnPassant
        //  if Position from is Pawn of current color
        //  AND
        // Position to is either (x+1, y+1) || (x-1, y+1)
        // 2. isEnPasantValid(Move nextMove);
        // if Position to a piece of opponent type
        //
        

        //  Position(to.x+1, from.x) == Position() || Position(to.x-1, from.x)
        // 3. doEnPasant(Move nextMove)
    // dummy variable
    return true;
}

void ChessGame::makeAMove(Move nextMove) {
    // std::cout << nextMove.from.x << nextMove.from.y << "   " << nextMove.to.x <<nextMove.to.y  << std::endl;
    if (board.get()->makeAMove(nextMove, currentPlayer)) {
        // pass to next player; 
        // ***issue still increment by one if moving opponent piece
        nextTurn();
        render();
    } else {
        render();
    }
}

void ChessGame::attachObserver(Observer *o) {
    observers.emplace_back(o);
}

void ChessGame::detachObserver(Observer *o) {
    for (auto it = observers.begin(); it != observers.end();) {
        if (*it == o) {
            it = observers.erase(it);
        } else {
            ++it;
        }
   }
}

void ChessGame::notifyObservers() {
    for (auto ob: observers) {
        ob->update();
    }
}

void ChessGame::removePiece(Position p) {
    board.get()->removePiece(p, white);
    board.get()->removePiece(p, black);
}
void ChessGame::addPiece(Position p, char c) {
    board.get()->addPiece(p, c);
}
bool ChessGame::isBoardSetupValid() {
    return board.get()->isBoardSetupValid();
}
char ChessGame::getPieceCharAt(Position p) {
    return board.get()->getPieceCharAt(p);
}

// opponent (black:0; white:1);
// int playerResign()

// 
// vector<int> gameEnd()

void ChessGame::render() {
    notifyObservers();
}

/* // Basic check: check if piece hit enemy piece(stop&capture), pop all consequtive moves
//              check if piece hit own piece, pop all current the following moves.
// Check if move [player]'s piece from [from] to [to] will cause enemy piece be able to capture [player]'s king
std::vector<PossibleMove> Board::getAllPossibleMoves(Move nextMove) {
    std::vector<PossibleMove> possMoves;
    Position from = nextMove.from;
    auto playerPieces = players.get()->at(currentPlayer).get()->playerPieces;
    auto pair = playerPieces.find(from);
    if(pair!=playerPieces.end()) {
        std::shared_ptr<ChessPieces> piece = pair->second;
        auto possMoves = piece.get()->getPossibleMoves(const Board & board);
    } else {
        // error, no piece at given location
    }
} */