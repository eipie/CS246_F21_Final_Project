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

