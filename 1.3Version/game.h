#pragma once
#include "board.h"

class Game
{
public:
    int score;
    int highscore;
    Board board;
    Difficulty difficulty;

    Game(int size = 4, Difficulty diff = Difficulty::EASY);
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
};