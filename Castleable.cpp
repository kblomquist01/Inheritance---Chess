#include "Castleable.h"
/****************************************************
    * MOVE
    * moves pieces from positionFrom to positionTo if valid
    ***************************************************/
bool Castleable::move(Piece board[], int positionFrom, int positionTo) {
    // do not move if a move was not indicated
    if (positionFrom == -1 || positionTo == -1)
        return false;
    assert(positionFrom >= 0 && positionFrom < 64);
    assert(positionTo >= 0 && positionTo < 64);


    // find the set of possible moves from our current location
    set <int> possiblePrevious = getPossibleMoves(board, positionFrom);

    // castling
    if (board[positionFrom] == 'K') {
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

    }

    // only move there is the suggested move is on the set of possible moves
    if (possiblePrevious.find(positionTo) != possiblePrevious.end())
    {
        board[positionTo] = board[positionFrom];
        board[positionFrom] = ' ';
        //when king or rook moves you cant castle
        if (board[positionTo].getType() == 'K' || board[positionTo].getType() == 'k' || board[positionTo].getType() == 'R' || board[positionTo].getType() == 'r') {
            Piece* piece = &board[positionTo];
            if (Castleable* castleablePiece = dynamic_cast<Castleable*>(piece)) {
                // The piece is indeed a Castleable
                castleablePiece->setCanCastle(false); // Set the canCastle attribute
            }
        }
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
/****************************************************
    * GET POSSIBLE MOVES
    * returns the moves the selected piece can make
    ***************************************************/
set<int> Castleable::getPossibleMoves(void* bord, int location){
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
    // KING
    //
    if (board[location] == 'K' && !board[location].getIsWhiteTurn())
    {
        RC moves[8] =
        {
           {-1,  1}, {0,  1}, {1,  1},
           {-1,  0},          {1,  0},
           {-1, -1}, {0, -1}, {1, -1}
        };
        for (int i = 0; i < 8; i++)
        {
            r = row + moves[i].row;
            c = col + moves[i].col;
            if (amBlack && isNotBlack(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
        }
        // what about castling?

        r = row;
        if (board[location] == 'K' && r == 7) {
            c = col + 1; // king side
            if (board[r * 8 + c] == ' ' && board[r * 8 + (c + 1)] == ' ' && board[r * 8 + (c + 2)] == 'R') {
                if ((board[r * 8 + (c + 2)]).getCanCastle() && board[row * 8 + col].getCanCastle()) {
                    if (testMoveOutCheck(bord, location, r * 8 + c + 1))
                        possible.insert(r * 8 + c + 1);
                }
            }
            c = col - 1; // queen side
            if (board[r * 8 + c] == ' ' && board[r * 8 + (c - 1)] == ' ' && board[r * 8 + (c - 3)] == 'R') {
                if ((board[r * 8 + (c - 3)]).getCanCastle() && board[row * 8 + col].getCanCastle()) {
                    if (testMoveOutCheck(bord, location, r * 8 + (c - 1)))
                        possible.insert(r * 8 + (c - 1));
                }
            }
        }

    }

    if (board[location] == 'k' && board[location].getIsWhiteTurn())
    {
        RC moves[8] =
        {
           {-1,  1}, {0,  1}, {1,  1},
           {-1,  0},          {1,  0},
           {-1, -1}, {0, -1}, {1, -1}
        };
        for (int i = 0; i < 8; i++)
        {
            r = row + moves[i].row;
            c = col + moves[i].col;
            if (amBlack && isNotBlack(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
        }
        // what about castling?

        r = row;

        if (board[location] == 'k' && r == 0) {
            c = col + 1; // king side
            if (board[r * 8 + c] == ' ' && board[r * 8 + (c + 1)] == ' ' && board[r * 8 + (c + 2)] == 'r') {
                if ((board[r * 8 + (c + 2)]).getCanCastle() && board[row * 8 + col].getCanCastle()) {
                    if (testMoveOutCheck(bord, location, r * 8 + c + 1))
                        possible.insert(r * 8 + c + 1);
                }
            }
            c = col - 1; // queen side
            if (board[r * 8 + c] == ' ' && board[r * 8 + (c - 1)] == ' ' && board[r * 8 + (c - 3)] == 'r') {
                if (board[r * 8 + (c - 3)].getCanCastle() && board[row * 8 + col].getCanCastle()) {
                    if (testMoveOutCheck(bord, location, r * 8 + (c - 1)))
                        possible.insert(r * 8 + (c - 1));
                }
            }
        }
    }

    //
    // ROOK
    //
    Rook* rook = (Rook*)bord;
    if (board[location] == 'R' && !board[location].getIsWhiteTurn())
    {
        RC moves[4] =
        {
                    {0,  1},
           {-1, 0},         {1, 0},
                    {0, -1}
        };
        for (int i = 0; i < 4; i++)
        {
            r = row + moves[i].row;
            c = col + moves[i].col;
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[r * 8 + c] == ' ')
            {
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
                r += moves[i].row;
                c += moves[i].col;
            }
            if (amBlack && isNotBlack(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
        }
    }
    if (board[location] == 'r' && board[location].getIsWhiteTurn())
    {
        RC moves[4] =
        {
                    {0,  1},
           {-1, 0},         {1, 0},
                    {0, -1}
        };
        for (int i = 0; i < 4; i++)
        {
            r = row + moves[i].row;
            c = col + moves[i].col;
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[r * 8 + c] == ' ')
            {
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
                r += moves[i].row;
                c += moves[i].col;
            }
            if (amBlack && isNotBlack(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
        }
    }
    return possible;
}
/****************************************************
    * SET CAN CASTLE
    * sets the canCastle variable
    ***************************************************/
void Castleable::setCanCastle(bool castle) {
    canCastle = castle;
}/****************************************************
    * GET ENPASSANT
    * gets the canCastle variable
    ***************************************************/
bool Castleable::getCanCastle() {
    return canCastle;
}