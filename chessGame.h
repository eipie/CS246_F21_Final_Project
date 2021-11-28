#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>
#include <vector>
class Board;
class Player;
class Move;
// class BoardSetup;
// class Position;
// class Observer;
class ChessGame {
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Board> board;
    // std::vector<Observer> observers;
    public:
    ChessGame();
    bool isMoveValid(Move nextMove);
    // attempt to makeAMove; return true success, return false, failure
    void makeAMove(Move nextMove);
    void newRound();
    // void changePieceAt(Position ini_p, Position target_p);

    // char getState(Position p);
    // void render();
    // void attachObserver(shared_ptr<Observer> o);
    // void detachObserver(shared_ptr<Observer> o);
    // void notifyObservers();


private:
/*     // return all Positions the piece at current location can go
    std::shared_ptr<std::vector<Position>> getAllPossibleMoves(Move nextMove);
    // return all legal Positions the piece at current location can go, 
    // including the piece it will be able to capture as value in map
    std::map<Position, char> getAllLegalMove(std::vector<Position> possMove, Move nextMove); */
};

#endif