#include "chessGame.h"
#include "board.h"
#include "move.h"
#include "position.h"
#include "player.h"
#include <string>
#include <iostream>

int main() {
    ChessGame *chess = new ChessGame();

    std::string command;
    while (getline(std::cin, command)) { //getline
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
            std::cin >> from_str;
            std::cin >> to_str;
            from.x = from_str[0] - 'a' + 1;
            from.y = from_str[1] - '0';
            to.x = to_str[0] - 'a' + 1;
            to.y = to_str[1] - '0';
            Move nextMove;
            nextMove.from = from;
            nextMove.to = to;
            char promo;
            if (std::cin >> promo) {
                nextMove.isPromotion = true;
                nextMove.promotionType = promo;
            }
            chess->makeAMove(nextMove);
        } else if (command == "setup") {
            std::string operation;
            std::cin >> operation;
            if (operation == "+") {
                char p; //piece
                std::string pos_str; //position
                std::cin >> p >> pos_str;
                Position pos;
                pos.x = pos_str[0] - 'a' + 1;
                pos.y = pos_str[1] - '0';
                chess->addPieces(pos, p);
            } else if (operation == "-") {
                Position pos;
                std::string pos_str:
                cin >> pos_str;
                pos.x = pos_str[0] - 'a' + 1;
                pos.y = pos_str[1] - '0';
                (chess->removePieces(pos);
            } else if (operation == "=") {
                std::string colour;
                std::cin >> colour;
                if (colour == "black") {
                    (chess->currentPlayer = 0;
                } else if (colour == "white") {
                    (chess->currentPlayer = 1;
                }
            } else if (operation == "done") {
                continue;
            }
        }
    }

    /*std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << wp.currentScore << std::endl;
    std::cout << "Black: " << bp.currentScore << std::endl;*/
    delete chess;
}