#include "Piece.h"




bool Piece::move(Piece* board[], int positionFrom, int positionTo)
{
    //Piece* board = (Piece*)bord;
    // do not move if a move was not indicated
    if (positionFrom == -1 || positionTo == -1)
        return false;
    assert(positionFrom >= 0 && positionFrom < 64);
    assert(positionTo >= 0 && positionTo < 64);


    // find the set of possible moves from our current location
    set <int> possiblePrevious = getPossibleMoves(board, positionFrom);

    // Enpassant movement
    if (board[positionFrom]->getType() == 'P') {

        if (board[positionTo]->getType() == ' ' && board[positionTo + 8]->getType() == 'p') {
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

        for (int row = 7; row >= 0; row--) {
            for (int col = 0; col < 8; col++) {
                board[row * 8 + col].isWhiteTurn = !isWhiteTurn;
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

set <int> Piece::getPossibleMoves(void* bord, int location) {
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
    if (board[location] == 'P' && !isWhiteTurn)
    {
        c = col;
        r = row - 2;
        if (row == 6 && board[r * 8 + c] == ' ') 
            if(testMoveOutCheck(bord, location, r * 8 + c))
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
    if (board[location] == 'p' && isWhiteTurn)
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

    //
    // KNIGHT
    //
    if (board[location] == 'N' && !isWhiteTurn)
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
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
        }
    }
    if (board[location] == 'n' && isWhiteTurn)
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
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
            if (!amBlack && isNotWhite(board, r, c))
                if (testMoveOutCheck(bord, location, r * 8 + c))
                    possible.insert(r * 8 + c);
        }
    }
    //
    // KING
    //
    if (board[location] == 'K' && !isWhiteTurn)
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

    if (board[location] == 'k' && isWhiteTurn)
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
    // QUEEN
    //
    if (board[location] == 'Q' && !isWhiteTurn)
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
    if (board[location] == 'q' && isWhiteTurn)
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
    //
    // ROOK
    //
    Rook* rook = (Rook*)bord;
    if (board[location] == 'R' && !isWhiteTurn)
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
    if (board[location] == 'r' && isWhiteTurn)
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
    //
    // BISHOP
    //
    if (board[location] == 'B' && !isWhiteTurn)
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
            //Important
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
    if (board[location] == 'b' && isWhiteTurn)
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

/********************************************************
 * GET POSSIBLE CHECKS
 * checks the kings location and sees if any enemy pieces put it in check
 *******************************************************/
set <int> Piece::getPossibleChecks(void* bord, int location) {

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

    if (board[location] == 'k' && isWhiteTurn)
    {
        RC repeatMoves[8] =
        {
            {-1,  1}, {0,  1}, {1,  1},
            {-1,  0},          {1,  0},
            {-1, -1}, {0, -1}, {1, -1}
        };
        
        for (int i = 0; i < 8; i++)
        {
            r = row + repeatMoves[i].row;
            c = col + repeatMoves[i].col;
            while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                board[r * 8 + c] == ' ')
            {
                

                r += repeatMoves[i].row;
                c += repeatMoves[i].col;
            }
            if (((i == 0 || i == 2 || i == 5 || i == 7) && board[r * 8 + c].getType() == 'B') || board[r * 8 + c].getType() == 'Q')
                possible.insert(r * 8 + c);
            else if ((i == 1 || i == 3 || i == 4 || i == 6) && board[r * 8 + c].getType() == 'R')
                possible.insert(r * 8 + c);

            RC singleMoves[8] =
            {
                     {-1,  2}, { 1,  2},
            {-2,  1},                    { 2,  1},
            {-2, -1},                    { 2, -1},
                     {-1, -2}, { 1, -2}
            };

            for (int i = 0; i < 8; i++)
                {
                    r = row + singleMoves[i].row;
                    c = col + singleMoves[i].col;

                    if (r <= 0 && r > 8 && c <= 0 && c > 8 && board[r * 8 + c].getType() == 'N')
                        possible.insert(r * 8 + c);
                    
                }
            
        }
    }
    else if (board[location] == 'K' && !isWhiteTurn)
    {
         RC repeatMoves[8] =
         {
             {-1,  1}, {0,  1}, {1,  1},
             {-1,  0},          {1,  0},
             {-1, -1}, {0, -1}, {1, -1}
         };
         
         for (int i = 0; i < 8; i++)
         {
             r = row + repeatMoves[i].row;
             c = col + repeatMoves[i].col;
             while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
                 board[r * 8 + c] == ' ')
             {
                 
         
                 r += repeatMoves[i].row;
                 c += repeatMoves[i].col;
             }
             if (((i == 0 || i == 2 || i == 5 || i == 7) && board[r * 8 + c].getType() == 'b') || board[r * 8 + c].getType() == 'q')
                 possible.insert(r * 8 + c);
             else if ((i == 1 || i == 3 || i == 4 || i == 6) && board[r * 8 + c].getType() == 'r')
                 possible.insert(r * 8 + c);
         
             RC singleMoves[8] =
             {
                      {-1,  2}, { 1,  2},
             {-2,  1},                    { 2,  1},
             {-2, -1},                    { 2, -1},
                      {-1, -2}, { 1, -2}
             };
         
             for (int i = 0; i < 8; i++)
             {
                 r = row + singleMoves[i].row;
                 c = col + singleMoves[i].col;
         
                 if (board[r * 8 + c].getType() == 'n')
                     possible.insert(r * 8 + c);
         
             }
         
         }
    }
    return possible;
}
bool Piece::getInCheck(void* bord) {
    Piece* board = (Piece*)bord;
    int king = 0;
    if (isWhiteTurn) {
        for (int row = 7; row >= 0; row--) {
            for (int col = 0; col < 8; col++) {
                if (board[row * 8 + col].getType() == 'k') {
                    king = row * 8 + col;
                }
            }
        }
        set <int> possible = getPossibleChecks(board, king);
        if (possible.size() == 0)
            return false;
        /*for (int row = 7; row >= 0; row--) {
            for (int col = 0; col < 8; col++) {


                board[0].isWhiteTurn = !isWhiteTurn;
                set <int> possible = getPossibleMoves2(board, king);
                auto it = possible.find(king);
                if (it != possible.end()) {

                    board[0].isWhiteTurn = !isWhiteTurn;
                    return true;
                }

                board[0].isWhiteTurn = !isWhiteTurn;
                
            }
        }*/
    }
    else if (!isWhiteTurn) {
        for (int row = 7; row >= 0; row--) {
            for (int col = 0; col < 8; col++) {
                if (board[row * 8 + col].getType() == 'K') {
                    king = row * 8 + col;
                }
            }
        }
        set <int> possible = getPossibleChecks(board, king);
        if (possible.size() == 0)
            return false;
        /*for (int row = 7; row >= 0; row--) {
            for (int col = 0; col < 8; col++) {

                board[0].isWhiteTurn = !isWhiteTurn;
                set <int> possible = getPossibleMoves2(board, king);
                auto it = possible.find(king);
                if (it != possible.end()) {

                    board[0].isWhiteTurn = !isWhiteTurn;
                    return true;
                }

                board[0].isWhiteTurn = !isWhiteTurn;
            }
        }*/
    }
    return true;
}

bool Piece::testMoveOutCheck(void* bord, int positionFrom, int positionTo) {
    Piece* board = (Piece*)bord;
    bool willBeInCheck;
    Piece save = board[positionTo];
    //testing future board
    board[positionTo] = board[positionFrom];
    board[positionFrom] = ' ';
    willBeInCheck = !getInCheck(board);
    //reset board
    board[positionFrom] = board[positionTo];
    board[positionTo] = save;
    return willBeInCheck;
}