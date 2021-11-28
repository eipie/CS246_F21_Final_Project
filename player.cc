#include "player.h"
#include "position.h"
#include "chessPieces.h"
#include "pawn.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include <iostream>

Player::Player(int identifier, int currentScore) : identifier{identifier}, currentScore{currentScore}{
    // std::cout<< "calling constructor" << std::endl;
    resetAllPieces();
};

// strong expection
void Player::movePiece(Position from, Position to) {
    std::cout << "moving pieces..." << from.x << ", " << from.y << "  " << to.x << to.y << std::endl;
    auto fromFindResult = playerPieces.find(from);
    // auto toFindResult = playerPieces.find(to);
    if(fromFindResult != playerPieces.end()) {
        playerPieces.erase(to);
        playerPieces[to] = fromFindResult->second;
        playerPieces.erase(from);
    } else {
        // error, no piece at from
    }
}

void Player::removePieces(Position p) {
    playerPieces.erase(p);
}

char Player::getPieceCharAt(Position p) {
    // std::cout<< "searching location: " << p.x << ", "<< p.y << std::endl;
    auto findResult = playerPieces.find(p);
    if(findResult != playerPieces.end()) {
        return findResult->second.get()->icon;
    } else {
        return ' ';
    }
}



// 8*8 square:
// white:1; black:-1
// start counting from bottom left 
// ...
// 2
// 1    
//   1   2   3   4   ....
void Player::resetAllPieces() {
    playerPieces.clear();
    // initialize Pawn*8
    for(int i = 1; i<=8; i++) {
        // std::cout<< "creating pawn" << std::endl;
        Position newPos;
        if(identifier==1) {
            newPos.x=i;
            newPos.y=2;
        } else {
            newPos.x=i;
            newPos.y=7;
        }
        playerPieces.emplace(newPos,std::make_shared<Pawn>(newPos,identifier));
    }
    // initialize Knight*2
    Position newPos1;
    Position newPos2;
    newPos1.x=2;
    newPos2.x=7;
    if(identifier==1) {
        newPos1.y=1;
        newPos2.y=1;
    } else {
        newPos1.y=8;
        newPos2.y=8;
    }
    playerPieces.emplace(newPos1,std::make_shared<Knight>(newPos1,identifier));
    playerPieces.emplace(newPos2,std::make_shared<Knight>(newPos2,identifier));
    // initialize Rook*2
    newPos1.x=1;
    newPos2.x=8;
    playerPieces.emplace(newPos1,std::make_shared<Rook>(newPos1,identifier));
    playerPieces.emplace(newPos2,std::make_shared<Rook>(newPos2,identifier));
    // initialize Bishop*2
    newPos1.x=3;
    newPos2.x=6;
    playerPieces.emplace(newPos1,std::make_shared<Bishop>(newPos1,identifier));
    playerPieces.emplace(newPos2,std::make_shared<Bishop>(newPos2,identifier));
    // initialize King*1
    newPos1.x=5;
    playerPieces.emplace(newPos1,std::make_shared<King>(newPos1,identifier));
    // initialize Queen*1
    newPos1.x=4;
    playerPieces.emplace(newPos1,std::make_shared<Queen>(newPos1,identifier));
}


void Player::addPiece(Position p, char c) {
    std::shared_ptr<ChessPieces> newPiece;
    switch (c)
    {
    case 'b':
    case 'B':
        newPiece = std::make_shared<Bishop>(p,identifier);
        break;
    case 'k':
    case 'K':
        newPiece = std::make_shared<King>(p,identifier);
        break;
    case 'p':
    case 'P':
        newPiece = std::make_shared<Pawn>(p,identifier);
        break;
    case 'q':
    case 'Q':
        newPiece = std::make_shared<Queen>(p,identifier);
        break;
    case 'r':
    case 'R':
        newPiece = std::make_shared<Rook>(p,identifier);
        break;
    case 'n':
    case 'N':
        newPiece = std::make_shared<Knight>(p,identifier);
        break;
    default:
        // error
        break;
    }
    playerPieces.find(p)->second = newPiece;
    playerPieces.insert({p,newPiece});
}