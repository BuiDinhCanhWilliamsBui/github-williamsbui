#ifndef BOARD_H
#define BOARD_H
#include <vector>
// struct cho bảng
class Board
{
private:
    int size;
    std::vector<std::vector<int>> net;

public:
    Board(int size = 4);
    void drawboard() const;
    void move_Up();
    void move_Down();
    void move_Left();
    void move_Right();
    void add_randomTile();
    bool check_Gameover() const;
};
#endif
