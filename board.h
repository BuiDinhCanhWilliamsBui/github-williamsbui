#ifndef BOARD_H
#define BOARD_H
#include <vector>
// struct cho bảng
class Board
{
public:
    const int size;
    std::vector<std::vector<int>> net;
    Board(int size = 4);
    void drawboard() const;
    void add_randomTile();       // Hàm thêm ô ngẫu nhiên
    bool check_Gameover() const; // check xem Game đã over chưa
};
#endif
