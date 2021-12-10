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
    const int cols=10;
    const int rows=10;
    int unitSize = 35;
    void drawBackground();
    void drawSquare(int i, int j, char filling);
    std::shared_ptr<Xwindow> w;
    
    public:
    GraphicDisplay( ChessGame *chessGame);
    void update() override;
};

#endif