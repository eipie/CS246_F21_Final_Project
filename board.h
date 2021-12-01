#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include <map>
class Player;
// class BoardSetup; 
class Move;
class Position;
class ChessPieces;

class Board{

    std::vector<std::shared_ptr<Player>> players;
    const int white =1;
    const int black = 0;
    public:
    Board(std::vector<std::shared_ptr<Player> > players);
    void makeAMove(Position from, Position to, int currentPlayer);
    void resetBoard();
    void removePiece(Position p);
    void addPiece(Position p, char c);
    // to be implemented, dummy variable
    bool isBoardSetupValid() const;
    char getPieceCharAt(Position p) const;
    std::shared_ptr<ChessPieces> getPieceAt(Position p) const;
    char isOpponentPiece(Position target, int identifier) const;
    bool isEmpty(Position target) const;
    bool tryMakeMove(Move m, int identifier);
};

#endif