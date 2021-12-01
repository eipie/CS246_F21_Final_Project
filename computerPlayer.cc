#include "computerPlayer.h"
#include "board.h"

ComputerPlayer::ComputerPlayer(int identifier, int level, int currentScore) 
: Player{identifier, currentScore}, level{level} {}

bool ComputerPlayer::tryMakeMove(Move move, const Board & board) {

    if (level == 1) {
        // select a random piece from the all the chesspieces that the player has;
        auto it = playerPieces.begin();
        std::advance(it, rand() % playerPieces.size());
        // a vector of all possible moves that the chesspiece may perform
        std::vector<PossibleMove> allPossibleMoves = it->second->getPossibleMoves(board);
        MakeMoveAtLevel1(it->second->pos, allPossibleMoves);
    }
    else if (level == 2) {
        // Call level 2 make move
        MakeMoveAtLevel2(board);
    }
    else if (level == 3) {
        // Call level 3 make move
    }
    else {
        // Call level 4 make move
    }

    return true;
}

bool ComputerPlayer::MakeMoveAtLevel1(Position currentPosition, std::vector<PossibleMove> availableMoves) {

    auto it = availableMoves.begin();
    std::advance(it, rand() % availableMoves.size());
    
    movePiece(currentPosition, it->to);
    return true;

}

bool ComputerPlayer::MakeMoveAtLevel2(const Board & board) {

    bool hasCaptureMove = false;
    bool hasCheckMove = false;
    for (auto i: playerPieces) {
        std::vector<PossibleMove> allPossibleMoves = i.second->getPossibleMoves(board);
        Position current_position = i.first;
        for (auto j: allPossibleMoves) {
            // if the move is a capture, then make that move and return
            // hasCaptureMove = true;
            if (j.capture == ' ') {
                hasCaptureMove = true;
                movePiece(current_position, j.to);
            }
            // if the move is a check, then make that move and return
            // hasCheckMove = true;
        }
    }

    if (!hasCaptureMove && !hasCheckMove) {
        auto it = playerPieces.begin();
        std::advance(it, rand() % playerPieces.size());
        std::vector<PossibleMove> allPossibleMoves = it->second->getPossibleMoves(board);
        MakeMoveAtLevel1(it->second->pos, allPossibleMoves);
    }

    return true;
}
