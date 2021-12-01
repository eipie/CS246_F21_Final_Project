#ifndef MOVE_H
#define MOVE_H
#include "position.h"
struct Move {
	// validMove is false if 
	// - user is computer
	// - or invalid move 
	bool validMove = true;
	Position from;
	Position to;
	bool kingSideCastle;
	bool queenSideCastle;
	bool enPassant;
	bool isPromotion;
	char promotionType;
};
#endif