#ifndef OBSERVER_H
#define OBSERVER_H

class chessGame;
class Observer {

    public:
        virtual void update() = 0;
        virtual ~Observer() = default;

};

#endif
