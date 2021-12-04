#include "computerPlayer.h"
#include "board.h"
#include <iostream>

ComputerPlayer::ComputerPlayer(int identifier, int level, int currentScore) 
: Player{identifier, false, currentScore}, level{level} {}

ComputerPlayer::ComputerPlayer(const ComputerPlayer &computerPlayer,  bool needToCheckSelfCheck) : Player(computerPlayer,  needToCheckSelfCheck){
    level = computerPlayer.level;
}
std::shared_ptr<Player> ComputerPlayer::clone( bool needToCheckSelfCheck) {
    std::cout << "copying Computer" << level << std::endl;
    return std::shared_ptr<Player>(new ComputerPlayer(*this));
}

bool ComputerPlayer::tryMakeMove(Move move, Board & board) {
    return true;
}

/* bool ComputerPlayer::tryMakeMove(Move move, Board & board) {

    std::cout << "try to make a move for computer" << std::endl;
    if (level == 1) {
        std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> choices = board.getPlayerPossibleMoves(identifier);
        int totalNumMoves = 0;
        // not possible to be 0, since either stalemate/checkmate detected at last round
        for(auto pieceSet:choices) {
            for(auto move : *pieceSet.second.get()) {
                totalNumMoves++;
            }
        }
        int random_index = std::rand() % totalNumMoves;
        for (auto pieceSet : choices) {
            std::shared_ptr<std::vector<PossibleMove>> possMoves = pieceSet.second;
                for(auto move : *possMoves.get()) {
                    if(random_index==0) {
                        //这里
                        PossibleMove nextMove = move;
                        Position from = pieceSet.first.get()->pos;
                        // call你那个method 直接move
                    }
                    random_index--;
                }
        }
    }
    else if (level == 2) {
        // Call level 2 make move
        std::cout << "computer make move at level 2" << std::endl;
        MakeMoveAtLevel2(board);
    }
    else if (level == 3) {
        std::cout << "computer make move at level 3" << std::endl;
        MakeMoveAtLevel3(board);
    }
    else {
        std::cout << "computer make move at level 4" << std::endl;

        // Call level 4 make move
    }

    return true;
}
 */
