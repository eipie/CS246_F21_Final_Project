#ifndef MOVE_H
#define MOVE_H
#include "position.h"
struct Move {
	Position from;
	Position to;
	bool kingSideCastle;
	bool queenSideCastle;
	bool enPassant;
	bool isPromotion;
	char promotionType;
};
#endif