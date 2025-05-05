#pragma once
#include "board.h"

class Game
{
public:
    int score;
    int highscore;
    Board board;

    Game(int size = 4);
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
};