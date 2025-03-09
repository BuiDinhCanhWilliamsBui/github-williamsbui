// sinh ô ngẫu nhiên , tạo bảng , di chuyển , kiểm tra thắng thua .
#include <iostream>
#include "board.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
Board::Board(int size) : size(size), net(size, std::vector<int>(size, 0))
{
    srand(time(0));
    add_randomTile();
    add_randomTile(); // 2 lần xuất hiện của 2 ô ngẫu nhiên đầu game
}
// vẽ bảng
void Board ::drawboard() const
{
    system("clear");
    for (const vector<int> &row : net) // thay vì in ra số 0 của ô thì in ra .
    {
        for (int cell : row)
        {
            if (cel == 0)
            {
                cout << ".\t";
            }
            else
            {
                cout << cell << "\t";
            }
        }
        cout << "\n";
    }
}
