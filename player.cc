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
#include <algorithm>

Player::Player(int identifier, bool isHuman, double currentScore) :  identifier{identifier}, isHuman{isHuman},isInCheck{false}, currentScore{currentScore}{
    // std::cout<< "calling constructor" << std::endl;
    if(identifier==1) {
        opponentIdentifier = 0;
    } else {
        opponentIdentifier = 1;
    }
    resetAllPieces();
};

Player::Player(const Player &player, bool needToCheckSelfCheck) {
    identifier = player.identifier;
    opponentIdentifier = player.opponentIdentifier;
    isInCheck = player.isInCheck;
    currentScore = player.currentScore;
    std::map<Position, std::shared_ptr<ChessPieces>> pieces;
    for(auto piecePair:player.playerPieces) {
        std::shared_ptr<ChessPieces> newPiece = piecePair.second.get()->clone(needToCheckSelfCheck);
        pieces[piecePair.first] = newPiece;
    }
    playerPieces = pieces;
    isHuman = player.isHuman;
    // copyPlayer(player);
}

void Player::enPassantAvailabilityCorrect(std::shared_ptr<ChessPieces> pieceToBeMoved, Board & board, Position from, Position to) {
    if(pieceToBeMoved==nullptr) {
        std::cout <<"nullptr..." <<std::endl;
        return;
    }
    board.disableAllEnPassant();
    if((pieceToBeMoved.get()->icon=='p' || pieceToBeMoved.get()->icon=='P') && (abs(from.y-to.y)==2)) {
        if(abs(from.y-to.y)==2) {
            pieceToBeMoved.get()->availableForEnPassant=true;
        } 
    }
}

// do not check if legal, make move directly
// tryMakeMove in child handle legal/illegal detection
// strong expection
void Player::movePiece(Position from, Position to, Board & board) {
    // std::cout << "moving pieces..." << from.x << ", " << from.y << "  " << to.x << to.y << std::endl;
    auto fromFindResult = playerPieces.find(from);
    // auto toFindResult = playerPieces.find(to);
    if(fromFindResult != playerPieces.end()) {
        fromFindResult->second.get()->afterFirstMove();
        board.removePiece(to, opponentIdentifier);
        fromFindResult->second.get()->setPos(to);
        playerPieces[to] = fromFindResult->second;
        playerPieces.erase(from);
    } else {
        // error, no piece at from
    }
}

void Player::getAllPossMoves(std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> & playerAllPossMoves, const Board & board) const{
    for(auto pieceSet: playerPieces) {
        std::shared_ptr<ChessPieces> currentPiece = pieceSet.second;
        // std::vector<PossibleMove> piecePossMoves = currentPiece.get()->getPossibleMoves(*this);
        auto piecePossMoves = std::make_shared<std::vector<PossibleMove>>(currentPiece.get()->getPossibleMoves(board));
        
        // std::cout << "storing... " << currentPiece.get()->pos.x << "|" << currentPiece.get()->pos.y << std::endl;
        playerAllPossMoves[currentPiece]  = piecePossMoves;
    }
}

/* std::vector<PossibleMove> Player::kingEscapeTrap(Board & board) {
    std::vector<PossibleMove> allKingMove = getKing().get()->getPossibleMoves(board);
    auto allOpponentsNextMove = board.getPlayerPossibleMoves(opponentIdentifier);
    for(auto kingMove : allKingMove) {
        
    }
     for(auto oppMoveSet : allOpponentsNextMove) {
        for(auto oppPossMove : *oppMoveSet.second.get()) {
            allKingMove.erase(std::find(allKingMove.begin(), allKingMove.end(), oppPossMove));
        }  
    } 
    return allKingMove;
}    */

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

std::shared_ptr<ChessPieces> Player::getKing() {
    for(auto pieceSet: playerPieces) {
        auto pieceCandidate = pieceSet.second;
        if(pieceCandidate.get()->icon=='K'||pieceCandidate.get()->icon=='k') {
            return pieceCandidate;
        }
    }
    return nullptr;
}

int Player::countKing() {
    int count = 0;
    if(identifier==1) {
            for(auto pieceSet: playerPieces) {
                auto pieceCandidate = pieceSet.second;
                if (pieceCandidate.get()->icon == 'K') {
                    ++count;
                }
            }
            // for testing only...
            if(count==0) {
                std::cout << "white" << std::endl;
            }
            return count;
    } else {
            for(auto pieceSet: playerPieces) {
                auto pieceCandidate = pieceSet.second;
                if (pieceCandidate.get()->icon == 'k') {
                    ++count;
                }
            }
            if(count==0) {
                std::cout << "black" << std::endl;
            }
            return count;
    }
    return count;
}


std::shared_ptr<ChessPieces> Player::getPieceAt(Position p) const {
    auto findResult = playerPieces.find(p);
    if(findResult != playerPieces.end()) {
        return findResult->second;
    } else {
        return nullptr;
    }
}

