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
		this->canEnpassant = false;
	}
	void setEnpassant(bool enpassant);

	/*virtual bool move(Piece* board, int positionFrom, int positionTo) override;*/
private:
	bool canEnpassant;
};

