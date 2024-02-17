#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include "Piece.h"
#pragma once
class Bishop : public Piece
{
public:
	Bishop(char type) {
		this->setType(type);
	}

private:
};

