#include <iostream>
#include <vector>
#include "game.h"
#include "board.h"
using namespace std;
Game ::Game(int size) : board(size), score(0) {}
void Game ::Start()
{
    system("clear"); // clear terminal trước khi in logo

    // Logo 2048 bằng ASCII
    cout << R"(
  _______  ________  ___   ___  ________     
 /  ___  \|\   __  \|\  \ |\  \|\   __  \    
/__/|_/  /\ \  \|\  \ \  \\_\  \ \  \|\  \   
|__|//  / /\ \  \\\  \ \______  \ \   __  \  
    /  /_/__\ \  \\\  \|_____|\  \ \  \|\  \ 
   |\________\ \_______\     \ \__\ \_______\
    \|_______|\|_______|      \|__|\|_______|
                                             
        )"
         << endl;

    cout << "Press Enter to start the game...";
    cin.ignore(); // bỏ qua ký tự newline còn lại trong buffer
    cin.get();    // chờ Enter

    char move;
    while (true)
    {
        bool checkValid = true;
        board.drawboard();
        cout << endl;
        cout << endl;
        cout << "Score : " << score << endl;
        cout << endl;
        cout << endl;
        cout << "w-a-s-d to move : ";
        cin >> move;
        switch (move)
        {
        case 'w':
            moveUp();
            board.add_randomTile();
            break;
        case 's':
            moveDown();
            board.add_randomTile();
            break;
        case 'a':
            moveLeft();
            board.add_randomTile();
            break;
        case 'd':
            moveRight();
            board.add_randomTile();
            break;
        default:
            cout << "Invalid move ! Press w-a-s-d to continue your game !" << endl;
            cin.ignore();
            cin.get();
            checkValid = false;
            break;
            ;
        }
        if (!checkValid)
        {
            continue;
        }
        if (board.check_Win())
        {
            board.drawboard(); // in ra bảng cuối
            cout << R"(
____    ____  ______    __    __     ____    __    ____  __  .__   __. 
\   \  /   / /  __  \  |  |  |  |    \   \  /  \  /   / |  | |  \ |  | 
 \   \/   / |  |  |  | |  |  |  |     \   \/    \/   /  |  | |   \|  | 
  \_    _/  |  |  |  | |  |  |  |      \            /   |  | |  . `  | 
    |  |    |  `--'  | |  `--'  |       \    /\    /    |  | |  |\   | 
    |__|     \______/   \______/         \__/  \__/     |__| |__| \__| 
                                                                       
                                             
        )";
            break; // dừng game
        }

        if (board.check_Gameover())
        {
            board.drawboard(); // In ra bảng cuối cùng
            cout << R"(
____    ____  ______    __    __      __        ______        _______. _______    
\   \  /   / /  __  \  |  |  |  |    |  |      /  __  \      /       ||   ____|   
 \   \/   / |  |  |  | |  |  |  |    |  |     |  |  |  |    |   (----`|  |__      
  \_    _/  |  |  |  | |  |  |  |    |  |     |  |  |  |     \   \    |   __|     
    |  |    |  `--'  | |  `--'  |    |  `----.|  `--'  | .----)   |   |  |____    
    |__|     \______/   \______/     |_______| \______/  |_______/    |_______|   
                                                                                  
                                                                       
                                             
        )";
            break; // Kết thúc vòng lặp và dừng game
        }
    }
}
void Game ::moveLeft()
{
    for (int i = 0; i < board.size; i++)
    {
        int pos = 0;
        for (int j = 0; j < board.size; j++)
        {
            if (board.net[i][j] != 0)
            {
                board.net[i][pos] = board.net[i][j];
                if (pos != j)
                {
                    board.net[i][j] = 0;
                }
                pos++;
            }
        }
        for (int k = 0; k < board.size - 1; k++)
        {
            if (board.net[i][k] == board.net[i][k + 1])
            {
                board.net[i][k] *= 2;
                score += board.net[i][k];
                board.net[i][k + 1] = 0;
            }
        }
        int newpos = 0;
        for (int j = 0; j < board.size; j++)
        {
            if (board.net[i][j] != 0)
            {
                board.net[i][newpos] = board.net[i][j];
                if (newpos != j)
                {
                    board.net[i][j] = 0;
                }
                newpos++;
            }
        }
    }
}
void Game ::moveRight()
{
    for (int i = board.size - 1; i >= 0; i--)
    {
        int pos = board.size - 1;
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
        for (int k = board.size - 1; k > 0; k--)
        {
            if (board.net[i][k] == board.net[i][k - 1])
            {
                board.net[i][k] *= 2;
                score += board.net[i][k];
                board.net[i][k - 1] = 0;
            }
        }
        int newpos = board.size - 1;
        for (int j = board.size - 1; j >= 0; j--)
        {
            if (board.net[i][j] != 0)
            {
                board.net[i][newpos] = board.net[i][j];
                if (newpos != j)
                {
                    board.net[i][j] = 0;
                }
                newpos--;
            }
        }
    }
}
void Game::moveUp()
{
    for (int j = 0; j < board.size; j++)
    {
        int pos = 0;
        for (int i = 0; i < board.size; i++)
        {
            if (board.net[i][j] != 0)
            {
                board.net[pos][j] = board.net[i][j];
                if (pos != i)
                {
                    board.net[i][j] = 0;
                }
                pos++;
            }
        }
        for (int k = 0; k < board.size - 1; k++)
        {
            if (board.net[k][j] != 0 && board.net[k][j] == board.net[k + 1][j])
            {
                board.net[k][j] *= 2;
                score += board.net[k][j];
                board.net[k + 1][j] = 0;
            }
        }
        int newpos = 0;
        for (int i = 0; i < board.size; i++)
        {
            if (board.net[i][j] != 0)
            {
                board.net[newpos][j] = board.net[i][j];
                if (newpos != i)
                {
                    board.net[i][j] = 0;
                }
                newpos++;
            }
        }
    }
}
void Game::moveDown()
{
    for (int j = 0; j < board.size; j++)
    {
        int pos = board.size - 1;
        for (int i = board.size - 1; i >= 0; i--)
        {
            if (board.net[i][j] != 0)
            {
                board.net[pos][j] = board.net[i][j];
                if (pos != i)
                {
                    board.net[i][j] = 0;
                }
                pos--;
            }
        }
        for (int k = board.size - 1; k >= 1; k--)
        {
            if (board.net[k][j] == board.net[k - 1][j])
            {
                board.net[k][j] *= 2;
                score += board.net[k][j];
                board.net[k - 1][j] = 0;
            }
        }
        int newpos = board.size - 1;
        for (int i = board.size - 1; i >= 0; i--)
        {
            if (board.net[i][j] != 0)
            {
                board.net[newpos][j] = board.net[i][j];
                if (newpos != i)
                {
                    board.net[i][j] = 0;
                }
                newpos--;
            }
        }
    }
}