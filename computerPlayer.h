#ifndef ComputerPLAYER_H
#define ComputerPLAYER_H
#include "player.h"
#include "move.h"
class ComputerPlayer : public Player {
    int level;
    public:
    // white/black AND level of player
        ComputerPlayer(int identifier, int level, int currentScore=0);
        ComputerPlayer(const ComputerPlayer &computerPlayer);
        std::shared_ptr<Player> clone() override;
        bool tryMakeMove(Move m, Board & board) override;
};
#endif