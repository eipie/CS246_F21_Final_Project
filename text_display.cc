#include "text_display.h"

Text_Display::Text_Display(ChessGame *g) {Game = g;}

void Text_Display::update() {

    for (int i = 8; i > 0; i--) {
        out << i << " ";
        for (int j = 0; j < 8; j++) {
            Position coordinate(j, i - 1);
            out << Game->getPieceCharAt(coordinate);
        }
        out << std::endl;
    }
    out << "" << std::endl;
    out << "  abcdefgh" << std::endl;
}
