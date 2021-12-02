#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include "move.h"
class HumanPlayer : public Player {
    bool validPromotion(char promotion, std::shared_ptr<ChessPieces> target);
    public:
        HumanPlayer(int identifier, int currentScore=0);
        bool tryMakeMove(Move m, Board & board) override;
};
#endif