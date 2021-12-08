#include "computerPlayer.h"
#include "board.h"
#include <iostream>

ComputerPlayer::ComputerPlayer(int identifier, int level, double currentScore) 
: Player{identifier, false, currentScore}, level{level} {}

ComputerPlayer::ComputerPlayer(const ComputerPlayer &computerPlayer,  bool needToCheckSelfCheck) : Player(computerPlayer,  needToCheckSelfCheck){
    level = computerPlayer.level;
}
std::shared_ptr<Player> ComputerPlayer::clone( bool needToCheckSelfCheck) {
    // std::cout << "copying Computer" << level << std::endl;
    return std::shared_ptr<Player>(new ComputerPlayer(*this));
}


bool ComputerPlayer::randomLegalMove(Board &board) {

    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> choices = board.getPlayerPossibleMoves(identifier);
    int totalNumMoves = 0;
    // not possible to be 0, since either stalemate/checkmate detected at last round
    for(auto pieceSet:choices) {
        for(auto move : *pieceSet.second.get()) {
            totalNumMoves++;
        }
    }
    //加下面这行
    std::srand(std::time(nullptr));
    int random_index = std::rand() % totalNumMoves;
    for (auto pieceSet : choices) {
        std::shared_ptr<std::vector<PossibleMove>> possMoves = pieceSet.second;
        // std::cout << "at " << pieceSet.first.get()->icon << std::endl;
        for(auto move : *possMoves.get()) {
            if(random_index==0) {
                //这里
                PossibleMove nextMove = move;
                Position from = pieceSet.first.get()->pos;
                SimpleMakeMove(from, nextMove, board);
            }
            random_index--;
        }
    }

    return true;
}

bool ComputerPlayer::tryMakeMove(Move move, Board & board) {

    std::cout << "try to make a move for computer" << std::endl;

    if (level == 1) {
        randomLegalMove(board);
    }
    else if (level == 2) {
        // Call level 2 make move
        std::cout << "computer make move at level 2" << std::endl;
        captureCheckPriorityMove(board);
    }
    else if (level == 3) {
        std::cout << "computer make move at level 3" << std::endl;
        avoidCapturePriorityMove(board);
    }
    else {
        std::cout << "computer make move at level 4" << std::endl;

        // Call level 4 make move
    }

    return true;
}

bool ComputerPlayer::SimpleMakeMove(Position currentPosition, PossibleMove nextMove, Board &board) {

    std::shared_ptr<ChessPieces> targetPiece = board.getPieceAt(currentPosition);
    // std::cout << "target piece acquired" << std::endl;

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

    enPassantAvailabilityCorrect(targetPiece, board, currentPosition, nextMove.to);
    // all check complete, move the piece
    movePiece(currentPosition, nextMove.to, board);
    return true;
 
}

