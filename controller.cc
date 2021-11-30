#include "chessGame.h"
#include "board.h"
#include "move.h"
#include "position.h"
#include "player.h"
#include <string>
#include <iostream>
#include <sstream>

int main() {
    ChessGame *chess = new ChessGame();

    std::string line;
    while (std::getline(std::cin, line)) {
        std::string command;
        std::stringstream ss(line);
        ss >> command;
        if (command == "game") {
            //determine human-computer game
        } else if (command == "resign") {
            //if ((chess->board).currentPlayer == 0) {
             /*   std::cout << "Black Wins!" << std::endl;
            } else {
                std::cout << "White Wins!" << std::endl;
            }*/
            break;
        } else if (command == "move") {
            std::string from_str;
            std::string to_str;
            Position from;
            Position to;
            ss >> from_str >> to_str;
            from.x = from_str[0] - 'a' + 1;
            from.y = from_str[1] - '0';
            to.x = to_str[0] - 'a' + 1;
            to.y = to_str[1] - '0';
            Move nextMove;
            nextMove.from = from;
            nextMove.to = to;
            char promo;
            if (ss >> promo) {
                nextMove.isPromotion = true;
                nextMove.promotionType = promo;
            }
            chess->makeAMove(nextMove);
        } else if (command == "setup") { // check if the game has started, then allow setup;
            // while loop until the user type done, then call isboardvalid
            std::string operation;
            ss >> operation;
            while (true) {
                if (operation != "done") {
                    break;
                } else if (operation == "+") {
                    char p;
                    std::string pos_str;
                    ss >> p >> pos_str;
                    Position pos;
                    pos.x = pos_str[0] - 'a' + 1;
                    pos.y = pos_str[1] - '0';
                    chess->addPiece(pos, p);
                } else if (operation == "-") {
                    Position pos;
                    std::string pos_str;
                    ss >> pos_str;
                    pos.x = pos_str[0] - 'a' + 1;
                    pos.y = pos_str[1] - '0';
                    chess->removePiece(pos);
                } else if (operation == "=") {
                    std::string colour;
                    ss >> colour;
                    if (colour == "black") {
                        //chess->changePlayer();
                    } else if (colour == "white") {
                        //chess->changePlayer();
                    }
                }
                // else invalid
            }
        }
    }

    /*std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << wp.currentScore << std::endl;
    std::cout << "Black: " << bp.currentScore << std::endl;*/
    delete chess;
}