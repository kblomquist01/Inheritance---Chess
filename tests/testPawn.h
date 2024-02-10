#pragma once

#include "board.h"

using namespace std;

class TestPawn
{
public:
    void run()
    {
        getMoves_blocked();
        getMoves_simpleMove();
        getMoves_initialMove();
        getMoves_capture();
        getMoves_enpassant();
        getMoves_promotion();
    }

private:

    void getMoves_blocked();
    void getMoves_simpleMove();
    void getMoves_initialMove();
    void getMoves_capture();
    void getMoves_enpassant();
    void getMoves_promotion();
};
