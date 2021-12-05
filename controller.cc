#include "chessGame.h"
#include "move.h"
#include "position.h"
#include <string>
#include <iostream>
#include <sstream>

int main() {
    ChessGame *chess;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::string command;
        std::stringstream ss(line);
        ss >> command;
        if (command == "game") {
            std::string game1;
            std::string game2;
            std::vector<int> levels{0,0};
            bool isHuman1 = true;
            bool isHuman2 = true;
            if (ss >> game1) {
                if (game1 == "human") {
                } else if (game1 ==  "computer[1]") {
                    isHuman1 = false;
                    levels[0] = 1;
                } else if (game1 == "computer[2]") {
                    isHuman1 = false;
                    levels[0] = 2;
                } else if (game1 == "computer[3]") {
                    isHuman1 = false;
                    levels[0] = 3;
                } else if (game1 == "computer[4]") {
                    isHuman1 = false;
                    levels[0] = 4;
                } else {
                    //invalid
                }
            } else {
                //invalid
            }
            if (ss >> game2) {
                if (game2 == "human") {
                } else if (game2 ==  "computer[1]") {
                    isHuman2 = false;
                    levels[1] = 1;
                } else if (game2 ==  "computer[2]") {
                    isHuman2 = false;
                    levels[1] = 2;
                } else if (game2 ==  "computer[3]") {
                    isHuman2 = false;
                    levels[1] = 3;
                } else if (game2 ==  "computer[4]") {
                    isHuman2 = false;
                    levels[1] = 4;
                } else {
                    //invalid
                }
            } else {
                //invalid
            }
            chess = new ChessGame(isHuman1, isHuman2, levels);
        } else if (command == "resign") {
            std::cout << chess->resign() << std::endl;
            break;
        } else if (command == "move") {
            std::string from_str;
            std::string to_str;
            Position from;
            Position to;
            Move nextMove;
            std::string moveResult;
            if (ss >> from_str >> to_str) {
                from.x = from_str[0] - 'a' + 1;
                from.y = from_str[1] - '0';
                to.x = to_str[0] - 'a' + 1;
                to.y = to_str[1] - '0';
                nextMove.from = from;
                nextMove.to = to;
                char promo;
                if (ss >> promo) {
                    nextMove.isPromotion = true;
                    nextMove.promotionType = promo;
                    Move nextMove(from , to, promo);
                    moveResult = chess->makeAMove(nextMove);
                } else {
                    Move nextMove(from, to);
                    moveResult = chess->makeAMove(nextMove);
                }
            } else {
                Move nextMove;
                moveResult = chess->makeAMove(nextMove);
            }
            std::cout << moveResult << std::endl;
        } else if (command == "setup") { 
            // check if the game has started, then allow setup;
            // while loop until the user type done, then call isboardvalid
            std::string operation;
            ss >> operation;
            while (true) {
                if (operation == "done") {
                    if (chess->isBoardSetupValid()) {
                        break;
                    } else {
                        // cout << "Cannot leave set up mode yet" << endl;
                        continue;
                    }
                } else if (operation == "+") {
                    char p;
                    std::string pos_str;
                    if (ss >> p >> pos_str) {
                        Position pos;
                        pos.x = pos_str[0] - 'a' + 1;
                        pos.y = pos_str[1] - '0';
                        chess->addPiece(pos, p);
                    } else {
                        //
                    }
                } else if (operation == "-") {
                    Position pos;
                    std::string pos_str;
                    if (ss >> pos_str) {
                        pos.x = pos_str[0] - 'a' + 1;
                        pos.y = pos_str[1] - '0';
                        chess->removePiece(pos);
                    } else {
                        //
                    }
                } else if (operation == "=") {
                    std::string colour;
                    if (ss >> colour) {
                        if (colour == "black") {
                            chess->nextTurn();
                        } else if (colour == "white") {
                            chess->nextTurn();
                        } else {
                            //invalid
                        }
                    } else {
                        //
                    }
                } else {
                    // else invalid
                }
            }
        }
    }
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << chess->whitePlayerScore() << std::endl;
    std::cout << "Black: " << chess->blackPlayerScore() << std::endl;
    delete chess;
}


           /* from.x = from_str[0] - 'a' + 1;
            from.y = from_str[1] - '0';
            to.x = to_str[0] - 'a' + 1;
            to.y = to_str[1] - '0';
            // Move nextMove(from, to);
            Move nextMove;
            nextMove.from = from;
            nextMove.to = to;
            char promo;
            if (ss >> promo) {
                nextMove.isPromotion = true;
                nextMove.promotionType = promo;
            }
            chess->makeAMove(nextMove);*/