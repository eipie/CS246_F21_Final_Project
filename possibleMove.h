#include "position.h"
#include "chessPieces.h"
#include <memory>
struct PossibleMove {
    // Position from;
    Position to;
    // ' ' if no capture
    char capture;
    // ChessPieces* capture;
};


// white: pawn e1  ->  vector<possiblemove>
// for loop Board cpyboard  -> Board cpyboard   g3
//
// currentplayer pieces black: 
// for loop pieces -> findPossibleMove() ->  vector<possiblemove>
// possition to == g3 