#include "game.h"
#include <iostream>
using namespace std;
int main()
{
    int size;
    cout << "Enter the size of the board (board size must be larger than 3): ";
    do
    {
        cin >> size;
    } while (size < 4);
    Game game(size);
    game.Start();
    return 0;
}

// clang++ -std=c++17 -Wall -Wextra board.cpp game.cpp officialgame.cpp -o officialgame&&./officialgame