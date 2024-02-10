#include "testMovement.h"
#include "movement.h"
#include <cassert>

// valid set should override previous position with an int
void testMovement::setPositionFromValid() {
	//SETUP
	Movement move;
	move.positionFrom = 0;

	//EXERCISE
	move.setPositionFrom(5);

	//VERIFY
	assert(!(move.positionFrom < 0));
	assert(!(move.positionFrom >= 64));
	assert(move.positionFrom == 5);
	//TEARDOWN
}
// valid set should not override previous position with a out of bounds
void testMovement::setPositionFromOutOfBounds() {
	//SETUP
	Movement move;
	move.postitionFrom = 5;

	//EXERCISE
	move.setPositionFrom(-1);

	//VERIFY
	assert(!(move.positionFrom < 0));
	assert(!(move.positionFrom >= 64));
	assert(move.positionFrom == 5);
	//TEARDOWN
}
// invalid set should not override previous position with a char
void testMovement::setPositionFromChar() {
	//SETUP
	Movement move;
	move.postitionFrom = 5;

	//EXERCISE
	move.setPositionFrom("a");

	//VERIFY
	assert(!(move.positionFrom < 0));
	assert(!(move.positionFrom >= 64));
	assert(move.positionFrom == 5);
	//TEARDOWN
}
void testMovement::setPostitionFromBorder() {
	//SETUP
	Movement move;
	move.postitionFrom = 5;

	//EXERCISE
	move.setPositionFrom(0);

	//VERIFY
	assert(!(move.positionFrom < 0));
	assert(!(move.positionFrom >= 64));
	assert(move.positionFrom == 0);
	//TEARDOWN
}

void testMovement::setPositionToValid() {
	//SETUP
	Movement move;
	move.positionTo = 0;

	//EXERCISE
	move.setPositionTo(5);

		//VERIFY
		assert(!(move.positionTo < 0));
	assert(!(move.positionTo >= 64));
	assert(move.positionTo == 5);
	//TEARDOWN
}
void testMovement::setPositionToOutOfBounds() {
	//SETUP
	Movement move;
	move.postitionTo = 5;

	//EXERCISE
	move.setPositionTo(-1);

	//VERIFY
	assert(!(positionTo < 0));
	assert(!(move.positionTo >= 64));
	assert(move.positionTo == 5);
	//TEARDOWN
}
void testMovement::setPositionToChar() {
	//SETUP
	Movement move;
	move.postitionTo = 5;

	//EXERCISE
	move.setPositionTo("a");

	//VERIFY
	assert(!(move.positionTo < 0));
	assert(!(move.positionTo >= 64));
	assert(move.positionTo == 5);
	//TEARDOWN
}
void testMovement::setPositionToBorder() {
	//SETUP
	Movement move;
	move.postitionTo = 5;

	//EXERCISE
	move.setPositionTo(0);

	//VERIFY
	assert(!(move.positionTo < 0));
	assert(!(move.positionTo >= 64));
	assert(move.positionTo == 0);
	//TEARDOWN
}

void testMovement::setMoveTypeEmpty() {
	//SETUP
	Movement move;
	move.moveType = 'a';
	//EXERCISE
	move.setMoveType('');
	//VERIFY
	assert(move.moveType != 'a');
	assert(move.moveType == '');
	//TEARDOWN
}
void testMovement::setMoveTypePawn() {
	//SETUP
	Movement move;
	move.moveType = 'a';
	//EXERCISE
	move.setMoveType('p');
	//VERIFY
	assert(move.moveType != 'a');
	assert(move.moveType == 'p');
	//TEARDOWN
}
void testMovement::setMoveTypeTower() {
	//SETUP
	Movement move;
	move.moveType = 'a';
	//EXERCISE
	move.setMoveType('r');
	//VERIFY
	assert(move.moveType != 'a');
	assert(move.moveType == 'r');
	//TEARDOWN
}
void testMovement::setMoveTypeBishop() {
	//SETUP
	Movement move;
	move.moveType = 'a';
	//EXERCISE
	move.setMoveType('b');
	//VERIFY
	assert(move.moveType != 'a');
	assert(move.moveType == 'b');
	//TEARDOWN
}
void testMovement::setMoveTypeKnight() {
	//SETUP
	Movement move;
	move.moveType = 'a';
	//EXERCISE
	move.setMoveType('n');
	//VERIFY
	assert(move.moveType != 'a');
	assert(move.moveType == 'n');
	//TEARDOWN
}
void testMovement::setMoveTypeQueen() {
	//SETUP
	Movement move;
	move.moveType = 'a';
	//EXERCISE
	move.setMoveType('q');
	//VERIFY
	assert(move.moveType != 'a');
	assert(move.moveType == 'q');
	//TEARDOWN
}
void testMovement::setMoveTypeKing() {
	//SETUP
	Movement move;
	move.moveType = 'a';
	//EXERCISE
	move.setMoveType('k');
	//VERIFY
	assert(move.moveType != 'a');
	assert(move.moveType == 'k');
	//TEARDOWN
}

