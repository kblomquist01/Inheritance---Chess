#include "Pawn.h"

bool Pawn::move(Piece board[], int positionFrom, int positionTo) {
    // do not move if a move was not indicated
    if (positionFrom == -1 || positionTo == -1)
        return false;
    assert(positionFrom >= 0 && positionFrom < 64);
    assert(positionTo >= 0 && positionTo < 64);


    // find the set of possible moves from our current location
    set <int> possiblePrevious = getPossibleMoves(board, positionFrom);

    // Enpassant movement
    if (board[positionFrom] == 'P') {

        if (board[positionTo] == ' ' && board[positionTo + 8] == 'p') {
            if (possiblePrevious.find(positionTo) != possiblePrevious.end())
            {
                board[positionTo] = board[positionFrom];
                board[positionTo + 8] = Piece();
                board[positionFrom] = ' ';

                return true;
            }

        }
        if (positionTo / 8 == 0) {
            if (possiblePrevious.find(positionTo) != possiblePrevious.end())
            {
                board[positionTo] = Piece('Q');
                board[positionFrom] = ' ';

                return true;
            }

        }
    }
    else if (board[positionFrom] == 'p') {
        if (board[positionTo] == ' ' && board[positionTo - 8] == 'P') {
            if (possiblePrevious.find(positionTo) != possiblePrevious.end())
            {
                board[positionTo] = board[positionFrom];
                board[positionTo - 8] = Piece();
                board[positionFrom] = ' ';

                return true;
            }

        }
        if (positionTo / 8 == 7) {
            if (possiblePrevious.find(positionTo) != possiblePrevious.end())
            {
                board[positionTo] = Piece('q');
                board[positionFrom] = ' ';

                return true;
            }

        }
    }
    // castling
    /*if (board[positionFrom] == 'K') {
        if (positionTo == positionFrom + 2) {
            if (possiblePrevious.find(positionTo) != possiblePrevious.end())
            {
                board[positionTo] = board[positionFrom];
                board[positionTo + 1] = Piece();
                board[positionTo - 1] = Piece('R', false);
                board[positionFrom] = ' ';

                return true;
            }

        }
        if (positionTo == positionFrom - 2) {
            if (possiblePrevious.find(positionTo) != possiblePrevious.end())
            {
                board[positionTo] = board[positionFrom];
                board[positionTo - 2] = Piece();
                board[positionTo + 1] = Piece('R', false);
                board[positionFrom] = ' ';

                return true;
            }

        }
    }
    else if (board[positionFrom] == 'k') {
        if (positionTo == positionFrom + 2) {
            if (possiblePrevious.find(positionTo) != possiblePrevious.end())
            {
                board[positionTo] = board[positionFrom];
                board[positionTo + 1] = Piece();
                board[positionTo - 1] = Piece('r', false);
                board[positionFrom] = ' ';

                return true;
            }

        }
        if (positionTo == positionFrom - 2) {
            if (possiblePrevious.find(positionTo) != possiblePrevious.end())
            {
                board[positionTo] = board[positionFrom];
                board[positionTo - 2] = Piece();
                board[positionTo + 1] = Piece('r', false);
                board[positionFrom] = ' ';

                return true;
            }

        }

    }*/

    // only move there is the suggested move is on the set of possible moves
    if (possiblePrevious.find(positionTo) != possiblePrevious.end())
    {
        board[positionTo] = board[positionFrom];
        board[positionFrom] = ' ';
        //when king or rook moves you cant castle
        //if (board[positionTo].getType() == 'K' || board[positionTo].getType() == 'k' || board[positionTo].getType() == 'R' || board[positionTo].getType() == 'r') {
        //    Piece* piece = &board[positionTo];
        //    if (Castleable* castleablePiece = dynamic_cast<Castleable*>(piece)) {
        //        // The piece is indeed a Castleable
        //        castleablePiece->setCanCastle(false); // Set the canCastle attribute
        //    }
        //}
        // gets rid of enpassantable features of pawns each move

        for (int row = 4; row >= 3; row--) {
            for (int col = 0; col < 8; col++) {
                Piece* piece = &board[row * 8 + col];
                if (Pawn* pawnPiece = dynamic_cast<Pawn*>(piece)) {
                    // The piece is indeed a Castleable
                    pawnPiece->setEnpassant(false); // Set the canCastle attribute
                }

            }
        }

        return true;
    }
    return false;
}

