#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include <map>
class Player;
// class BoardSetup; 
class Move;
class Position;

class Board{

    std::vector<std::shared_ptr<Player> > players;
    public:
    Board(std::vector<std::shared_ptr<Player> > players);
    void makeAMove(Position from, Position to, int currentPlayer);
    void resetBoard();
    void removePiece(Position p);
    void addPiece(Position p, char c);
    // to be implemented, dummy variable
    bool isBoardSetupValid();
    char getPieceCharAt(Position p);
};

#endif