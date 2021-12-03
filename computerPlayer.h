#ifndef ComputerPLAYER_H
#define ComputerPLAYER_H
#include "player.h"
#include "move.h"
#include "possibleMove.h"
#include <stdlib.h>
#include "position.h"
#include <algorithm>
#include <iterator>
#include <map>

class ComputerPlayer : public Player {
    int level;
    public:
    // white/black AND level of player
        ComputerPlayer(int identifier, int level, int currentScore=0);
        ComputerPlayer(const ComputerPlayer &computerPlayer);
        std::shared_ptr<Player> clone() override;
        bool tryMakeMove(Move m, Board & board) override;
        bool SimpleMakeMove(Position currentPosition, PossibleMove nextMove, Board & board);
        bool MakeMoveAtLevel1(Position currentPosition, std::vector<PossibleMove> availableMoves, Board & board);
        bool MakeMoveAtLevel2(Board & board);
        bool OpponentCaptureAvailable(Board & board);
        Position OpponentCapturePos(Board & board);
        bool MakeMoveAtLevel3(Board & board);

};
#endif
