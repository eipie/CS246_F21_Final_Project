#include "chessGame.h"
#include "board.h"
#include "move.h"
#include "position.h"
#include "player.h"
#include <string>
#include <iostream>

int main() {
    ChessGame *chess = ChessGame();

    std::string command;
    while (std::cin >> command) {
        if (command == "game") {
            //determine human-computer game
        } else if (command == "resign") {
            if ((chess->board).currentPlayer == 0) {
                cout << "Black Wins!" << endl;
            } else {
                cout << "White Wins!" << endl;
            }
            break;
        } else if (command == "move") {
            string from_str;
            string to_str;
            position from;
            position to;
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
                isPromotion = true;
                promotionType = promo;
            }
            chess->makeAMove(nextMove);
        } else if (command == "setup") {
            string operation;
            cin >> operation;
            if (operation == "+") {
                char p; //piece
                string pos_str: //position
                cin >> p >> pos_str;
                pos.x = pos_str[0] - 'a' + 1;
                pos.y = pos_str[1] - '0';
                (chess->board).addPieces(pos, p);
            } else if (operation == "-") {
                position pos;
                string pos_str:
                cin >> pos_str;
                pos.x = pos_str[0] - 'a' + 1;
                pos.y = pos_str[1] - '0';
                (chess->board).removePieces(pos);
            } else if (operation == "=") {
                string colour;
                cin >> colour;
                if (colour == "black") {
                    currentPlayer = 0;
                } else if (colour == "white") {
                    currentPlayer = 1;
                }
            } else if (operation == "done") {
                continue;
            }
        }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << wp.currentScore << endl;
    cout << "Black: " << bp.currentScore << endl;    
    delete b;
}