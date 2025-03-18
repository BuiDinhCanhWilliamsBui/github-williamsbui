#ifndef BOARD_H
#define BOARD_H
#include <vector>
// struct cho bảng
class Board
{
public:
    std::vector<std::vector<int>> net;
    const int size;
    Board(int size = 4);
    void drawboard() const;
    void add_randomTile();
    bool check_Gameover() const;
};
#endif
