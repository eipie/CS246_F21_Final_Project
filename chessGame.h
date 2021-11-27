#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>
#include <vector>
class Board;
class Player;
class Move;
class BoardSetup;
// class Position;
// class Observer;
class ChessGame {
    std::shared_ptr<std::vector<Player>> players;
    std::shared_ptr<Board> board;
    // std::vector<Observer> observers;
    public:
    ChessGame(BoardSetup setup);
    // attempt to makeAMove; return true success, return false, failure
    bool makeAMove(Move nextMove);

    // void changePieceAt(Position ini_p, Position target_p);

    // char getState(Position p);
    // void render();
    // void attachObserver(shared_ptr<Observer> o);
    // void detachObserver(shared_ptr<Observer> o);
    // void notifyObservers();

};

#endif