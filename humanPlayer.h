#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include "move.h"
class HumanPlayer : public Player {
    
    public:
        HumanPlayer(int identifier, int currentScore=0);
        HumanPlayer(const HumanPlayer &humanPlayer);
        std::shared_ptr<Player> clone() override;
        // void copyPlayer(const Player &player) override;
        bool tryMakeMove(Move m, Board & board) override;
};
#endif