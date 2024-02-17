#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
class Rook;
using namespace std;
#pragma once
class Piece
{
public:
	Piece() {
		this->type = ' ';
		canCastle = true;
		canBeEnpassant = false;
		isWhiteTurn = true;
	}
	Piece(char type) {
		this->type = type;
		canCastle = true;
		canBeEnpassant = false;
		isWhiteTurn = true;
	}
	Piece(char type, bool castle) {
		this->type = type;
		canCastle = castle;
		canBeEnpassant = false;
		isWhiteTurn = true;
	}
	virtual ~Piece() = default;
	/***********************************************
	* Row Column
	* Simple row/column pair
	************************************************/
	struct RC
	{
		int row;
		int col;
	};

	void setType(char type) {
		this->type = type;
	}
	char getType() const {
		return type;
	}
	/****************************************************
	* IS  BLACK
	* Is the current location valid and the piece is black
	***************************************************/
	inline bool isBlack(const Piece* board, int row, int col)
	{
		// not white if we are off the board or if we are looking at a space
		if (row < 0 || row >= 8 || col < 0 || col >= 8)
			return false;
		Piece piece = board[row * 8 + col];

		return (piece >= Piece('A') && piece <= Piece('Z'));
	}
	/****************************************************
	* IS NOT BLACK
	* Is the current location valid and the piece is either
	* white (lowercase) or space
	***************************************************/
	inline bool isNotBlack(const Piece* board, int row, int col)
	{
		// not white if we are off the board or if we are looking at a space
		if (row < 0 || row >= 8 || col < 0 || col >= 8)
			return false;
		Piece piece = board[row * 8 + col];

		return piece == Piece() || (piece >= Piece('a') && piece <= Piece('z'));
	}
	/****************************************************
	* IS NOT WHITE
	* Is the current location valid and the piece is either
	* black (uppercase) or space
	 ***************************************************/
	inline bool isNotWhite(const Piece* board, int row, int col)
	{
		// not white if we are off the board or if we are looking at a space
		if (row < 0 || row >= 8 || col < 0 || col >= 8)
			return false;
		Piece piece = board[row * 8 + col];

		return piece == ' ' || (piece >= Piece('A') && piece <= Piece('Z'));
	}

	/****************************************************
	 * IS  WHITE
	 * Is the current location valid and the piece is white
	 ***************************************************/
	inline bool isWhite(const Piece* board, int row, int col)
	{
		// not white if we are off the board or if we are looking at a space
		if (row < 0 || row >= 8 || col < 0 || col >= 8)
			return false;
		Piece piece = board[row * 8 + col];

		return (piece >= Piece('a') && piece <= Piece('z'));
	}

	/*********************************************
	* MOVE
	* Execute one movement. Return TRUE if successful
	*********************************************/
	virtual bool move(Piece* board[], int positionFrom, int positionTo);

	bool operator==(const Piece& other) const {
		return this->type == other.type;
	}
	bool operator>=(const Piece& other) const {
		return this->type >= other.type;
	}
	bool operator<=(const Piece& other) const {
		return this->type <= other.type;
	}
	bool getCanCastle() const { return canCastle; };
	bool getCanBeEnpassant() const { return canBeEnpassant; };
	bool getInCheck(void* board);
	bool testMoveOutCheck(void* bord, int positionFrom, int positionTo);
	virtual set <int> getPossibleMoves(void* board, int location);
	set <int> Piece::getPossibleChecks(void* bord, int location);
	bool getIsWhiteTurn() { return isWhiteTurn; };
	void setIsWhiteTurn(bool turn) {isWhiteTurn = turn;};

private:
	char type;
	bool canCastle;
	bool canBeEnpassant;
	bool isWhiteTurn;
};
