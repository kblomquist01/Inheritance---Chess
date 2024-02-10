#pragma once

using namespace std;

/**************************************************
 * TEST KING
 * Unit tests for the King class
 **************************************************/
class TestKing
{
public:
   void run()
   {
      getMoves_free();
      getMoves_blocked();
      getMoves_capture();
      getMoves_castleKingMoved();
      getMoves_castleKingMovedNMoves();
      getMoves_castleBlocked();
      getMoves_castle();
   }

private:
   
    void getMoves_free();
    void getMoves_blocked();
    void getMoves_capture();
    void getMoves_castleKingMoved();
    void getMoves_castleKingMovedNMoves();
    void getMoves_castleBlocked();
    void getMoves_castle();
};
