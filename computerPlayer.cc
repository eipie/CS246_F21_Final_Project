#include "computerPlayer.h"
#include "board.h"

ComputerPlayer::ComputerPlayer(int identifier, int level, int currentScore) 
: Player{identifier, currentScore}, level{level} {}