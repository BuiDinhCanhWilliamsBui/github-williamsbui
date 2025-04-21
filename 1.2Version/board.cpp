// sinh ô ngẫu nhiên , tạo bảng , di chuyển , kiểm tra thắng thua .
#include <iostream>
#include "board.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

    const std::string horizontal = "──────";
    const std::string topLeft = "┌", topMid = "┬", topRight = "┐";
    const std::string midLeft = "├", midMid = "┼", midRight = "┤";
    const std::string botLeft = "└", botMid = "┴", botRight = "┘";
    const std::string vertical = "│";

    auto print_row_border = [&](const std::string &left, const std::string &mid, const std::string &right)
    {
        std::cout << left;
        for (int i = 0; i < size; ++i)
        {
            std::cout << horizontal;
            if (i < size - 1)
                std::cout << mid;
        }
        std::cout << right << "\n";
    };

    print_row_border(topLeft, topMid, topRight);
    for (int i = 0; i < size; ++i)
    {
        std::cout << vertical;
        for (int j = 0; j < size; ++j)
        {
            if (net[i][j] == 0)
                std::cout << "      ";
            else
                std::cout << std::setw(6) << net[i][j];
            std::cout << vertical;
        }
        std::cout << "\n";
        if (i < size - 1)
            print_row_border(midLeft, midMid, midRight);
    }
    print_row_border(botLeft, botMid, botRight);
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
bool Board::check_Win() const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (net[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
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