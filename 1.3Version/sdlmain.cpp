#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "game.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 700;

void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
    if (!surface)
    {
        std::cerr << "TTF_RenderText_Blended error: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("Arial.ttf", 36);
    if (!font)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    Game game(4);
    bool quit = false;
    bool gameStarted = false;
    bool gameWon = false;
    bool gameOver = false;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (!gameStarted)
                {
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        gameStarted = true;
                    }
                }
                else if (!gameWon && !gameOver)
                {
                    bool moved = false;
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        moved = game.moveUp();
                        break;
                    case SDLK_s:
                        moved = game.moveDown();
                        break;
                    case SDLK_a:
                        moved = game.moveLeft();
                        break;
                    case SDLK_d:
                        moved = game.moveRight();
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    }
                    if (moved)
                    {
                        game.board.add_randomTile();
                    }
                }
                else if (event.key.keysym.sym == SDLK_r)
                {
                    // Reset game
                    game = Game(4);
                    gameStarted = true;
                    gameWon = false;
                    gameOver = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
        SDL_RenderClear(renderer);

        if (!gameStarted)
        {
            SDL_Color white = {255, 255, 255, 255};
            drawText(renderer, font, "2048 Game", WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 50, white);
            drawText(renderer, font, "Press Enter to Start", WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2 + 10, white);
        }
        else
        {
            game.board.drawBoardSDL(renderer, font, WINDOW_WIDTH, WINDOW_HEIGHT - 100);

            SDL_Color black = {0, 0, 0, 255};
            char scoreText[64];
            snprintf(scoreText, sizeof(scoreText), "Score: %d", game.score);
            drawText(renderer, font, scoreText, 10, WINDOW_HEIGHT - 80, black);

            if (game.board.check_Win() && !gameWon)
            {
                gameWon = true;
            }
            if (game.board.check_Gameover() && !gameOver)
            {
                gameOver = true;
            }

            if (gameWon)
            {
                SDL_Color white = {255, 255, 255, 255};
                drawText(renderer, font, "You Win!", WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 - 20, white);
                drawText(renderer, font, "Press R to Restart", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 20, white);
            }
            else if (gameOver)
            {
                SDL_Color white = {255, 255, 255, 255};
                drawText(renderer, font, "Game Over!", WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 20, white);
                drawText(renderer, font, "Press R to Restart", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 20, white);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}