#ifndef GRAPHICDRAWER_H_
#define GRAPHICDRAWER_H_
#include "observer.h"
#include <memory>

class ChessGame;
class Xwindow;
class GraphicDisplay: public Observer {
    private:
    const char BORDER = '*';
    const char BLACK = '_';
    const char WHITE = ' ';
    ChessGame *subject;
    int t;
    int b;
    int l;
    int r;
    int cols;
    int rows;
    int unitSize = 10;
    void drawBackground();
    void drawSquare(int i, int j, char filling);
    std::unique_ptr<Xwindow> w;
    public:
    GraphicDisplay( ChessGame *chessGame, int t, int b, int l, int r);
    void update() override;
};

#endif