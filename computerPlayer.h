#ifndef ComputerPLAYER_H
#define ComputerPLAYER_H
#include "player.h"
#include "move.h"
#include "possibleMove.h"
#include <cstdlib>
#include "position.h"
#include <algorithm>
#include <iterator>
#include <map>
#include <ctime>

class ComputerPlayer : public Player {
    int level;
    public:
    // white/black AND level of player
        ComputerPlayer(int identifier, int level, double currentScore=0);
        ComputerPlayer(const ComputerPlayer &computerPlayer,  bool needToCheckSelfCheck);
        std::shared_ptr<Player> clone( bool needToCheckSelfCheck) override;
        bool tryMakeMove(Move m, Board & board) override;
        bool randomLegalMove(Board &board);
        bool SimpleMakeMove(Position currentPosition, PossibleMove nextMove, Board & board);
        bool OpponentCaptureAvailable(Board &board, Position p);
        PossibleMove escapeCapture(Board &board, Position piecePosition);
        bool captureCheckPriorityMove(Board & board);
        bool avoidCapturePriorityMove(Board & board);
        bool smartMove(Board & board);
};
#endif
