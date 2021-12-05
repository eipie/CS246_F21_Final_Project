#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include "move.h"
class HumanPlayer : public Player {
    
    public:
        HumanPlayer(int identifier, double currentScore=0);
        HumanPlayer(const HumanPlayer &humanPlayer,  bool needToCheckSelfCheck);
        std::shared_ptr<Player> clone( bool needToCheckSelfCheck) override;
        // void copyPlayer(const Player &player) override;
        bool tryMakeMove(Move m, Board & board) override;
};
#endif