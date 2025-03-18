#include <iostream>
#include <vector>
#include "game.h"
#include "board.h"
using namespace std;
Game ::Game() : score(0) {}
void Game ::Start()
{
    char move;
    while (!board.check_Gameover())
    {
        board.drawboard();
        cout << "Score : " << score << endl;
        cout << "w-a-s-d to move : ";
        cin >> move;
        switch (move)
        {
        case 'w':
            moveUp();
            break;
        case 's':
            moveDown();
            break;
        case 'a':
            moveLeft();
            break;
        case 'd':
            moveRight();
            break;
        default:
            cout << "invalid move !" << endl;
        }
        board.add_randomTile();
    }
}
void Game ::moveLeft()
{
    // di chuyển ô khác  0  sang trái,thay cho các ô  = 0  bên cạnh
    for (int i = 0; i < board.size; i++)
    {
        int pos = 0; // khởi tạo vị trí để dịch ô
        for (int j = 0; j < board.size; j++)
        {
            if (board.net[i][j] != 0) // bắt đầu từ ô khác 0  đầu tiên
            {
                board.net[i][pos] = board.net[i][j];
                if (pos != j) // chứng tỏ pos đang dừng ở ô  = 0 ;còn j đã chạy đến ô khác  0 ==> đã dịch thành công
                {
                    board.net[i][j] = 0; // cho vị trí vừa chuyển đi  = 0;
                }
                pos++;
            }
        }
        // Gộp ô giống nhau
        for (int k = 0; k < board.size; k++)
        {
            if (board.net[i][k] == board.net[i][k + 1])
            {
                board.net[i][k] *= 2;
                board.net[i][k + 1] = 0;
            }
        }
    }
}
void Game ::moveRight()
{
    // di chuyển ô khác 0 sang phải , thay cho các ô = 0  bên cạnh
    for (int i = board.size - 1; i >= 0; i--)
    {
        int pos = board.size - 1; // khởi tạo vị trí dịch ô
        for (int j = board.size - 1; j >= 0; j--)
        {
            if (board.net[i][j] != 0)
            {
                board.net[i][pos] = board.net[i][j];
                if (pos != j)
                {
                    board.net[i][j] = 0;
                }
                pos--;
            }
        }
        for (int k = board.size - 1; k >= 0; k--)
        {
            if (board.net[i][k] == board.net[i][k - 1])
            {
                board.net[i][k] *= 2;
                board.net[i][k - 1] = 0;
            }
        }
    }
}