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
    bool noPawnFirstLastRow() const;
    public:
    std::vector<std::shared_ptr<Player>> players;
    // constructor
    Board(std::vector<std::shared_ptr<Player> > players);
    // copy constructor
    Board(const Board &board,  bool needToCheckSelfCheck=true);
    int makeAMove(Move m, int currentPlayer);
    void resetBoard();
    bool removePiece(Position p, int currentPlayer);
    bool addPiece(Position p, char c);
    // to be implemented, dummy variable
    bool isBoardSetupValid() const;
    char getPieceCharAt(Position p) const;
    std::shared_ptr<ChessPieces> getPieceAt(Position p) const;
    char isOpponentPiece(Position target, int identifier) const;
    bool isEmpty(Position target) const;
    int getPlayerAllPiecesWeight(int identifier) const;
    // return all pieces that currently puts identifier's king in check
    std::vector<std::shared_ptr<ChessPieces>> putInCheck(int identifier) const;
    // all possible moves of all the pieces player identifier has
    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> getPlayerPossibleMoves (int identifier) const;
    // check if a player is in check (incheck variable in Player class)
    bool ifInCheck(int identifier) const;
    void disableAllEnPassant();
    void makeAMoveWithoutCheck(Position from, Position to, int identifier);
    Position getHint(Position starting_position, std::vector<PossibleMove> possMoves, int identifier) const;
};

#endif
