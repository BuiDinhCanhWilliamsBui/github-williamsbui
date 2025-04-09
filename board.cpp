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
            if (cell == 0)
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
void Board::add_randomTile() // pick a random number 2/4 - Ở phiên bản 1.1 này tỉ lệ ô 2/4 ngẫu nhiên sẽ là 50 - 50
{
    vector<pair<int, int>> check; // check if a cell is empty
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (net[i][j] == 0)
            {
                check.push_back({i, j});
            }
        }
    }
    if (!check.empty())
    {
        std::pair<int, int> cell = check[rand() % (int)check.size()]; // pick a random cell
        int a = cell.first, b = cell.second;
        int check2 = rand() % 2;
        if (check2 == 0)
        {
            net[a][b] = 2;
        }
        if (check2 == 1)
        {
            net[a][b] = 4;
        }
    }
}
bool Board::check_Gameover() const
{
    for (const vector<int> &row : net)
    {
        for (int cell : row)
        {
            if (cell == 0)
            {
                return false; // kiểm tra còn ô trống thì vẫn còn nước đi
            }
        }
    }
    for (int i = 0; i < size; i++) // check xem còn 2 ô kề nhau bằng nhau thì vẫn còn nước đi
    {
        for (int j = 0; j < size; j++)
        {
            if ((i < 3 && net[i][j] == net[i + 1][j]) || (j < 3 && net[i][j] == net[i][j + 1]))
            {
                return false;
            }
        }
    }
    return true; // nếu không còn gì để move thì gameover !
}