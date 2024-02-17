#pragma once
#include "Piece.h"
#include "Pawn.h"
#include "Castleable.h"
#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for draw*

class Board
{
public:
	Board() {
        isWhiteTurn = true;
	}
    void callBack(Interface* pUI);
    void draw(const Interface& ui, const set <int>& possible);
    Piece** getBoard() { return board; };
private:
    Piece* board[64] = {
        new Castleable('r'), new Piece('n'), new Piece('b'), new Piece('q'), new Castleable('k'),  new Piece('b'), new Piece('n'),  new Castleable('r'),
        new Pawn('p'),       new Pawn('p'),  new Pawn('p'),  new Pawn('p'),  new Pawn('p'),        new Pawn('p'),  new Pawn('p'),   new Pawn('p'),
        new Piece(' '),      new Piece(' '), new Piece(' '), new Piece(' '), new Piece(' '),       new Piece(' '), new Piece(' '),  new Piece(' '),
        new Piece(' '),      new Piece(' '), new Piece(' '), new Piece(' '), new Piece(' '),       new Piece(' '), new Piece(' '),  new Piece(' '),
        new Piece(' '),      new Piece(' '), new Piece(' '), new Piece(' '), new Piece(' '),       new Piece(' '), new Piece(' '),  new Piece(' '),
        new Piece(' '),      new Piece(' '), new Piece(' '), new Piece(' '), new Piece(' '),       new Piece(' '), new Piece(' '),  new Piece(' '),
        new Pawn('P'),       new Pawn('P'),  new Pawn('P'),  new Pawn('P'),  new Pawn('P'),        new Pawn('P'),  new Pawn('P'),   new Pawn('P'),
        new Castleable('R'), new Piece('N'), new Piece('B'), new Piece('Q'), new Castleable('K'),  new Piece('B'), new Piece('N'),  new Castleable('R')
    };
    bool isWhiteTurn;
};

