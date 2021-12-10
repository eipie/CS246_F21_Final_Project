#ifndef POSSIBLEMOVE_H
#define POSSIBLEMOVE_H
#include "position.h"
#include "chessPieces.h"
#include <memory>
struct PossibleMove {
    Position to;
    // ' ' if no capture
    char capture;
    bool kingSideCastle=false;
	bool queenSideCastle=false;
    Position rookFrom;
    Position rookTo;
	bool enPassant=false;
    Position enPassantLoc;
    bool isPromotion=false;
    char promotionType;
    
    PossibleMove(){}
    PossibleMove(const PossibleMove& pm) {
        to = pm.to;
        capture = pm.capture;
        kingSideCastle = pm.kingSideCastle;
        queenSideCastle = pm.queenSideCastle;
        rookFrom = pm.rookFrom;
        rookTo = pm.rookTo;
        enPassant = pm.enPassant;
        enPassantLoc = pm.enPassantLoc;
        promotionType = pm.promotionType;
    }
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
        rookFrom = pm.rookFrom;
        rookTo = pm.rookTo;
        enPassant = pm.enPassant;
        enPassantLoc = pm.enPassantLoc;
        promotionType = pm.promotionType;
        return *this;
    }
};

#endif