void Player::disableAllEnPassant() {
    for(auto piecePair : playerPieces) {
        piecePair.second.get()->availableForEnPassant=false;
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
    isInCheck=false;
    // currentScore=0;
    playerPieces.clear();
    // initialize Pawn*8
    for(int i = 1; i<=HIGHER_BOUND; i++) {
        // std::cout<< "creating pawn" << std::endl;
        Position newPos;
        if(identifier==1) {
            newPos.x=i;
            newPos.y=2;
        } else {
            newPos.x=i;
            newPos.y=HIGHER_BOUND - 1;
        }
        playerPieces.emplace(newPos,std::make_shared<Pawn>(newPos,identifier));
    }
    // initialize Knight*2
    Position newPos1;
    Position newPos2;
    newPos1.x=2;
    newPos2.x=HIGHER_BOUND - 1;
    if(identifier==1) {
        newPos1.y=1;
        newPos2.y=1;
    } else {
        newPos1.y=HIGHER_BOUND;
        newPos2.y=HIGHER_BOUND;
    }
    playerPieces.emplace(newPos1,std::make_shared<Knight>(newPos1,identifier));
    playerPieces.emplace(newPos2,std::make_shared<Knight>(newPos2,identifier));
    // initialize Rook*2
    newPos1.x=1;
    newPos2.x=HIGHER_BOUND;
    playerPieces.emplace(newPos1,std::make_shared<Rook>(newPos1,identifier));
    playerPieces.emplace(newPos2,std::make_shared<Rook>(newPos2,identifier));
    // initialize Bishop*2
    newPos1.x=3;
    newPos2.x=HIGHER_BOUND - 2;
    playerPieces.emplace(newPos1,std::make_shared<Bishop>(newPos1,identifier));
    playerPieces.emplace(newPos2,std::make_shared<Bishop>(newPos2,identifier));
    // initialize King*1
    newPos1.x=5;
    playerPieces.emplace(newPos1,std::make_shared<King>(newPos1,identifier));
    // initialize Queen*1
    newPos1.x=4;
    playerPieces.emplace(newPos1,std::make_shared<Queen>(newPos1,identifier));
}


bool Player::addPiece(Position p, char c) {
    std::shared_ptr<ChessPieces> newPiece;
    switch (c)
    {
    case 'b':
    case 'B':
        removePieces(p);
        newPiece = std::make_shared<Bishop>(p,identifier);
        break;
    case 'k':
    case 'K':
        removePieces(p);
        newPiece = std::make_shared<King>(p,identifier);
        break;
    case 'p':
    case 'P':
        removePieces(p);
        newPiece = std::make_shared<Pawn>(p,identifier);
        break;
    case 'q':
    case 'Q':
        removePieces(p);
        newPiece = std::make_shared<Queen>(p,identifier);
        break;
    case 'r':
    case 'R':
        removePieces(p);
        newPiece = std::make_shared<Rook>(p,identifier);
        break;
    case 'n':
    case 'N':
        removePieces(p);
        newPiece = std::make_shared<Knight>(p,identifier);
        break;
    default:
        // error
        return false;
        break;
    }
    playerPieces[p] = newPiece;
    return true;
    /* playerPieces.find(p)->second = newPiece;
    playerPieces.insert({p,newPiece}); */
}


bool Player::tryDoPawnPromotion(char promotion, Position promoteLoc, int identifier, Board & board) {
    if((identifier==0 && (promotion == 'p'|| promotion == 'r'|| promotion == 'n'|| promotion == 'b'|| promotion == 'q'))
        || (identifier==1 && (promotion == 'P'|| promotion == 'R'|| promotion == 'N'|| promotion == 'B'|| promotion == 'Q'))) {
        
        if(promotion== 'p'||promotion=='P') {

        } else if(promotion== 'r'||promotion=='R') {
            std::cout << "rook promotion detected" << std::endl;
            if(identifier==1) {
                removePieces(promoteLoc);
                addPiece(promoteLoc, 'R');
            } else {
                removePieces(promoteLoc);
                addPiece(promoteLoc, 'r');
            }
            
        } else if(promotion== 'n'||promotion=='N') {
            if(identifier==1) {
                removePieces(promoteLoc);
                addPiece(promoteLoc, 'N');
            } else {
                removePieces(promoteLoc);
                addPiece(promoteLoc, 'n');
            }
        } else if(promotion== 'b'||promotion=='B') {
            if(identifier==1) {
                removePieces(promoteLoc);
                addPiece(promoteLoc, 'B');
            } else {
                removePieces(promoteLoc);
                addPiece(promoteLoc, 'b');
            }
        } else if(promotion== 'q'||promotion=='Q') {
            if(identifier==1) {
                removePieces(promoteLoc);
                addPiece(promoteLoc, 'Q');
            } else {
                removePieces(promoteLoc);
                addPiece(promoteLoc, 'q');
            }
        }
        return true;
    } 
    return false;
}
