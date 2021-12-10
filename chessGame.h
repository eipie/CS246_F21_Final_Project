#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>
#include <vector>
class Board;
class Player;
struct Move;
class Observer;

struct Position;

class ChessGame {
    const int white = 1;
    const int black = 0;
    // 0:black; 1:white
    int currentPlayer;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Board> board;
    std::vector<Observer *> observers;
    std::shared_ptr<Observer> textObserver;
    public:
    bool roundEnds=true;
    // level of 1-3 is for computer; level 0 means human
    ChessGame(bool isHuman1, bool isHuman2, std::vector<int> levels);
    void nextTurn();
    void setCurrentPlayer(int playerId);
    bool isMoveValid(Move nextMove);
    // attempt to makeAMove; return true success, return false, failure
    std::string makeAMove(Move nextMove);
    void makeBlankBoard();
    void newRound();
    bool removePiece(Position p);
    bool addPiece(Position p, char c);
    bool isBoardSetupValid();
    char getPieceCharAt(Position p);
    void notifyObservers();
    void render();
    std::string resign();
    double whitePlayerScore();
    double blackPlayerScore();
    void giveHintAt(Position focus);
};

#endif