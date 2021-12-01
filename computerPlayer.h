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
        bool tryMakeMove(Move m, const Board & board) override;
        bool MakeMoveAtLevel1(Position currentPosition, std::vector<PossibleMove> availableMoves);
        bool MakeMoveAtLevel2(const Board & board);

};
#endif
