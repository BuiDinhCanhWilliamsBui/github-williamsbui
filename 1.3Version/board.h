#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Board
{
public:
    int size;
    std::vector<std::vector<int>> net;
    Board(int size = 4);
    void add_randomTile();
    bool check_Win() const;
    bool check_Gameover() const;
    // Hàm vẽ bảng bằng SDL : Update hàm ngày 21/04
    void drawBoardSDL(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight) const;
};

#endif