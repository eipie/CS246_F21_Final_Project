#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include <map>
class Player;
class BoardSetup;
class Move;
class Position;
class Board{
    // 0:black; 1:white
    int currentPlayer;
    std::shared_ptr<std::vector<std::shared_ptr<Player>>> players;
    // return all Positions the piece at current location can go
    std::shared_ptr<std::vector<Position>> getAllPossibleMoves(Move nextMove);
    // return all legal Positions the piece at current location can go, 
    // including the piece it will be able to capture as value in map
    std::map<Position, char> getAllLegalMove(std::vector<Position> possMove, Move nextMove);
    public:
    Board(std::shared_ptr<std::vector<std::shared_ptr<Player>>> players, BoardSetup boardSetup);
    void changePlayer();
    void makeAMove(Move nextMove);
};

#endif