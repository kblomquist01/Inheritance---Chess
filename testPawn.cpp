
#include "testPawn.h"
    
    /**************************************************
     * GET MOVES - Blocked by another piece
     * +---a-b-c-d-e-f-g-h---+
     * |                     |
     * 8                     8
     * 7                     7
     * 6                     6
     * 5         P           5
     * 4        (p)          4
     * 3                     3
     * 2                     2
     * 1                     1
     * |                     |
     * +---a-b-c-d-e-f-g-h---+
     **************************************************/
void TestPawn::getMoves_blocked()
{
    // setup
    Board board;
    Pawn pawn;
    pawn.white = true;
    pawn.position = Position(3, 3); // d4    
    board.assign(pawn);


    Pawn pawn2;    
    pawn2.white = true;
    pawn2.position = Position(3, 4); // d5
    board.assign(pawn2);

      
    // exercise
    auto moves = pawn.getMoves(board);


    // verify
    set<string> expectedMoves{};
    set<string> actualMoves;
    for (auto move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);
    assert(pawn.position == Position(3, 3));   
    assert(pawn2.position == Position(3, 4));    
}  // cleanup

    /**************************************************
     * GET MOVES - Move a pawn forward
     * +---a-b-c-d-e-f-g-h---+
     * |                     |
     * 8                     8
     * 7                     7
     * 6                     6
     * 5     *               5
     * 4    (p)              4
     * 3                     3
     * 2                     2
     * 1                     1
     * |                     |
     * +---a-b-c-d-e-f-g-h---+
     **************************************************/
void TestPawn::getMoves_simpleMove()
{
    // setup
    Board board;

    Pawn pawn;
    pawn.white = true;
    pawn.position = Position(1, 3); // b4
    board.assign(pawn);

    // exercise
    auto moves = pawn.getMoves(board);

    // verify
    set<string> expectedMoves{ "b4b5" };
    set<string> actualMoves;
    for (auto move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);
    assert(pawn.position == Position(1, 3));

}  // cleanup

    /**************************************************
     * GET MOVES - Move a pawn one or two spaces on its first move
     * +---a-b-c-d-e-f-g-h---+
     * |                     |
     * 8                     8
     * 7                     7
     * 6                     6
     * 5                     5
     * 4     *               4
     * 3     *               3
     * 2    (p)              2
     * 1                     1
     * |                     |
     * +---a-b-c-d-e-f-g-h---+
     **************************************************/
void TestPawn::getMoves_initialMove()
{
    // setup
    Board board;

    Pawn pawn;
    pawn.white = true;
    pawn.position = Position(1, 1); // b2
    board.assign(pawn);

    // exercise
    auto moves = pawn.getMoves(board);

    // verify
    set<string> expectedMoves{ "b2b3", "b2b4" };
    set<string> actualMoves;
    for (auto move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);
    assert(pawn.position == Position(1, 1));

}  // cleanup

    /**************************************************
     * GET MOVES - Capture pawns diagonally
     * +---a-b-c-d-e-f-g-h---+
     * |                     |
     * 8                     8
     * 7   P P P             7
     * 6    (p)              6
     * 5                     5
     * 4                     4
     * 3                     3
     * 2                     2
     * 1                     1
     * |                     |
     * +---a-b-c-d-e-f-g-h---+
     **************************************************/
void TestPawn::getMoves_capture()
{
    // setup
    Board board;

    Pawn pawn;
    pawn.white = true;
    pawn.position = Position(1, 5); // b6
    board.assign(pawn);

    Pawn pawn2;
    pawn2.white = false;
    pawn2.position = Position(0, 6); // a7
    board.assign(pawn2);
    Pawn pawn3;
    pawn3.white = true;
    pawn3.position = Position(1, 6); // b7
    board.assign(pawn3);

    Pawn pawn4;
    pawn4.white = true;
    pawn4.position = Position(2, 6); // c7
    board.assign(pawn4);

    // exercise
    auto moves = pawn.getMoves(board);

    // verify
    set<string> expectedMoves{ "b6a7p", "b6c7p" };
    set<string> actualMoves;
    for (auto move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);
    assert(pawn.position == Position(1, 5));
    assert(pawn2.position == Position(0, 6));
    assert(pawn3.position == Position(1, 6));
    assert(pawn4.position == Position(2, 6));

}  // cleanup

     /**************************************************
     * GET MOVES - Blocked by another piece
     * +---a-b-c-d-e-f-g-h---+
     * |                     |
     * 8                     8
     * 7                     7
     * 6   . P .             6
     * 5   P(p)P             5
     * 4                     4
     * 3                     3
     * 2                     2
     * 1                     1
     * |                     |
     * +---a-b-c-d-e-f-g-h---+
     **************************************************/
void TestPawn::getMoves_enpassant()
{
    // setup
    Board board;

    Pawn pawn;
    pawn.white = true;
    pawn.position = Position(1, 4); // b5
    board.assign(pawn);

    Pawn pawn2;
    pawn2.white = false;
    pawn2.position = Position(1, 5); // b6
    board.assign(pawn2);

    Pawn pawn3;
    pawn3.white = false;
    pawn3.position = Position(0, 4); // a5
    pawn3.lastMove = 1;
    board.assign(pawn3);

    Pawn pawn4;
    pawn4.white = false;
    pawn4.position = Position(2, 4); // c5
    pawn4.lastMove = 1;
    board.assign(pawn4);

    // exercise
    auto moves = pawn.getMoves(board);

    // verify
    set<string> expectedMoves{ "b5c6E", "b5a6E" };
    set<string> actualMoves;
    for (auto move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);
    assert(pawn.position == Position(1, 4));
    assert(pawn2.position == Position(1, 5));
    assert(pawn3.position == Position(0, 4));
    assert(pawn4.position == Position(2, 4));

}  // cleanup

     /**************************************************
     * GET MOVES - Blocked by another piece
     * +---a-b-c-d-e-f-g-h---+
     * |                     |
     * 8     *               8
     * 7    (p)              7
     * 6                     6
     * 5                     5
     * 4                     4
     * 3                     3
     * 2                     2
     * 1                     1
     * |                     |
     * +---a-b-c-d-e-f-g-h---+
     **************************************************/
void TestPawn::getMoves_promotion()
{
    // setup
    Board board;

    Pawn pawn;
    pawn.white = true;
    pawn.position = Position(1, 6); // b7
    board.assign(pawn);

    // exercise
    auto moves = pawn.getMoves(board);

    // verify
    set<string> expectedMoves{ "b7b8Q" };
    set<string> actualMoves;
    for (auto move : moves)
        actualMoves.insert(move.getText());

    assert(expectedMoves == actualMoves);
    assert(pawn.position == Position(1, 6));

}  // cleanup

