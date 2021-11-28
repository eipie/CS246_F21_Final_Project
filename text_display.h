#ifndef TDISPLAY_H
#define TDISPLAY_H
#include "observer.h"
#include "chessGame.h"
#include <iostream>

class Text_Display: public Observer {

    private:
        ChessGame *Game;
        std::ostream &out = std::cout;

    public:
        Text_Display(ChessGame *g);
        void update() override;
};


#endif