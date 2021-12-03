#include "computerPlayer.h"
#include "board.h"
#include <iostream>

ComputerPlayer::ComputerPlayer(int identifier, int level, int currentScore) 
: Player{identifier, currentScore}, level{level} {}

ComputerPlayer::ComputerPlayer(const ComputerPlayer &computerPlayer) : Player(computerPlayer){
    level = computerPlayer.level;
}
std::shared_ptr<Player> ComputerPlayer::clone() {
    std::cout << "copying Computer" << level << std::endl;
    return std::shared_ptr<Player>(new ComputerPlayer(*this));
}