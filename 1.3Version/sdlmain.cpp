#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "game.h"
#include <fstream>
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
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
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
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Load hình ảnh cho màn hình bắt đầu và game over
    SDL_Surface *startSurface = IMG_Load("start_screen.png");
    if (!startSurface)
    {
        std::cerr << "IMG_Load Error (start_screen.png): " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture *startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
    SDL_FreeSurface(startSurface);

    SDL_Surface *gameOverSurface = IMG_Load("game_over.png");
    if (!gameOverSurface)
    {
        std::cerr << "IMG_Load Error (game_over.png): " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(startTexture);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    SDL_FreeSurface(gameOverSurface);

    Game game(4);
    // đọc từ file highscore.txt
    std::ifstream inFile("highscore.txt");
    if (inFile.is_open())
    {
        inFile >> game.highscore;
        inFile.close();
    }
    else
    {
        game.highscore = 0; // Giá trị mặc định nếu file không tồn tại
    }
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
            // Hiển thị hình ảnh màn hình bắt đầu
            SDL_Rect startRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_RenderCopy(renderer, startTexture, nullptr, &startRect);
        }
        else
        {
            game.board.drawBoardSDL(renderer, font, WINDOW_WIDTH, WINDOW_HEIGHT - 100);

            SDL_Color black = {0, 0, 0, 255};
            char scoreText[64];
            snprintf(scoreText, sizeof(scoreText), "Score: %d", game.score);
            drawText(renderer, font, scoreText, 10, WINDOW_HEIGHT - 80, black);
            char highscoreText[64];
            snprintf(highscoreText, sizeof(highscoreText), "Highscore: %d", game.highscore);
            drawText(renderer, font, highscoreText, 10, WINDOW_HEIGHT - 40, black); // update vẽ highscore
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
                // Hiển thị hình ảnh game over
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
                SDL_Rect overlay = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
                SDL_RenderFillRect(renderer, &overlay);

                SDL_Rect gameOverRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
                SDL_RenderCopy(renderer, gameOverTexture, nullptr, &gameOverRect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    // Thêm đoạn ghi highscore vào file ngay trước khi cleanup
    std::ofstream outFile("highscore.txt");
    if (outFile.is_open())
    {
        outFile << game.highscore;
        outFile.close();
    }
    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(gameOverTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}