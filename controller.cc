#include "chessGame.h"
#include "board.h"
#include "position.h"
#include "player.h"
#include <string>
#include <iostream>

int main() {
    ChessGame *g = ChessGame();
    Player wp = Player(1, 0);    //creates white player
    Player bp = Player(-1, 0);   //creates blackc player
    std::vector<std::shared_ptr<Player>> players;
    //emplace players
    Board * b = new Board(players);
    std::string command;
    while (std::cin >> command) {
        if (command == "game") {
            //determine human-computer game
        } else if (command == "resign") {
            if (b->currentPlayer == 0) {
                cout << "Black Wins!" << endl;
            } else {
                cout << "White Wins!" << endl;
            }
        } else if (command == "move") {
            string from_str;
            string to_str;
            position from;
            position to;
            std::cin >> from_str;
            std::cin >> to_str;
            from.x = from_str[0];
            from.y = from_str[1];
            to.x = to_str[0];
            to.y = to_str[1] - '0';
            b->makeAMove(from, to);
            b->changePlayer();
        } else if (command == "setup") {
            string operation;
            cin >> operation;
            if (operation == "+") {
                char p; //piece
                string pos_str: //position
                cin >> p >> pos_str;
                pos.x = pos_str[0];
                pos.y = pos_str[1] - '0';
                b->addPieces(pos, p);
            } else if (operation == "-") {
                position pos;
                string pos_str: //position
                cin >> pos_str;
                pos.x = pos_str[0];
                pos.y = pos_str[1] - '0';
                b->removePieces(pos);
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