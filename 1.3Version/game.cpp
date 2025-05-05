#include "game.h"
#include "board.h"
#include <vector>
using namespace std;

Game::Game(int size) : board(size), score(0), highscore(0) {}

bool Game::moveLeft()
{
    bool moved = false;
    for (int i = 0; i < board.size; i++)
    {
        // Nén các ô không trống về bên trái
        int pos = 0;
        for (int j = 0; j < board.size; j++)
        {
            if (board.net[i][j] != 0)
            {
                if (pos != j)
                {
                    board.net[i][pos] = board.net[i][j];
                    board.net[i][j] = 0;
                    moved = true;
                }
                pos++;
            }
        }
        // Gộp các ô giống nhau
        for (int k = 0; k < board.size - 1; k++)
        {
            if (board.net[i][k] != 0 && board.net[i][k] == board.net[i][k + 1])
            {
                board.net[i][k] *= 2;
                score += board.net[i][k];
                if (score > highscore)
                {
                    highscore = score;
                }
                board.net[i][k + 1] = 0;
                moved = true;
            }
        }
        // Nén lại lần nữa
        pos = 0;
        for (int j = 0; j < board.size; j++)
        {
            if (board.net[i][j] != 0)
            {
                if (pos != j)
                {
                    board.net[i][pos] = board.net[i][j];
                    board.net[i][j] = 0;
                }
                pos++;
            }
        }
    }
    return moved;
}

bool Game::moveRight()
{
    bool moved = false;
    for (int i = 0; i < board.size; i++)
    {
        int pos = board.size - 1;
        for (int j = board.size - 1; j >= 0; j--)
        {
            if (board.net[i][j] != 0)
            {
                if (pos != j)
                {
                    board.net[i][pos] = board.net[i][j];
                    board.net[i][j] = 0;
                    moved = true;
                }
                pos--;
            }
        }
        for (int k = board.size - 1; k > 0; k--)
        {
            if (board.net[i][k] != 0 && board.net[i][k] == board.net[i][k - 1])
            {
                board.net[i][k] *= 2;
                score += board.net[i][k];
                if (score > highscore)
                {
                    highscore = score;
                }
                board.net[i][k - 1] = 0;
                moved = true;
            }
        }
        pos = board.size - 1;
        for (int j = board.size - 1; j >= 0; j--)
        {
            if (board.net[i][j] != 0)
            {
                if (pos != j)
                {
                    board.net[i][pos] = board.net[i][j];
                    board.net[i][j] = 0;
                }
                pos--;
            }
        }
    }
    return moved;
}

bool Game::moveUp()
{
    bool moved = false;
    for (int j = 0; j < board.size; j++)
    {
        int pos = 0;
        for (int i = 0; i < board.size; i++)
        {
            if (board.net[i][j] != 0)
            {
                if (pos != i)
                {
                    board.net[pos][j] = board.net[i][j];
                    board.net[i][j] = 0;
                    moved = true;
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
                if (score > highscore)
                {
                    highscore = score;
                }
                board.net[k + 1][j] = 0;
                moved = true;
            }
        }
        pos = 0;
        for (int i = 0; i < board.size; i++)
        {
            if (board.net[i][j] != 0)
            {
                if (pos != i)
                {
                    board.net[pos][j] = board.net[i][j];
                    board.net[i][j] = 0;
                }
                pos++;
            }
        }
    }
    return moved;
}

bool Game::moveDown()
{
    bool moved = false;
    for (int j = 0; j < board.size; j++)
    {
        int pos = board.size - 1;
        for (int i = board.size - 1; i >= 0; i--)
        {
            if (board.net[i][j] != 0)
            {
                if (pos != i)
                {
                    board.net[pos][j] = board.net[i][j];
                    board.net[i][j] = 0;
                    moved = true;
                }
                pos--;
            }
        }
        for (int k = board.size - 1; k >= 1; k--)
        {
            if (board.net[k][j] != 0 && board.net[k][j] == board.net[k - 1][j])
            {
                board.net[k][j] *= 2;
                score += board.net[k][j];
                if (score > highscore)
                {
                    highscore = score;
                }
                board.net[k - 1][j] = 0;
                moved = true;
            }
        }
        pos = board.size - 1;
        for (int i = board.size - 1; i >= 0; i--)
        {
            if (board.net[i][j] != 0)
            {
                if (pos != i)
                {
                    board.net[pos][j] = board.net[i][j];
                    board.net[i][j] = 0;
                }
                pos--;
            }
        }
    }
    return moved;
}