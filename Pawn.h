#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include "Piece.h"
#pragma once
class Pawn : public Piece
{
public:
	Pawn(char type) {
		this->setType(type);
		this->canBeEnpassant = false;
	}
	void setEnpassant(bool enpassant);
	bool getEnpassant();
	bool move(Piece board[], int positionFrom, int positionTo);
	set<int> getPossibleMoves(void* bord, int location) override;
private:
	bool canBeEnpassant;
};

