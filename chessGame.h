#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>
#include <vector>
class Board;
class Player;
class Move;
class Observer;

// class BoardSetup;
// class Position;
class ChessGame {
    std::vector<std::shared_ptr<Player> > players;
    std::shared_ptr<Board> board;
    std::vector<Observer *> observers;
    // std::vector<Observer> observers;
    public:
    ChessGame();
    bool isMoveValid(Move nextMove);
    // attempt to makeAMove; return true success, return false, failure
    void makeAMove(Move nextMove);
    void newRound();
    // void changePieceAt(Position ini_p, Position target_p);

    void attachObserver(Observer *o);
    void detachObserver(Observer *o);
    void notifyObservers();
    void render();
    char getState(Position p);



private:
/*     // return all Positions the piece at current location can go
    std::shared_ptr<std::vector<Position>> getAllPossibleMoves(Move nextMove);
    // return all legal Positions the piece at current location can go, 
    // including the piece it will be able to capture as value in map
    std::map<Position, char> getAllLegalMove(std::vector<Position> possMove, Move nextMove); */
};

#endif