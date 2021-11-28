#include "text_display.h"

Text_Display::Text_Display(ChessGame *g) {Game = g;}

void Text_Display::update() {

    for (int i = 8; i >= 0; i--) {
        out << i;
        out << " ";
        out << std::endl;
    }
    

}