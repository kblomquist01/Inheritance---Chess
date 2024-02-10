
#include "king.h"
#include "pawn.h"
#include "board.h"
#include "rook.h"

#include "testKing.h"

using namespace std;

/**************************************************
    * GET MOVES - King can move in all directions
    * +---a-b-c-d-e-f-g-h---+
    * |                     |
    * 8                     8
    * 7                     7
    * 6         * * *       6
    * 5         *(k)*       5
    * 4         * * *       4
    * 3                     3
    * 2                     2
    * 1                     1
    * |                     |
    * +---a-b-c-d-e-f-g-h---+
    **************************************************/
void TestKing::getMoves_free()
{
    // setup
    Board board;
    board.clear();

    King king;
    king.white = true;
    king.position = Position(4, 4); // e5
    board.assign(king);

    // exercise
    auto moves = king.getMoves(board);

    // verify
    set<string> expectedMoves{ "e5d6", "e5e6", "e5f6", "e5d5", "e5f5", "e5d4", "e5e4", "e5f4" };
    set<string> actualMoves;
    for (auto& move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);
    assert(king.position == Position(4, 4));

}  // cleanup

void TestKing::getMoves_blocked()
{
    // setup
    Board board;
    board.clear();

    King king;
    king.white = true;
    king.position = Position(4, 4); // e5
    board.assign(king);

    Pawn pawn1(3, 5, true);
    board.assign(pawn1);
    Pawn pawn2(4, 5, true);
    board.assign(pawn2);
    Pawn pawn3(5, 5, true);
    board.assign(pawn3);
    Pawn pawn4(3, 4, true);
    board.assign(pawn4);
    Pawn pawn5(5, 4, true);
    board.assign(pawn5);
    Pawn pawn6(3, 3, true);
    board.assign(pawn6);
    Pawn pawn7(4, 3, true);
    board.assign(pawn7);
    Pawn pawn8(5, 3, true);
    board.assign(pawn8);

    // exercise
    auto moves = king.getMoves(board);

    // verify
    set<string> expectedMoves{};
    set<string> actualMoves;
    for (auto& move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);

    // cleanup
}

void TestKing::getMoves_capture()
{
    // setup
    Board board;
    board.clear();

    King king;
    king.position = Position(4, 4); // e6
    king.white = true;
    board.assign(king);

    Pawn pawn1(3, 5, false);
    board.assign(pawn1);
    Pawn pawn2(4, 5, false);
    board.assign(pawn2);
    Pawn pawn3(5, 5, false);
    board.assign(pawn3);
    Pawn pawn4(3, 4, false);
    board.assign(pawn4);
    Pawn pawn5(5, 4, false);
    board.assign(pawn5);
    Pawn pawn6(3, 3, false);
    board.assign(pawn6);
    Pawn pawn7(4, 3, false);
    board.assign(pawn7);
    Pawn pawn8(5, 3, false);
    board.assign(pawn8);

    // exercise
    auto moves = king.getMoves(board);

    // verify
    set<string> expectedMoves{ "e6d6p", "e6e5p", "e6f6p", "e6d5p", "e6f5p", "e6d7p", "e6e7p", "e6f7p" };
    set<string> actualMoves;
    for (auto& move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);

    // cleanup
}

void TestKing::getMoves_castleKingMoved()
{
    // setup
    Board board;
    board.clear();

    King king;
    king.position = Position(4, 0); // e1
    king.nMoves = 1;
    board.assign(king);

    Rook rook1(0, 0, true);//a1
    board.assign(rook1);
    Rook rook2(7, 0, true);//h1
    board.assign(rook2);

    // exercise
    auto moves = king.getMoves(board);

    // verify
    set<string> expectedMoves{ "e1f1", "e1d1", "e1d2", "e1e2", "e1f2" };
    set<string> actualMoves;
    for (auto& move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);

    // cleanup
}

void TestKing::getMoves_castleKingMovedNMoves()
{
    // setup
    Board board;
    board.clear();

    King king;
    king.position = Position(4, 0); // e1
    board.assign(king);

    Rook rook1(1, 0, true);//a1
    rook1.nMoves = 1;
    board.assign(rook1);
    Rook rook2(7, 0, true);//h1
    rook2.nMoves = 1;
    board.assign(rook2);

    // exercise
    auto moves = king.getMoves(board);

    // verify
    set<string> expectedMoves{ "e1f1", "e1d1", "e1d2", "e1e2", "e1f2" };
    set<string> actualMoves;
    for (auto& move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);

    // cleanup
}

void TestKing::getMoves_castleBlocked()
{
    // setup
    Board board;
    board.clear();

    King king;
    king.position = Position(4, 0); // e1
    king.nMoves = 0;
    board.assign(king);

    Rook rook1(1, 0, true);//a1
    rook1.nMoves = 0;
    board.assign(rook1);
    Rook rook2(7, 0, true);//h1
    rook2.nMoves = 0;
    board.assign(rook2);

    Pawn pawn1(1, 0, false);//b1
    board.assign(pawn1);
    Pawn pawn2(6, 0, false);//g2
    board.assign(pawn2);

    // exercise
    auto moves = king.getMoves(board);

    // verify
    set<string> expectedMoves{ "e1f1", "e1d1", "e1d2", "e1e2", "e1f2" };
    set<string> actualMoves;
    for (auto& move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);

    // cleanup
}

void TestKing::getMoves_castle()
{
    // setup
    Board board;
    board.clear();

    King king;
    king.position = Position(4, 0); // e1
    king.nMoves = 0;
    board.assign(king);

    Rook rook1(0, 0, true);//a1
    rook1.nMoves = 0;
    board.assign(rook1);
    Rook rook2(7, 0, true);//h1
    rook2.nMoves = 0;
    board.assign(rook2);

    // exercise
    auto moves = king.getMoves(board);

    // verify
    set<string> expectedMoves{ "e1f1", "e1d1", "e1g1c", "e1c1C", "e1d2", "e1e2", "e1f2" };
    set<string> actualMoves;
    for (auto& move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);

    // cleanup
}

