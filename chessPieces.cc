#include "chessPieces.h"
#include "position.h"
ChessPieces::ChessPieces(Position p, int identifier, bool isFirstMove) 
    : pos{p}, ownerIdentifier{identifier}, isFirstMove{isFirstMove} {}