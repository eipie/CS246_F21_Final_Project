#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <vector>
#include <map>
class Position;
class ChessPieces;
class Player {
/*     int numPawn = 8;
    int numKnight = 2;
    int numRook = 2;
    int numBishop = 2;
    int numKing = 1;
    int numQueen = 1; */
    int currentScore;
    // -1:black; 1:white;
    int identifier;
    
    public:
    // use map for easier lookup
    std::map<Position, std::shared_ptr<ChessPieces>> playerPieces;

    Player(int identifier, int currentScore=0);
    void removePieces(Position p);
    // void addPieces(Position p, char c);
    void resetAllPieces();
}

#endif