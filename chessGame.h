#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>
#include <vector>
class Board;
class Player;
class Move;
class Observer;

class Position;
// class BoardSetup;
// class Position;

class ChessGame {
    // player id
    const int white = 1;
    const int black = 0;
    // 0:black; 1:white
    int currentPlayer;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Board> board;
    std::vector<Observer *> observers;
    std::shared_ptr<Observer> textObserver;
    // std::vector<Observer> observers;
    public:
    ChessGame();
    void nextTurn();
    void setCurrentPlayer(int playerId);
    // [to be implemented], dummy variable
    bool isMoveValid(Move nextMove);
    // attempt to makeAMove; return true success, return false, failure
    void makeAMove(Move nextMove);
    void newRound();
    void removePiece(Position p);
    void addPiece(Position p, char c);
    bool isBoardSetupValid();
    char getPieceCharAt(Position p);
    // void changePieceAt(Position ini_p, Position target_p);

    void attachObserver(Observer *o);
    void detachObserver(Observer *o);
    void notifyObservers();
    void render();


private:
/*     // return all Positions the piece at current location can go
    std::vector<PossibleMove> getAllPossibleMoves(Move nextMove);
    // return all legal Positions the piece at current location can go, 
    // including the piece it will be able to capture as value in map
    std::map<Position, char> getAllLegalMove(std::vector<Position> possMove, Move nextMove); */
};

#endif