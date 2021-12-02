#include "position.h"
#include "chessPieces.h"
#include <memory>
struct PossibleMove {
    // Position from;
    Position to;
    // ' ' if no capture
    char capture;
    // ChessPieces* capture;
    bool kingSideCastle;
	bool queenSideCastle;
	bool enPassant;
    Position enPassantLoc;
    bool isPromotion;
    char promotionType;
    bool operator==(PossibleMove pm) const{
        return (pm.to == to);
    }
    bool operator<(const PossibleMove& pm) const { 
        return to < pm.to; 
    }
    PossibleMove& operator=(const PossibleMove& pm)
    {
        to = pm.to;
        capture = pm.capture;
        kingSideCastle = pm.kingSideCastle;
        queenSideCastle = pm.queenSideCastle;
        enPassant = pm.enPassant;
        enPassantLoc = pm.enPassantLoc;
        promotionType = pm.promotionType;
        return *this;
    }
};


// white: pawn e1  ->  vector<possiblemove>
// for loop Board cpyboard  -> Board cpyboard   g3
//
// currentplayer pieces black: 
// for loop pieces -> findPossibleMove() ->  vector<possiblemove>
// possition to == g3 