#include "game.h"

int main()
{
    Game game;
    game.Start();
    return 0;
}

// clang++ -std=c++17 -Wall -Wextra board.cpp game.cpp officialgame.cpp -o officialgame&&./officialgame