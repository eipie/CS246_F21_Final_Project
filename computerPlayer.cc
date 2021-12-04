#include "computerPlayer.h"
#include "board.h"
#include <iostream>

ComputerPlayer::ComputerPlayer(int identifier, int level, int currentScore) 
: Player{identifier, false, currentScore}, level{level} {}

ComputerPlayer::ComputerPlayer(const ComputerPlayer &computerPlayer,  bool needToCheckSelfCheck) : Player(computerPlayer,  needToCheckSelfCheck){
    level = computerPlayer.level;
}
std::shared_ptr<Player> ComputerPlayer::clone( bool needToCheckSelfCheck) {
    // std::cout << "copying Computer" << level << std::endl;
    return std::shared_ptr<Player>(new ComputerPlayer(*this));
}


bool ComputerPlayer::tryMakeMove(Move move, Board & board) {

    std::cout << "try to make a move for computer" << std::endl;


    if (level == 1) {
        std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> choices = board.getPlayerPossibleMoves(identifier);
        int totalNumMoves = 0;
        // not possible to be 0, since either stalemate/checkmate detected at last round
        for(auto pieceSet:choices) {
            for(auto move : *pieceSet.second.get()) {
                totalNumMoves++;
            }
        }
        std::srand(std::time(nullptr));
        int random_index = std::rand() % totalNumMoves;
        for (auto pieceSet : choices) {
            std::shared_ptr<std::vector<PossibleMove>> possMoves = pieceSet.second;
            for(auto move : *possMoves.get()) {
                if(random_index==0) {
                    //这里
                    PossibleMove nextMove = move;
                    Position from = pieceSet.first.get()->pos;
                    std::cout << "current position x " << from.x << std::endl;
                    std::cout << "current position y " << from.y << std::endl;

                    std::cout << "target position x " << nextMove.to.x << std::endl;
                    std::cout << "target position y " << nextMove.to.y << std::endl;
                    // call你那个method 直接move
                }
                random_index--;
            }
        }
        return true;
    }
    else if (level == 2) {
        // Call level 2 make move
        std::cout << "computer make move at level 2" << std::endl;
        MakeMoveAtLevel2(board);
    }
    else if (level == 3) {
        std::cout << "computer make move at level 3" << std::endl;
        MakeMoveAtLevel3(board);
    }
    else {
        std::cout << "computer make move at level 4" << std::endl;

        // Call level 4 make move
    }

    return true;
}

bool ComputerPlayer::SimpleMakeMove(Position currentPosition, PossibleMove nextMove, Board &board) {

    std::cout << "current position x " << currentPosition.x << std::endl;
    std::cout << "current position y " << currentPosition.y << std::endl;
    
    std::shared_ptr<ChessPieces> targetPiece = board.getPieceAt(currentPosition);

    std::cout << "x " << targetPiece->pos.x << std::endl;
    std::cout << "y " << targetPiece->pos.y << std::endl;
    std::cout << "icon " << targetPiece->icon << std::endl;

    std::cout << "target piece acquired" << std::endl;
    if (nextMove.kingSideCastle || nextMove.queenSideCastle) {
        movePiece(nextMove.rookFrom, nextMove.rookTo, board);
    }
    if (nextMove.enPassant) {
        board.removePiece(nextMove.enPassantLoc, opponentIdentifier);
    }
    if (nextMove.isPromotion) {
        bool checkPromotionResult = tryDoPawnPromotion(nextMove.promotionType,targetPiece.get()->pos, targetPiece.get()->ownerIdentifier, board);
        if(!checkPromotionResult) {
            return false;
        }
    }
    std::cout << "checking enpassant" << std::endl;
    enPassantAvailabilityCorrect(targetPiece, board, currentPosition, nextMove.to);
    std::cout << "good to move now" << std::endl;
    movePiece(currentPosition, nextMove.to, board);
    return true;
 
}