void testMovement::setMoveTypeInvalid() {
	//SETUP
	Movement move;
	move.moveType = 'k';
	//EXERCISE
	move.setMoveType('i');
	//VERIFY
	assert(move.moveType != 'i');
	assert(move.moveType == 'k');
	//TEARDOWN
}
void testMovement::setMoveTypeShortCastle() {
	//SETUP
	Movement move;
	move.moveType = 'k';
	//EXERCISE
	move.setMoveType('c');
	//VERIFY
	assert(move.moveType != 'k');
	assert(move.moveType == 'c');
	//TEARDOWN
}
void testMovement::setMoveTypeLongCastle() {
	//SETUP
	Movement move;
	move.moveType = 'k';
	//EXERCISE
	move.setMoveType('C');
	//VERIFY
	assert(move.moveType != 'k');
	assert(move.moveType == 'C');
	//TEARDOWN
}
void testMovement::setMoveTypeEnPassant() {
	//SETUP
	Movement move;
	move.moveType = 'k';
	//EXERCISE
	move.setMoveType('E');
	//VERIFY
	assert(move.moveType != 'k');
	assert(move.moveType == 'E');
	//TEARDOWN
}
void testMovement::setMoveTypePromotion() {
	//SETUP
	Movement move;
	move.moveType = 'k';
	//EXERCISE
	move.setMoveType('Q');
	//VERIFY
	assert(move.moveType != 'k');
	assert(move.moveType == 'Q');
	//TEARDOWN
}


int testMovement::getPositionFromValid() {
	//SETUP
	Movement move;
	move.positionFrom = 5;

	//EXERCISE
	test =move.getPositionFrom();

	//VERIFY
	assert(!(test < 0));
	assert(!(test >= 64));
	assert(test == 5);
	//TEARDOWN
}
int testMovement::getPositionFromInvalid() {
	//SETUP
	Movement move;
	move.positionFrom = 64;

	//EXERCISE
	test = move.getPositionFrom();

	//VERIFY
	assert(!(test < 0));
	assert(!(test >= 64));
	assert(test == -1);
	//TEARDOWN
}
int testMovement::getPositionFromBorder() {
	//SETUP
	Movement move;
	move.positionFrom = 0;

	//EXERCISE
	test = move.getPositionFrom();

	//VERIFY
	assert(!(test < 0));
	assert(!(test >= 64));
	assert(test == 0);
	//TEARDOWN
}

int testMovement::getPositionToValid() {
	//SETUP
	Movement move;
	move.positionTo = 5;

	//EXERCISE
	test = move.getPositionTo();

	//VERIFY
	assert(!(test < 0));
	assert(!(test >= 64));
	assert(test == 5);
	//TEARDOWN
}
int testMovement::getPositionToInvalid() {
	//SETUP
	Movement move;
	move.positionTo = 64;

	//EXERCISE
	test = move.getPositionTo();

	//VERIFY
	assert(!(test < 0));
	assert(!(test >= 64));
	assert(test == -1);
	//TEARDOWN
}
int testMovement::getPositionToBorder() {
	//SETUP
	Movement move;
	move.positionTo = 0;

	//EXERCISE
	test = move.getPositionTo();

	//VERIFY
	assert(!(test < 0));
	assert(!(test >= 64));
	assert(test == 0);
	//TEARDOWN
}

void testMovement::getMoveTypeEmpty() {
	//SETUP
	Movement move;
	move.moveType = '';
	//EXERCISE
	test = move.getMoveType('');
	//VERIFY
	assert(test == '');
	//TEARDOWN
}

char testMovement::getMoveTypePawn() {
	//SETUP
	Movement move;
	move.moveType = 'p';
	//EXERCISE
	test = move.getMoveType();
	//VERIFY
	assert(test == 'p');
	//TEARDOWN
}
char testMovement::getMoveTypeTower() {
	//SETUP
	Movement move;
	move.moveType = 'r';
	//EXERCISE
	test = move.getMoveType();
	//VERIFY
	assert(test == 'r');
	//TEARDOWN
}
char testMovement::getMoveTypeBishop() {
	//SETUP
	Movement move;
	move.moveType = 'b';
	//EXERCISE
	test = move.getMoveType();
	//VERIFY
	assert(test == 'b');
	//TEARDOWN
}
char testMovement::getMoveTypeKnight() {
	//SETUP
	Movement move;
	move.moveType = 'n';
	//EXERCISE
	test = move.getMoveType();
	//VERIFY
	assert(test == 'n');
	//TEARDOWN
}
char testMovement::getMoveTypeQueen() {
	//SETUP
	Movement move;
	move.moveType = 'q';
	//EXERCISE
	test = move.getMoveType();
	//VERIFY
	assert(test == 'q');
	//TEARDOWN
}
char testMovement::getMoveTypeKing() {
	//SETUP
	Movement move;
	move.moveType = 'k';
	//EXERCISE
	test = move.getMoveType();
	//VERIFY
	assert(test == 'k');
	//TEARDOWN
}
void testMovement::getMoveTypeShortCastle() {
	//SETUP
	Movement move;
	move.moveType = 'c';
	//EXERCISE
	test = move.getMoveType('c');
	//VERIFY
	assert(test == 'c');
	//TEARDOWN
}
void testMovement::getMoveTypeLongCastle() {
	//SETUP
	Movement move;
	move.moveType = 'C';
	//EXERCISE
	move.setMoveType('C');
	//VERIFY
	assert(test == 'C');
	//TEARDOWN
}
void testMovement::getMoveTypeEnPassant() {
	//SETUP
	Movement move;
	move.moveType = 'E';
	//EXERCISE
	move.setMoveType('E');
	//VERIFY
	assert(test == 'E');
	//TEARDOWN
}
void testMovement::getMoveTypePromotion() {
	//SETUP
	Movement move;
	move.moveType = 'Q';
	//EXERCISE
	move.setMoveType('Q');
	//VERIFY
	assert(test == 'Q');
	//TEARDOWN
}