#include "graphic_display.h"
#include "chessGame.h"
#include "window.h"
#include "position.h"

// assume t<=b l<=r
GraphicDisplay::GraphicDisplay( ChessGame *chessGame, int t, int b, int l, int r) 
    : subject{chessGame}, t{t}, b{b}, l{l}, r{r}, cols{r-l+1}, rows{b-t+1} {
    w = std::make_unique<Xwindow>(cols*unitSize, rows*unitSize);
    drawBackground();
} 

void GraphicDisplay::update() {
    for (int i = 8; i >= 1; i--) {
        for (int j = 1; j <= 8; j++) {
            Position coordinate;
            coordinate.x = j;
            coordinate.y = i;
            char c = subject->getPieceCharAt(coordinate);
            if (c!=' ') {
                drawSquare(i,j,c);
            }
        }
    }
}

// Based on the input character, convert to colored squares and print on window
void GraphicDisplay::drawSquare(int i, int j, char filling) {
    int color = 1;
    if(filling==BORDER||filling==WHITE||filling==BLACK) {
            if(filling == BORDER) {
                color = Xwindow::Brown;
            } else if (filling==WHITE) {
                color = Xwindow::White;
            } else if (filling==BLACK) {
                color = Xwindow::Black;
            }
            w->fillRectangle((j)*unitSize, (i)*unitSize, unitSize, unitSize, color);
    } else {
        std::string piece(1, filling);
        w->drawString((j)*unitSize, (i)*unitSize, piece);
    }

}

void GraphicDisplay::drawBackground() {
    for(int i = 0; i <= 9; i++) {
        for(int j=0; j<=9;j++) {
            if(i==0||i==9){
                drawSquare(i,j,BORDER);
            } else if(j==0||j==9) {
                drawSquare(i,0,BORDER);
            } else {
                Position coordinate;
                coordinate.x = j;
                coordinate.y = i;
                if ((coordinate.x % 2 ==0 && coordinate.y % 2 ==0)
                || (coordinate.x % 2 !=0 && coordinate.y % 2 !=0)) {
                    drawSquare(i,j,BLACK);
                } else {
                    drawSquare(i,j,WHITE);
                }
            }
        }
    }
}
