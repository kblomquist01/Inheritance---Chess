#pragma once
class testMovement
{
public:
	void run() {
		setPositionFromValid();
		setPositionFromOutOfBounds();
		setPositionToChar();
		setPostitionFromBorder();

		setPositionToValid();
		setPositionToOutOfBounds();
		setPositionToBorder();
		
		setMoveTypeEmpty();
		setMoveTypePawn();
		setMoveTypeTower();
		setMoveTypeBishop();
		setMoveTypeKnight();
		setMoveTypeQueen();
		setMoveTypeKing();
		setMoveTypeShortCastle();
		setMoveTypeLongCastle();
		setMoveTypeEnPassant();
		setMoveTypePromotion();

		getPositionFromValid();
		getPositionFromInvalid();
		getPositionFromBorder();

		getPositionToValid();
		getPositionToInvalid();
		getPositionToBorder();

		getMoveTypePawn();
		getMoveTypeTower();
		getMoveTypeBishop();
		getMoveTypeKnight();
		getMoveTypeQueen();
		getMoveTypeKing();

	}
private:
	void setPositionFromValid();
	void setPositionFromOutOfBounds();
	void setPositionFromChar();
	void setPostitionFromBorder();

	void setPositionToValid();
	void setPositionToOutOfBounds();
	void setPositionToChar();
	void setPositionToBorder();

	void setMoveTypeEmpty();
	void setMoveTypePawn();
	void setMoveTypeTower();
	void setMoveTypeBishop();
	void setMoveTypeKnight();
	void setMoveTypeQueen();
	void setMoveTypeKing();
	void setMoveTypeInvalid();
	void setMoveTypeShortCastle();
	void setMoveTypeLongCastle();
	void setMoveTypeEnPassant();
	void setMoveTypePromotion();

	int getPositionFromValid();
	int getPositionFromInvalid();
	int getPositionFromBorder();

	int getPositionToValid();
	int getPositionToInvalid();
	int getPositionToBorder();

	char getMoveTypePawn();
	char getMoveTypeTower();
	char getMoveTypeBishop();
	char getMoveTypeKnight();
	char getMoveTypeQueen();
	char getMoveTypeKing();
};