bool ComputerPlayer::captureCheckPriorityMove(Board & board) {

    // copy the board: 
    // put in check(opponent_identifier): check the current layout of the board and return a vector containing all pieces that I can move to cause a check
    
    // start by checking if there's any available moves that can put the opponent in check
    
    // if there's no checking move available, the player will check if there's any capture move available

    // since neither option is available, the player will choose a random legal move

    // std::vector<std::shared_ptr<ChessPieces>> putInCheck(int identifier);

    // auto allPossibleMoves = board.getPlayerPossibleMoves(this->identifier);

    // for (auto i: allPossibleMoves) {
    //     auto currentPiece = i.first; 
    //     auto possibleMoveForPiece = i.second.get();
    //     std::cout << "the piece is at position (" << currentPiece->pos.x << ", " << currentPiece->pos.y << ")" << std::endl;

    //     for (auto m: *possibleMoveForPiece) {
    //         std::cout << "the piece can move to position (" << m.to.x << ", " << m.to.y << ")" << std::endl;
    //     }
    //     std::cout << "" << std::endl;
    // }

    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> choices = board.getPlayerPossibleMoves(identifier);
    for (auto pieceSet : choices) {
        std::shared_ptr<std::vector<PossibleMove>> possMoves = pieceSet.second;
        std::cout << "at " << pieceSet.first.get()->icon << std::endl;
        for(auto move : *possMoves.get()) {
            Board tempBoard = Board(board);
            std::cout << "temporary copy created" << std::endl;
            Position starting_position = pieceSet.first->pos;
            Position target_position = move.to;
            std::cout << "current position: " << starting_position.x << ", " << starting_position.y << std::endl;
            std::cout << "target position: " << target_position.x << ", " << target_position.y  << std::endl;
            // Move currentMove = Move(starting_position, target_position);
            // int result = tempBoard.makeAMove(currentMove, identifier);
            // std::cout << "result: " << result << std::endl;
            // if (result == 1) {
            //     std::cout << "found check move" << std::endl;
            //     break;
            // } 
            // if (move.capture != ' ') {
            //     std::cout << "found capture move" << std::endl;
            //     break;
            // }
        }
    }
    std::cout << "end" << std::endl;

    // for (auto i: playerPieces) {
    //     std::vector<PossibleMove> allPossibleMoves = i.second->getPossibleMoves(board);
    //     for (auto j: allPossibleMoves) {
    //         std::cout << "current piece position: " << i.first.x << ", " << i.first.y << std::endl;
    //         std::cout << "possible move to: " << j.to.x << ", " << j.to.y << std::endl; 
    //     }
        
    //     // std::cout << "current position: " << i.first.x << ", " << i.first.y << std::endl;
    //     // std::cout << "number of moves available: " << allPossibleMoves.size() << std::endl;
        
    //     // if (allPossibleMoves.size() != 0) {
    //     //     std::cout << "looking for checks and captures for position" << i.first.x << ", " << i.first.y << std::endl;
    //     //     Position starting_position = i.first;
    //     //     for (int a = 0; a < allPossibleMoves.size(); a++) {
    //     //         Board tempBoard(board, true);
    //     //         std::cout << "temp board created" << std::endl;
    //     //         Position target_position = allPossibleMoves[a].to;
    //     //         Move currentMove(starting_position, target_position);
    //     //         std::cout << "current position: " << starting_position.x << ", " << starting_position.y << std::endl;
    //     //         std::cout << "target position: " << target_position.x << ", " << target_position.y << std::endl;
    //     //         int result = tempBoard.makeAMove(currentMove, identifier);
    //     //         std::cout << "result" << result << std::endl;
    //     //         if (result == 1) {
    //     //             // found the check move that we need
    //     //             std::cout << "found check move" << std::endl;
    //     //             std::cout << "current position: " << starting_position.x << ", " << starting_position.y << std::endl;
    //     //             std::cout << "target position: " << target_position.x << ", " << target_position.y << std::endl;
    //     //             break;
    //     //         } else {
    //     //             if (allPossibleMoves[a].capture != ' ') {
    //     //                 // found capture;
    //     //                 std::cout << "found capture move" << std::endl;
    //     //                 std::cout << "current position: " << starting_position.x << ", " << starting_position.y << std::endl;
    //     //                 std::cout << "target position: " << target_position.x << ", " << target_position.y << std::endl;
    //     //                 break;
    //     //             }
    //     //         }
                
    //     //     }
    //     //     // for (auto j: allPossibleMoves) {
    //     //         // create a temporary board
    //     //         // Board tempBoard(board, false);
    //     //         // std::cout << "temp board created" << std::endl;
    //     //         // Position starting_position = i.first;
    //     //         // Position target_position = j.to;
    //     //         // Move currentMove(starting_position, target_position);
    //     //         // std::cout << "current position: " << starting_position.x << ", " << starting_position.y << std::endl;
    //     //         // std::cout << "target position: " << target_position.x << ", " << target_position.y << std::endl;
    //     //         // int result = tempBoard.makeAMove(currentMove, identifier);
    //     //         // if (result == 1) {
    //     //         //     // found the check move that we need
    //     //         //     std::cout << "found check move" << std::endl;
    //     //         //     std::cout << "current position: " << starting_position.x << ", " << starting_position.y << std::endl;
    //     //         //     std::cout << "target position: " << target_position.x << ", " << target_position.y << std::endl;
    //     //         //     break;
    //     //         // } else {
    //     //         //     if (j.capture != ' ') {
    //     //         //         // found capture;
    //     //         //         std::cout << "found capture move" << std::endl;
    //     //         //         std::cout << "current position: " << starting_position.x << ", " << starting_position.y << std::endl;
    //     //         //         std::cout << "target position: " << target_position.x << ", " << target_position.y << std::endl;
    //     //         //         break;
    //     //         //     }
    //     //         // }
    //     //     // }
    //     // }
        
        
    //     std::cout << "" << std::endl;
        
    // }

    return true;
}

bool ComputerPlayer::OpponentCaptureAvailable(Board &board) {

    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> playerPossibleMoves = board.getPlayerPossibleMoves(opponentIdentifier);
    for (auto i : playerPossibleMoves) {
        // for each entry in the map
        for (auto j: *i.second) {
            if (j.capture != ' ') {
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
            if (j.capture != ' ') {
                // the opponent has capture available
                return j.to;
            } 
        }
    }   
    return Position(-1, -1);

}

bool ComputerPlayer::avoidCapturePriorityMove(Board &board) {

    bool needToAvoidCapture = OpponentCaptureAvailable(board);
    // std::cout << needToAvoidCapture << std::endl;

    if (needToAvoidCapture) { 
        std::cout << "computer need to avoid capture first" << std::endl;
        // need to avoid capture case: move the piece at avoidCapturePosition to avoid capture
        Position avoidCapturePosition = OpponentCapturePos(board);
        std::cout << "avoid x: " << avoidCapturePosition.x << std::endl;
        std::cout << "avoid y: " << avoidCapturePosition.y << std::endl;
        std::vector<PossibleMove> escapeMoves = playerPieces[avoidCapturePosition]->getPossibleMoves(board);
    //     // available moves for the target piece
    //     // selecting a random available move to avoid capture
    //     PossibleMove escape = escapeMoves[rand() % escapeMoves.size()];
    //     SimpleMakeMove(avoidCapturePosition, escape, board);
    } else {
        std::cout << "no avoiding capture necessary" << std::endl;
        // std::vector<PossibleMove> moves = playerPieces[Position(1, 7)]->getPlayerPossibleMoves(board);
        // for (int i = 0; i < moves.size(); i++) {
        //     std::cout << "available move: " << moves[i].to.x << ", " << moves[i].to.y << std::endl; 
        // }
    //     standard case: prefer capture and checks
    //     captureCheckPriorityMove(board);    
    }
    return true;

}
