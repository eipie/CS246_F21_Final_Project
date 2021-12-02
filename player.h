#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <vector>
#include <map>
#include "move.h"

class PossibleMove;
class Position;
class ChessPieces;
class Board;
class Player {
/*     int numPawn = 8;
    int numKnight = 2;
    int numRook = 2;
    int numBishop = 2;
    int numKing = 1;
    int numQueen = 1; */
    
    protected:
    // 0:black; 1:white;
    int identifier;
    int opponentIdentifier;
    std::shared_ptr<ChessPieces> getKing();
    // computer always true
    bool tryDoPawnPromotion(char promotion, std::shared_ptr<ChessPieces> target);
    // computer always true
    bool moveWithSpecial(PossibleMove possMove);
    // return all possible ways current player can escape Check
    
    public:
    // use map for easier lookup
    bool isInCheck = false;
    int currentScore;
    std::map<Position, std::shared_ptr<ChessPieces>> playerPieces;
    // std::vector<PossibleMove> Player::kingEscapeTrap(Board & board);
    Player(int identifier, int currentScore=0);
    
    void removePieces(Position p);
    // void addPieces(Position p, char c);
    void resetAllPieces();
    void movePiece(Position from, Position to);
    void addPiece(Position p, char c);
    char getPieceCharAt(Position p);
    std::shared_ptr<ChessPieces> getPieceAt(Position p) const;
    virtual bool tryMakeMove(Move m, Board & board) = 0;
    void disableAllEnPassant();
    // std::map<std::shared_ptr<ChessPieces>, std::vector<PossibleMove>> getPlayerPossibleMoves();

};

#endif