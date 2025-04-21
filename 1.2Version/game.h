#pragma once
#include "board.h"
class Game
{
private:
    Board board; // đối tượng board để game.cpp xử lí bảng
    int score;

public:
    Game(int size = 4); // constructor khởi tạo , để bắt đầu với score  = 0;
    void Start();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};