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
    // 0:black; 1:white
    int currentPlayer;
    std::vector<std::shared_ptr<Player> > players;
    void resetBoardByPlayer(std::map<Position, std::shared_ptr<ChessPieces> > *playerPieces, int identifier);

    public:
    Board(std::vector<std::shared_ptr<Player> > players);
    void changePlayer();
    void makeAMove(Position from, Position to);
    void resetBoard();
    void removePiece(Position p);
    void addPiece(Position p, char c);
    // to be implemented, dummy variable
    bool isBoardSetupValid();
    char getPieceCharAt(Position p);
};

#endif