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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
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

    SDL_Surface *selectLevelSurface = IMG_Load("selectLevel.png");
    if (!selectLevelSurface)
    {
        std::cerr << "IMG_Load Error (selectLevel.png): " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(startTexture);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture *selectLevelTexture = SDL_CreateTextureFromSurface(renderer, selectLevelSurface);
    SDL_FreeSurface(selectLevelSurface);

    SDL_Surface *gameOverSurface = IMG_Load("game_over.png");
    if (!gameOverSurface)
    {
        std::cerr << "IMG_Load Error (game_over.png): " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(selectLevelTexture);
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

    Mix_Chunk *beepSound = Mix_LoadWAV("beep.mp3");
    if (!beepSound)
    {
        std::cerr << "Mix_LoadWAV Error (beep.wav): " << Mix_GetError() << std::endl;
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(selectLevelTexture);
        SDL_DestroyTexture(gameOverTexture);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_Quit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    Mix_Music *backgroundMusic = Mix_LoadMUS("background_music.mp3");
    if (!backgroundMusic)
    {
        std::cerr << "Mix_LoadMUS Error (background_music.wav): " << Mix_GetError() << std::endl;
        Mix_FreeChunk(beepSound);
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(selectLevelTexture);
        SDL_DestroyTexture(gameOverTexture);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_Quit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    Mix_PlayMusic(backgroundMusic, -1);

    Game *game = nullptr; // Use pointer to initialize later
    std::ifstream inFile("highscore.txt");
    int highscore = 0;
    if (inFile.is_open())
    {
        inFile >> highscore;
        inFile.close();
    }

    bool quit = false;
    bool gameStarted = false;
    bool levelSelected = false; // New state for level selection
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
                        Mix_PlayChannel(-1, beepSound, 0);
                        gameStarted = true;
                    }
                }
                else if (gameStarted && !levelSelected)
                {
                    Difficulty selectedDifficulty = Difficulty::EASY;
                    bool difficultyChosen = false;
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_1:
                        selectedDifficulty = Difficulty::EASY;
                        difficultyChosen = true;
                        Mix_PlayChannel(-1, beepSound, 0);
                        break;
                    case SDLK_2:
                        selectedDifficulty = Difficulty::MEDIUM;
                        difficultyChosen = true;
                        Mix_PlayChannel(-1, beepSound, 0);
                        break;
                    case SDLK_3:
                        selectedDifficulty = Difficulty::HARD;
                        difficultyChosen = true;
                        Mix_PlayChannel(-1, beepSound, 0);
                        break;
                    }
                    if (difficultyChosen)
                    {
                        game = new Game(4, selectedDifficulty);
                        game->highscore = highscore;
                        levelSelected = true;
                    }
                }
                else if (!gameWon && !gameOver)
                {
                    bool moved = false;
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w:
                        moved = game->moveUp();
                        Mix_PlayChannel(-1, beepSound, 0);
                        break;
                    case SDLK_s:
                        moved = game->moveDown();
                        Mix_PlayChannel(-1, beepSound, 0);
                        break;
                    case SDLK_a:
                        moved = game->moveLeft();
                        Mix_PlayChannel(-1, beepSound, 0);
                        break;
                    case SDLK_d:
                        moved = game->moveRight();
                        Mix_PlayChannel(-1, beepSound, 0);
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    }
                    if (moved)
                    {
                        game->board.add_randomTile();
                    }
                }
                else if (event.key.keysym.sym == SDLK_r)
                {
                    // Reset game
                    Mix_PlayChannel(-1, beepSound, 0);
                    Difficulty currentDifficulty = game->difficulty;
                    delete game;
                    game = new Game(4, currentDifficulty);
                    game->highscore = highscore;
                    gameStarted = true;
                    levelSelected = true;
                    gameWon = false;
                    gameOver = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
        SDL_RenderClear(renderer);

        if (!gameStarted)
        {
            SDL_Rect startRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_RenderCopy(renderer, startTexture, nullptr, &startRect);
        }
        else if (gameStarted && !levelSelected)
        {
            SDL_Rect selectLevelRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_RenderCopy(renderer, selectLevelTexture, nullptr, &selectLevelRect);
        }
        else
        {
            game->board.drawBoardSDL(renderer, font, WINDOW_WIDTH, WINDOW_HEIGHT - 100);

            SDL_Color black = {0, 0, 0, 255};
            char scoreText[64];
            snprintf(scoreText, sizeof(scoreText), "Score: %d", game->score);
            drawText(renderer, font, scoreText, 10, WINDOW_HEIGHT - 100, black);
            char highscoreText[64];
            snprintf(highscoreText, sizeof(highscoreText), "Highscore: %d", game->highscore);
            drawText(renderer, font, highscoreText, 10, WINDOW_HEIGHT - 60, black);
            if (game->board.check_Win() && !gameWon)
            {
                gameWon = true;
            }
            if (game->board.check_Gameover() && !gameOver)
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

    std::ofstream outFile("highscore.txt");
    if (outFile.is_open())
    {
        outFile << (game ? game->highscore : highscore);
        outFile.close();
    }

    Mix_FreeChunk(beepSound);
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(selectLevelTexture);
    SDL_DestroyTexture(gameOverTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    delete game;
    return 0;
}