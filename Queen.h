#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include "Piece.h"
#pragma once
class Queen : public Piece
{
public:
	Queen(char type) {
		this->setType(type);
	}

private:
};

