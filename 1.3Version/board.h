#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum class Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

class Board
{
public:
    int size;
    std::vector<std::vector<int>> net;
    Difficulty difficulty;
    Board(int size = 4, Difficulty diff = Difficulty::EASY);
    void add_randomTile();
    bool check_Win() const;
    bool check_Gameover() const;
    void drawBoardSDL(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight) const;
};

#endif