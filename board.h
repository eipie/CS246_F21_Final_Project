#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>
#include <map>
class Player;
// class BoardSetup; 
struct Move;
struct Position;
class ChessPieces;
struct PossibleMove;
class Board{

    
    const int white =1;
    const int black = 0;
    
    public:
    std::vector<std::shared_ptr<Player>> players;
    // constructor
    Board(std::vector<std::shared_ptr<Player> > players);
    // copy constructor
    Board(const Board &board);
    int makeAMove(Move m, int currentPlayer);
    void resetBoard();
    void removePiece(Position p, int currentPlayer);
    void addPiece(Position p, char c);
    // to be implemented, dummy variable
    bool isBoardSetupValid() const;
    char getPieceCharAt(Position p) const;
    std::shared_ptr<ChessPieces> getPieceAt(Position p) const;
    char isOpponentPiece(Position target, int identifier) const;
    bool isEmpty(Position target) const;
    // return all pieces that currently puts identifier's king in check
    std::vector<std::shared_ptr<ChessPieces>> putInCheck(int identifier);
    // all possible moves of all the pieces player identifier has
    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> getPlayerPossibleMoves(int identifier);
    // check if a player is in check (incheck variable in Player class)
    bool ifInCheck(int identifier) const;
    void disableAllEnPassant();
    void makeAMoveWithoutCheck(Position from, Position to, int identifier);
    // std::cout << "already reached here" << std::endl;
};

#endif