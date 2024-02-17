#pragma once
#include "Piece.h"
#include "Pawn.h"

class Castleable : public Piece
{
public:
	Castleable() : Piece() {
		this->setType(' ');
		this->canCastle = true;
	};
	Castleable(char type){
		this->setType(type);
		this->canCastle = true;
	};
	Castleable(char type, bool canCastle){
		this->setType(type);
		this->canCastle = canCastle;
	};

	void setCanCastle(bool castle);
	bool getCanCastle();
	bool move(Piece board[], int positionFrom, int positionTo);
	set<int> getPossibleMoves(void* bord, int location) override;
private:
	bool canCastle;
};

