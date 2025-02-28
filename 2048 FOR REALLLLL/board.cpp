#include <iostream>
#include "board.h"
#include <vector>

board::board(int s) : size(s), net(s, std::vector<int>(s, 0))
{
    addNewTile();
    addNewTile();
}
