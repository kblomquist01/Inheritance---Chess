#include "Pawn.h"

void Pawn :: setEnpassant(bool enpassant) {
    canEnpassant = enpassant;
}

//bool move(Piece* board, int positionFrom, int positionTo)
//{
//    // do not move if a move was not indicated
//    if (positionFrom == -1 || positionTo == -1)
//        return false;
//    assert(positionFrom >= 0 && positionFrom < 64);
//    assert(positionTo >= 0 && positionTo < 64);
//
//
//    // find the set of possible moves from our current location
//    set <int> possiblePrevious = board[positionFrom].getPossibleMoves(board, positionFrom);
//
//    // only move there is the suggested move is on the set of possible moves
//    if (possiblePrevious.find(positionTo) != possiblePrevious.end())
//    {
//        board[positionTo] = board[positionFrom];
//        board[positionFrom] = Piece();
//        return true;
//    }
//
//    return false;
//
//}