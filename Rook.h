#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include "Piece.h"
#pragma once
class Rook : public Piece
{
public:
	Rook(char type) {
		this->setType(type);
		this->canCastle = true;
	}
	Rook(char type, bool castle) {
		this->setType(type);
		this->canCastle = castle;
	}
	void setCanCastle(bool castle);
	//virtual bool getCanCastle() const override { return canCastle; };
	bool getCanCastle() const;
private:
	bool canCastle;
};

