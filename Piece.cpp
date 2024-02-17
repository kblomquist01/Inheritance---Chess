#include "Piece.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"


bool Piece::move(void* bord, int positionFrom, int positionTo)
{
    Piece* board = (Piece*)bord;
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
                board[positionTo] = Queen('Q');
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
                board[positionTo] = Queen('q');
                board[positionFrom] = ' ';

                return true;
            }
            
        }
    }
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
            board[positionTo].canCastle = false;
        }
        // gets rid of enpassantable features of pawns each move

        for (int row = 4; row >= 3; row--) {
            for (int col = 0; col < 8; col++) {
                board[row * 8 + col].canBeEnpassant = false;
            }
        }

        // makes the paw enpassantable for the next turn
        if (board[positionTo].getType() == 'P' || board[positionTo].getType() == 'p') {
            if (positionTo == positionFrom + (8 * 2) || positionTo == positionFrom - (8 * 2)) {
                board[positionTo].canBeEnpassant = true;
            }
        }

        return true;
    }


    return false;

}

set <int> Piece::getPossibleMoves(const void* bord, int location) {
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
    if (board[location] == 'P')
    {
        c = col;
        r = row - 2;
        if (row == 6 && board[r * 8 + c] == ' ')
            possible.insert(r * 8 + c);  // forward two blank spaces
        r = row - 1;
        if (r >= 0 && board[r * 8 + c] == ' ')
            possible.insert(r * 8 + c);  // forward one black space
        c = col - 1;
        if (isWhite(board, r, c))
            possible.insert(r * 8 + c);    // attack left
        c = col + 1;
        if (isWhite(board, r, c))
            possible.insert(r * 8 + c);    // attack right
        c = col + 1;
        r = row;
        if (r == 3) {
            if (isWhite(board, r, c) && board[(r * 8 + c)].getCanBeEnpassant())
                possible.insert(r * 8 - 8 + c);    // enpassant right
            c = col - 1;
            r = row;
            if (isWhite(board, r, c) && board[(r * 8 + c)].getCanBeEnpassant())
                possible.insert(r * 8 - 8 + c);    // enpassant left
        }

        // what about en-passant and pawn promotion
    }
    if (board[location] == 'p')
    {
        c = col;
        r = row + 2;
        if (row == 1 && board[r * 8 + c] == ' ')
            possible.insert(r * 8 + c);  // forward two blank spaces
        r = row + 1;
        if (r < 8 && board[r * 8 + c] == ' ')
            possible.insert(r * 8 + c);    // forward one blank space
        c = col - 1;
        if (isBlack(board, r, c))
            possible.insert(r * 8 + c);      // attack left
        c = col + 1;
        if (isBlack(board, r, c))
            possible.insert(r * 8 + c);      // attack right
        // what about en-passant and pawn promotion
        c = col + 1;
        r = row;
        if (r == 4) {
            if (isBlack(board, r, c) && (board[r * 8 + c]).getCanBeEnpassant())
                possible.insert(r * 8 + 8 + c);    // enpassant right
            c = col - 1;
            if (isBlack(board, r, c) && (board[r * 8 + c]).getCanBeEnpassant())
                possible.insert(r * 8 + 8 + c);    // enpassant left
        }

    }

    //
    // KNIGHT
    //
    if (board[location] == 'N' || board[location] == 'n')
    {
        RC moves[8] =
        {
                 {-1,  2}, { 1,  2},
        {-2,  1},                    { 2,  1},
        {-2, -1},                    { 2, -1},
                 {-1, -2}, { 1, -2}
        };
        for (int i = 0; i < 8; i++)
        {
            r = row + moves[i].row;
            c = col + moves[i].col;
            if (amBlack && isNotBlack(board, r, c))
                possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                possible.insert(r * 8 + c);
        }
    }

    //
    // KING
    //
    if (board[location] == 'K' || board[location] == 'k')
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
                possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                possible.insert(r * 8 + c);
        }
        // what about castling?

        r = row;
        if (board[location] == 'K' && r == 7) {
            c = col + 1; // king side
            if (board[r * 8 + c] == ' ' && board[r * 8 + (c + 1)] == ' ' && board[r * 8 + (c + 2)] == 'R') {
                if ((board[r * 8 + (c + 2)]).getCanCastle() && board[row * 8 + col].getCanCastle()) {
                    possible.insert(r * 8 + c + 1);
                }
            }
            c = col - 1; // queen side
            if (board[r * 8 + c] == ' ' && board[r * 8 + (c - 1)] == ' ' && board[r * 8 + (c - 3)] == 'R') {
                if ((board[r * 8 + (c - 3)]).getCanCastle() && board[row * 8 + col].getCanCastle()) {
                    possible.insert(r * 8 + (c - 1));
                }
            }
        }
        if (board[location] == 'k' && r == 0) {
            c = col + 1; // king side
            if (board[r * 8 + c] == ' ' && board[r * 8 + (c + 1)] == ' ' && board[r * 8 + (c + 2)] == 'r') {
                if ((board[r * 8 + (c + 2)]).getCanCastle() && board[row * 8 + col].getCanCastle()) {
                    possible.insert(r * 8 + c + 1);
                }
            }
            c = col - 1; // queen side
            if (board[r * 8 + c] == ' ' && board[r * 8 + (c - 1)] == ' ' && board[r * 8 + (c - 3)] == 'r') {
                if (board[r * 8 + (c - 3)].getCanCastle() && board[row * 8 + col].getCanCastle()) {
                    possible.insert(r * 8 + (c - 1));
                }
            }
        }
    }

    //
    // QUEEN
    //
    if (board[location] == 'Q' || board[location] == 'q')
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
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[r * 8 + c] == ' ')
            {
                possible.insert(r * 8 + c);
                r += moves[i].row;
                c += moves[i].col;
            }
            if (amBlack && isNotBlack(board, r, c))
                possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                possible.insert(r * 8 + c);
        }
    }

    //
    // ROOK
    //
    Rook* rook = (Rook*)bord;
    if (board[location] == 'R' || board[location] == 'r')
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
                possible.insert(r * 8 + c);
                r += moves[i].row;
                c += moves[i].col;
            }
            if (amBlack && isNotBlack(board, r, c))
                possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                possible.insert(r * 8 + c);
        }
    }

    //
    // BISHOP
    //
    if (board[location] == 'B' || board[location] == 'b')
    {
        RC moves[4] =
        {
           {-1,  1}, {1,  1},
           {-1, -1}, {1, -1}
        };
        for (int i = 0; i < 4; i++)
        {
            r = row + moves[i].row;
            c = col + moves[i].col;
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[r * 8 + c] == ' ')
            {
                possible.insert(r * 8 + c);
                r += moves[i].row;
                c += moves[i].col;
            }
            if (amBlack && isNotBlack(board, r, c))
                possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                possible.insert(r * 8 + c);
        }
    }

    return possible;
}