set<int> Pawn::getPossibleMoves(void* bord, int location) {
    set <int> possible;
    Piece* board = (Piece*)bord;
    // return the empty set if there simply are no possible moves
    if (location < 0 || location >= 64 || board[location] == ' ')
        return possible;
    int row = location / 8;  // current location row
    int col = location % 8;  // current location column
    int r;                   // the row we are checking
    int c;                   // the column we are checking
    bool amBlack = isBlack((Piece*)board, row, col);

    //
   // PAWN
   //
    if (board[location] == 'P' && !(board[location].getIsWhiteTurn()))
    {
        c = col;
        r = row - 2;
        if (row == 6 && board[r * 8 + c] == ' ')
            if (testMoveOutCheck(bord, location, r * 8 + c))
                possible.insert(r * 8 + c);  // forward two blank spaces

        r = row - 1;
        if (r >= 0 && board[r * 8 + c] == ' ')
            if (testMoveOutCheck(bord, location, r * 8 + c))
                possible.insert(r * 8 + c);  // forward one black space
        c = col - 1;
        if (isWhite(board, r, c))
            if (testMoveOutCheck(bord, location, r * 8 + c))
                possible.insert(r * 8 + c);    // attack left
        c = col + 1;
        if (isWhite(board, r, c))
            if (testMoveOutCheck(bord, location, r * 8 + c))
                possible.insert(r * 8 + c);    // attack right
        c = col + 1;
        r = row;
        if (r == 3) {
            if (isWhite(board, r, c) && board[(r * 8 + c)].getCanBeEnpassant())
                if (testMoveOutCheck(bord, location, r * 8 - 8 + c))
                    possible.insert(r * 8 - 8 + c); // enpassant right

            c = col - 1;
            r = row;
            if (isWhite(board, r, c) && board[(r * 8 + c)].getCanBeEnpassant())
                if (testMoveOutCheck(bord, location, r * 8 - 8 + c))
                    possible.insert(r * 8 - 8 + c);    // enpassant left

        }

        // what about en-passant and pawn promotion
    }
    if (board[location] == 'p' && (board[location].getIsWhiteTurn()))
    {
        c = col;
        r = row + 2;
        if (row == 1 && board[r * 8 + c] == ' ')
            if (testMoveOutCheck(bord, location, r * 8 + c))
                possible.insert(r * 8 + c);  // forward two blank spaces
        r = row + 1;
        if (r < 8 && board[r * 8 + c] == ' ')
            if (testMoveOutCheck(bord, location, r * 8 + c))
                possible.insert(r * 8 + c);    // forward one blank space
        c = col - 1;
        if (isBlack(board, r, c))
            if (testMoveOutCheck(bord, location, r * 8 + c))
                possible.insert(r * 8 + c);      // attack left
        c = col + 1;
        if (isBlack(board, r, c))
            if (testMoveOutCheck(bord, location, r * 8 + c))
                possible.insert(r * 8 + c);      // attack right
        // what about en-passant and pawn promotion
        c = col + 1;
        r = row;
        if (r == 4) {
            if (isBlack(board, r, c) && (board[r * 8 + c]).getCanBeEnpassant())
                if (testMoveOutCheck(bord, location, r * 8 + 8 + c))
                    possible.insert(r * 8 + 8 + c);    // enpassant right

            c = col - 1;
            if (isBlack(board, r, c) && (board[r * 8 + c]).getCanBeEnpassant())
                if (testMoveOutCheck(bord, location, r * 8 + 8 + c))
                    possible.insert(r * 8 + 8 + c);    // enpassant left

        }

    }
    return possible;
}

void Pawn :: setEnpassant(bool enpassant) {
    canBeEnpassant = enpassant;
}
bool Pawn::getEnpassant() {
    return canBeEnpassant;
}

