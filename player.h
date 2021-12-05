#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <vector>
#include <map>
#include "move.h"

struct PossibleMove;
struct Position;
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
    bool tryDoPawnPromotion(char promotion, Position promoteLoc, int identifier, Board & board);
    ChessPieces * tryDoPawnPromotion(char promotion, ChessPieces * target);
    // computer always true
    bool moveWithSpecial(PossibleMove possMove);
    // return all possible ways current player can escape Check
    void enPassantAvailabilityCorrect(std::shared_ptr<ChessPieces> pieceToBeMoved, Board & board, Position from, Position to);
    
    public:
    bool isHuman;
    // use map for easier lookup
    bool isInCheck = false;
    int currentScore=0;
    std::map<Position, std::shared_ptr<ChessPieces>> playerPieces;
    
    // std::vector<PossibleMove> Player::kingEscapeTrap(Board & board);
    Player(int identifier, bool isHuman, int currentScore=0);
    Player(const Player &player,  bool needToCheckSelfCheck);
    virtual std::shared_ptr<Player> clone( bool needToCheckSelfCheck) =0;

    void removePieces(Position p);
    // void addPieces(Position p, char c);
    void resetAllPieces();
    void movePiece(Position from, Position to, Board & board);
    void addPiece(Position p, char c);
    char getPieceCharAt(Position p);
    std::shared_ptr<ChessPieces> getPieceAt(Position p) const;
    virtual bool tryMakeMove(Move m, Board & board) = 0;
    void disableAllEnPassant();
    int countKing();
    // std::map<std::shared_ptr<ChessPieces>, std::vector<PossibleMove>> getPlayerPossibleMoves();

};

#endif