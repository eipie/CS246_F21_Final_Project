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
    // computer always true
    bool moveWithSpecial(PossibleMove possMove);
    // return all possible ways current player can escape Check
    void enPassantAvailabilityCorrect(std::shared_ptr<ChessPieces> pieceToBeMoved, Board & board, Position from, Position to);
    
    public:
    bool isHuman;
    // use map for easier lookup
    bool isInCheck = false;
    double currentScore=0;
    std::map<Position, std::shared_ptr<ChessPieces>> playerPieces;

    Player(int identifier, bool isHuman, double currentScore=0);
    Player(const Player &player,  bool needToCheckSelfCheck);
    // helper for copy constructor
    virtual std::shared_ptr<Player> clone( bool needToCheckSelfCheck) =0;
    // talley all scores from pieces for level4 computer
    int getAllPieceScore() const;
    // remove a piece from current player, do nothing if current player does not have piece at p
    void removePieces(Position p);
    // used to reset all pieces to initial position, when creating new round
    void resetAllPieces();
    // move a piece from Position form to to inside board, without checking rules; remove captured piece from board
    // will appear as if nothing changed if piece at from does not have piece of current player
    void movePiece(Position from, Position to, Board & board);
    // add a Piece of character c to position p
    // if currentplayer has piece at location p, remove it before add
    // will not check if c follows identity
    bool addPiece(Position p, char c);
    // return character representaiton of piece at p
    // return ' ' if not found
    char getPieceCharAt(Position p) const;
    // return pointer to chessPiece of piece at p
    // return nullptr if not found
    std::shared_ptr<ChessPieces> getPieceAt(Position p) const;
    // move piece with checking if move is valid
    virtual bool tryMakeMove(Move m, Board & board) = 0;
    // reset all availableForEnPassant attribute to false one round after any Pawn make 2-step first move
    void disableAllEnPassant();
    // return number of king current player has
    int countKing() const;
    // emplace all possible moves of all pieces of current player into map possMoves
    void getAllPossMoves(std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> & possMoves, const Board & board) const;
};

#endif