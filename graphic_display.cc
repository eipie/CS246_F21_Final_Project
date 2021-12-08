#include "graphic_display.h"
#include "chessGame.h"
#include "window.h"
#include "position.h"

// assume t<=b l<=r
GraphicDisplay::GraphicDisplay( ChessGame *chessGame) 
    : subject{chessGame} {
    w = std::make_unique<Xwindow>((cols)*unitSize, (rows)*unitSize);
    drawBackground();
} 

void GraphicDisplay::update() {
    drawBackground();
    for (int x = 1; x <= 8; x++) {
        for (int y = 8; y >= 1; y--) {
            Position coordinate;
            coordinate.x = x;
            coordinate.y = y;
            char c = subject->getPieceCharAt(coordinate);
            if (c!=' ') {
                drawSquare(x,y,c);
            }
            
        }
    }
}

// Based on the input character, convert to colored squares and print on window
void GraphicDisplay::drawSquare(int i, int j, char filling) {
    int color = 3;
    if(filling==BORDER||filling==WHITE||filling==BLACK) {
            if(filling == BORDER) {
                color = Xwindow::Brown;
            } else if (filling==WHITE) {
                color = Xwindow::White;
            } else if (filling==BLACK) {
                color = Xwindow::Blue;
            }
            w->fillRectangle((j)*unitSize, (i)*unitSize, unitSize, unitSize, color);
    } else {
        std::string piece(1, filling);
        w->drawString((i)*unitSize+0.45*unitSize, (9-j)*unitSize+0.6*unitSize, piece);
    }

}

void GraphicDisplay::drawBackground() {
    for(int i = 0; i <= 9; i++) {
        for(int j=0; j<=9;j++) {
            if(i==0||i==9){
                drawSquare(i,j,BORDER);
            } else if(j==0||j==9) {
                drawSquare(i,j,BORDER);
            } else {
                Position coordinate;
                coordinate.x = j;
                coordinate.y = i;
                if ((coordinate.x % 2 ==0 && coordinate.y % 2 ==0)
                || (coordinate.x % 2 !=0 && coordinate.y % 2 !=0)) {
                    drawSquare(i,j,WHITE);
                } else {
                    drawSquare(i,j,BLACK);
                }
            }
        }
    }
}
