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
void Game ::moveUp()
{
    for
}