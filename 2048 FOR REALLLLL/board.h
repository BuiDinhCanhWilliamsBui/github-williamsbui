#ifndef BOARD_H //
#define BOARD_H
#include <vector>
// struct cho bảng
class board
{
private:
    int size;
    std::vector<std::vector<int>> net;

public:
    board(int a = 4);
    void drawboard() const; // cải tiến dùng const tối ưu hiệu suất,
    // việc CPU truy cập vào cache nhanh hơn khi truy xuất lại qua RAM
    void move_Up();
    void move_Down();
    void move_Left();
    void move_Right();
    void add_randomTile();
    bool check_Gameover() const;
};
#endif
