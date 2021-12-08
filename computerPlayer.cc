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

    // std::cout << "try to make a move for computer" << std::endl;

    if (level == 1) {
        randomLegalMove(board);
    }
    else if (level == 2) {
        // Call level 2 make move
        // std::cout << "computer make move at level 2" << std::endl;
        captureCheckPriorityMove(board);
    }
    else if (level == 3) {
        // std::cout << "computer make move at level 3" << std::endl;
        avoidCapturePriorityMove(board);
    }
    else {
        // std::cout << "computer make move at level 4" << std::endl;

        // Call level 4 make move
    }

    return true;
}

bool ComputerPlayer::SimpleMakeMove(Position currentPosition, PossibleMove nextMove, Board &board) {

    std::shared_ptr<ChessPieces> targetPiece = getPieceAt(currentPosition);
    if(targetPiece==nullptr) {
        std::cout <<"nullptr outer..." <<std::endl;
    }
    std::cout << "we are here" << std::endl;
    if (nextMove.kingSideCastle || nextMove.queenSideCastle) {
        movePiece(nextMove.rookFrom, nextMove.rookTo, board);
    }
    std::cout << "we are here 2" << std::endl;
    if (nextMove.enPassant) {
        board.removePiece(nextMove.enPassantLoc, opponentIdentifier);
    }
    std::cout << "we are here 3" << std::endl;
    if (nextMove.isPromotion) {
        bool checkPromotionResult = tryDoPawnPromotion(nextMove.promotionType,targetPiece.get()->pos, targetPiece.get()->ownerIdentifier, board);
        if(!checkPromotionResult) {
            return false;
        }
    }
    std::cout << "we are here 4" << std::endl;
    enPassantAvailabilityCorrect(targetPiece, board, currentPosition, nextMove.to);
    // all check complete, move the piece
    std::cout << "we are here 5" << std::endl;
    movePiece(currentPosition, nextMove.to, board);
    return true;

}

bool ComputerPlayer::captureCheckPriorityMove(Board & board) {

    // copy the board: 
    // start by checking if there's any available moves that can put the opponent in check
    // if there's no checking move available, the player will check if there's any capture move available
    // since neither option is available, the player will choose a random legal move
    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> choices = board.getPlayerPossibleMoves(identifier);
    for (auto pieceSet : choices) {
        std::shared_ptr<std::vector<PossibleMove>> possMoves = pieceSet.second;
        // std::cout << "at " << pieceSet.first.get()->icon << std::endl;
        for(auto move : *possMoves.get()) {
            Board tempBoard{board};
            // std::cout << "temporary copy created" << std::endl;
            const Position starting_position = pieceSet.first->pos;
            const Position target_position = move.to;
            std::cout << "current position: " << starting_position.x << ", " << starting_position.y << std::endl;
            std::cout << "target position: " << target_position.x << ", " << target_position.y  << std::endl;
            Move currentMove{starting_position, target_position};

            // int result = tempBoard.makeAMove(currentMove, identifier);
            tempBoard.makeAMoveWithoutCheck(starting_position, target_position, identifier);
            if (tempBoard.putInCheck(opponentIdentifier).size()!=0) {
                std::cout << "found check move" << std::endl;
                SimpleMakeMove(starting_position, move, board);
                return true;
            }
            if (move.capture != ' ') {
                std::cout << "found capture move  " << pieceSet.first.get()->icon << std::endl;
                std::cout << pieceSet.first->pos.x << " | " << pieceSet.first->pos.y  << std::endl;
                std::cout << starting_position.x << " | " << starting_position.y  << std::endl;
                 std::cout << move.to.x << " | " << move.to.y  << std::endl;
                SimpleMakeMove(starting_position, move, board);
                //SimpleMakeMove(starting_position, move, board);
                return true;
            }
        }
    }
    std::cout<<"performing randomeLegal" <<std::endl;
    // since there's no capture or check move available for the player, the player will make a random legal move from its current piece
    randomLegalMove(board);

    return true;
}

// returns true if the opponent can capture the piece at Position targetPosition
bool ComputerPlayer::OpponentCaptureAvailable(Board &board, Position targetPosition) {

    auto opponentAllMoves = board.getPlayerPossibleMoves(opponentIdentifier);
    for (auto i: opponentAllMoves) {
        for (auto j: *i.second) {
            if (j.capture != ' ' && j.to == targetPosition) {
                return true;
            }
        }
    }
    return false;

}

Position ComputerPlayer::escapeCapture(Board &board, Position p) {

    std::shared_ptr<ChessPieces> piece = board.getPieceAt(p);
    std::map<std::shared_ptr<ChessPieces>, std::shared_ptr<std::vector<PossibleMove>>> allPossibleMoves = board.getPlayerPossibleMoves(identifier);
    std::shared_ptr<std::vector<PossibleMove>> escapeChoices = allPossibleMoves[piece];
    if (escapeChoices->size() == 0) {
        // can't avoid the capture, returning a null position
        return Position{-1, -1};
    } else {
        // could be a random move here
        PossibleMove escapeTo = escapeChoices->at(0);
        return escapeTo.to;
    }

}


bool ComputerPlayer::avoidCapturePriorityMove(Board &board) {

    for (auto i: playerPieces) {
        Position piecePosition = i.first;
        bool opponentCanCapture = OpponentCaptureAvailable(board, piecePosition);
        if (opponentCanCapture) {
            Position escapePosition = escapeCapture(board, piecePosition);
            Position nullPosition{-1, -1};
            if (escapePosition == nullPosition) {
                // can't escape
            } else {
                // escape by calling simpleMakeMove
            }
        } else {
            // we can move on checking on the next piece
        }
    }

    // at this point, the player finished avoiding capture since either:
        // the player detected capture and avoided it,
        // the player detected capture and can't avoid it
        // the player's pieces won't be captured for this round

    captureCheckPriorityMove(board);

    return true;

}