bool ComputerPlayer::MakeMoveAtLevel1(Position currentPosition, std::vector<PossibleMove> availableMoves, Board & board) {

    // auto it = availableMoves.begin();
    // std::advance(it, rand() % availableMoves.size());
    std::cout << "number of available moves: " << availableMoves.size() << std::endl;

    PossibleMove choseMove = availableMoves[rand() % availableMoves.size()];
    std::cout << "success" << std::endl;
    SimpleMakeMove(currentPosition, choseMove, board);
    return true;

}

bool ComputerPlayer::MakeMoveAtLevel2(Board & board) {

    bool hasCaptureMove = false;
    bool hasCheckMove = false;
    // copy the board: 
    // put in check(opponent_identifier): check the current layout of the board and return a vector containing all pieces that I can move to cause a check
    
    // std::vector<std::shared_ptr<ChessPieces>> putInCheck(int identifier);
    for (auto i: playerPieces) {
        Board tempBoard = board;
        std::vector<PossibleMove> allPossibleMoves = i.second->getPossibleMoves(tempBoard);
        for (auto j: allPossibleMoves) {
            Position current_position = i.first;
            tempBoard.makeAMove(Move(current_position, j.to), identifier);
            std::vector<std::shared_ptr<ChessPieces>> checkMovePieces = tempBoard.putInCheck(opponentIdentifier);
            if (checkMovePieces.size() != 0) {
                // found piece that can check the opponent
                hasCheckMove = true;
                SimpleMakeMove(current_position, j, board);
                return true;
            }
        }
    }

    for (auto i: playerPieces) {
        std::vector<PossibleMove> allPossibleMoves = i.second->getPossibleMoves(board);
        Position current_position = i.first;
        for (auto j: allPossibleMoves) {
            // if the move is a capture, then make that move and return
            if (j.capture == ' ') {
                hasCaptureMove = true;
                SimpleMakeMove(current_position, j, board);
                return true;
            }

        }
    }

    // if there is no capturing move and check move available to the player, the player will make a random, legal move
    if (!hasCaptureMove && !hasCheckMove) {
        auto it = playerPieces.begin();
        std::advance(it, rand() % playerPieces.size());
        std::vector<PossibleMove> allPossibleMoves = it->second->getPossibleMoves(board);
        MakeMoveAtLevel1(it->second->pos, allPossibleMoves, board);
    }
    return true;
}

bool ComputerPlayer::OpponentCaptureAvailable(Board &board) {

    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> playerPossibleMoves = board.getPlayerPossibleMoves(opponentIdentifier);
    for (auto i : playerPossibleMoves) {
        // for each entry in the map
        for (auto j: *i.second) {
            if (j.capture == ' ') {
                // the opponent has capture available
                return true;
            } 
        }
    }
    return false;

}

Position ComputerPlayer::OpponentCapturePos(Board &board) {

    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove> > > playerPossibleMoves = board.getPlayerPossibleMoves(opponentIdentifier);
    for (auto i : playerPossibleMoves) {
        // for each entry in the map
        for (auto j: *i.second) {
            if (j.capture == ' ') {
                // the opponent has capture available
                return j.to;
            } 
        }
    }   
    return Position(-1, -1);

}

bool ComputerPlayer::MakeMoveAtLevel3(Board &board) {

    bool needToAvoidCapture = OpponentCaptureAvailable(board);
    if (needToAvoidCapture) {
        // need to avoid capture case: move the piece at avoidCapturePosition to avoid capture
        Position avoidCapturePosition = OpponentCapturePos(board);
        // available moves for the target piece
        std::vector<PossibleMove> escapeMoves = playerPieces[avoidCapturePosition]->getPossibleMoves(board);
        // selecting a random available move to avoid capture
        PossibleMove escape = escapeMoves[rand() % escapeMoves.size()];
        SimpleMakeMove(avoidCapturePosition, escape, board);
    } else {
        // standard case: prefer capture and checks
        MakeMoveAtLevel2(board);    
    }
    return true;

}
