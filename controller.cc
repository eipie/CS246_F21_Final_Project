#include "chessGame.h"
#include "move.h"
#include "position.h"
#include <string>
#include <iostream>
#include <sstream>
#include <memory>

int main() {
    std::unique_ptr<ChessGame>chess;
    std::string line;
    bool gameHasStarted = false;
    bool isFirstTime = true;
    bool inSetUp = false;
    bool isSetUpAllowed=true;
    while (std::getline(std::cin, line)) {
        std::string command;
        std::stringstream ss(line);
        ss >> command;
        std::string moveResult;
        if (!inSetUp) {
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
                        std::cout << "The input for white player is not valid" << std::endl;
                        continue;
                    }
                } else {
                    std::cout << "No white player is given" << std::endl;
                    continue;
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
                        std::cout << "The input for black player is not valid" << std::endl;
                        continue;
                    }
                } else {
                    std::cout << "No black player is given" << std::endl;
                    continue;
                }
                chess = std::make_unique<ChessGame>(isHuman1, isHuman2, levels);
                gameHasStarted = true;
            } else if (command == "resign") {
                std::cout << chess->resign() << std::endl;
                break;
            } else if (command == "move") {
                isSetUpAllowed=false;
                std::string from_str;
                std::string to_str;
                Position from;
                Position to;
                Move nextMove;
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
                if(chess.get()->roundEnds) {
                    isSetUpAllowed=true;
                }
                std::cout << moveResult << std::endl;
            } else if (command == "setup") {
                if (gameHasStarted&&isSetUpAllowed) {
                    inSetUp = true;
                    if (isFirstTime) {
                        chess->makeBlankBoard();
                    }
                    chess->render();
                    continue;
                } else if (!gameHasStarted){
                    std::cout << "Game has not started yet, can't enter setup!" << std::endl;
                } else {
                    std::cout << "Game is still running, can't enter setup!" << std::endl;
                }
            }
        } else {
            if (command == "done") {
                if (chess->isBoardSetupValid()) {
                    inSetUp = false;
                    std::cout<<"Successfully exited setup mode!"<<std::endl;
                } else {
                    std::cout << "Cannot leave set up mode yet" << std::endl;
                }
            } else if (command == "+") {
                char p;
                std::string pos_str;
                if (ss >> p >> pos_str) {
                Position pos;
                pos.x = pos_str[0] - 'a' + 1;
                pos.y = pos_str[1] - '0';
                chess->addPiece(pos, p);
                chess->render();
                } else {
                    std::cout << "Error, the command should be in the form '+ k e1'" << std::endl;
                }  
            } else if (command == "-") {
                std::string pos_str;
                if (ss >> pos_str) {
                    Position pos;
                    pos.x = pos_str[0] - 'a' + 1;
                    pos.y = pos_str[1] - '0';
                    chess->removePiece(pos);
                    chess->render();
                    } else {
                        std::cout << "Error, the command should be in the form '- e1'" << std::endl;
                    }
            } else if (command == "=") {
                std::string colour;
                if (ss >> colour) {
                    if (colour == "black") {
                        chess->setCurrentPlayer(1);
                    } else if (colour == "white") {
                        chess->setCurrentPlayer(0);
                    } else {
                        std::cout << "Next player should be black or white" << std::endl;
                    }
                } else {
                    std::cout << "Error, the command should be in the form '= colour'" << std::endl;
                }
            } else {
                std::cout << "Error, the given input is not valid" << std::endl;
            }
        } 
    }
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << chess->whitePlayerScore() << std::endl;
    std::cout << "Black: " << chess->blackPlayerScore() << std::endl;
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







            /*} else if (command == "setup") { 
            if (isFirstTime) {
                std::vector<int> change = {1, 2, 3, 4, 5, 6, 7, 8};
                for(int x:change) {
                    for(int y:change) {
                        Position p;
                        p.x=x;
                        p.y=y;
                        chess->removePiece(p);
                    }
                }
            }
            if (!gameHasStarted) {  // check if the game has started, then allow setup;
                std::cout << "Game has not started yet" << std::endl;
            } else {
                std::cout << "Game started" << std::endl;
            // while loop until the user type done, then call isboardvalid
                std::string operation;
                std::string moveResult;
                while (ss >> operation) {
                    std::cout << "operation ready" << operation << std::endl;
                        if (operation == "done") {
                            //if (chess->isBoardSetupValid()) {
                                break;
                            //} else {
                                // cout << "Cannot leave set up mode yet" << endl;
                            //    continue;
                        //}
                        } else if (operation == "+") {
                            char p;
                            std::string pos_str;
                            if (ss >> p >> pos_str) {
                                Position pos;
                                pos.x = pos_str[0] - 'a' + 1;
                                pos.y = pos_str[1] - '0';
                                chess->addPiece(pos, p);
                                chess->render();
                            } else {
                                //
                            }
                        } else if (operation == "-") {
                            std::string pos_str;
                            if (ss >> pos_str) {
                                Position pos;
                                pos.x = pos_str[0] - 'a' + 1;
                                pos.y = pos_str[1] - '0';
                                chess->removePiece(pos);
                                chess->render();
                            } else {
                                //
                            }
                        } else if (operation == "=") {
                            std::string colour;
                            if (ss >> colour) {
                                if (colour == "black" || colour == "white") {
                                    chess->nextTurn();
                                } else {
                                    //invalid
                                }
                            } else {
                                //
                            }
                        } else {
                            //invalid
                        }
                }
                isFirstTime = false;
            }
        }*/