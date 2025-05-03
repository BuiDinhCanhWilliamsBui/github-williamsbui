// #include <iostream>
// #include "board.h"
// #include <vector>
// #include <cstdlib>
// #include <ctime>
// #include <iomanip>
// #include <string>
// #include <sstream>
// using namespace std;

// Board::Board(int size) : size(size), net(size, std::vector<int>(size, 0))
// {
//     srand(time(0));
//     add_randomTile();
//     add_randomTile();
// }

// void Board::add_randomTile()
// {
//     vector<pair<int, int>> check;
//     for (int i = 0; i < size; i++)
//     {
//         for (int j = 0; j < size; j++)
//         {
//             if (net[i][j] == 0)
//             {
//                 check.push_back({i, j});
//             }
//         }
//     }
//     if (!check.empty())
//     {
//         std::pair<int, int> cell = check[rand() % check.size()];
//         int a = cell.first, b = cell.second;
//         net[a][b] = (rand() % 2 == 0) ? 2 : 4;
//     }
// }

// bool Board::check_Win() const
// {
//     for (int i = 0; i < size; i++)
//     {
//         for (int j = 0; j < size; j++)
//         {
//             if (net[i][j] == 2048)
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// bool Board::check_Gameover() const
// {
//     for (const auto &row : net)
//     {
//         for (int cell : row)
//         {
//             if (cell == 0)
//             {
//                 return false;
//             }
//         }
//     }
//     for (int i = 0; i < size; i++)
//     {
//         for (int j = 0; j < size; j++)
//         {
//             if ((i < size - 1 && net[i][j] == net[i + 1][j]) ||
//                 (j < size - 1 && net[i][j] == net[i][j + 1]))
//             {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// SDL_Color getColorForValue(int value)
// {
//     switch (value)
//     {
//     case 0:
//         return {205, 193, 180, 255};
//     case 2:
//         return {238, 228, 218, 255};
//     case 4:
//         return {237, 224, 200, 255};
//     case 8:
//         return {242, 177, 121, 255};
//     case 16:
//         return {245, 149, 99, 255};
//     case 32:
//         return {246, 124, 95, 255};
//     case 64:
//         return {246, 94, 59, 255};
//     case 128:
//         return {237, 207, 114, 255};
//     case 256:
//         return {237, 204, 97, 255};
//     case 512:
//         return {237, 200, 80, 255};
//     case 1024:
//         return {237, 197, 63, 255};
//     case 2048:
//         return {237, 194, 46, 255};
//     default:
//         return {60, 58, 50, 255};
//     }
// }

// void Board::drawBoardSDL(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight) const
// {
//     int size = this->size;
//     int margin = 10;
//     int boardSize = std::min(windowWidth, windowHeight) - 2 * margin;
//     int tileSize = (boardSize - (size + 1) * margin) / size;

//     SDL_Color textColor = {119, 110, 101, 255};

//     // Vẽ background bảng
//     SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
//     SDL_Rect boardRect = {margin, margin, boardSize, boardSize};
//     SDL_RenderFillRect(renderer, &boardRect);

//     for (int i = 0; i < size; i++)
//     {
//         for (int j = 0; j < size; j++)
//         {
//             int val = net[i][j];
//             SDL_Color tileColor = getColorForValue(val);
//             SDL_SetRenderDrawColor(renderer, tileColor.r, tileColor.g, tileColor.b, tileColor.a);

//             SDL_Rect tileRect = {
//                 margin + (tileSize + margin) * j + margin,
//                 margin + (tileSize + margin) * i + margin,
//                 tileSize,
//                 tileSize};

//             SDL_RenderFillRect(renderer, &tileRect);

//             if (val != 0)
//             {
//                 std::stringstream ss;
//                 ss << val;
//                 std::string text = ss.str();

//                 SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
//                 SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

//                 int textW = surface->w;
//                 int textH = surface->h;

//                 SDL_FreeSurface(surface);

//                 SDL_Rect dstRect = {
//                     tileRect.x + (tileSize - textW) / 2,
//                     tileRect.y + (tileSize - textH) / 2,
//                     textW,
//                     textH};

//                 SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
//                 SDL_DestroyTexture(texture);
//             }
//         }
//     }
// }
#include <iostream>
#include "board.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

Board::Board(int size) : size(size), net(size, std::vector<int>(size, 0))
{
    srand(time(0));
    add_randomTile();
    add_randomTile();
}

void Board::add_randomTile()
{
    vector<pair<int, int>> check;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (net[i][j] == 0)
            {
                check.push_back({i, j});
            }
        }
    }
    if (!check.empty())
    {
        std::pair<int, int> cell = check[rand() % check.size()];
        int a = cell.first, b = cell.second;
        net[a][b] = (rand() % 2 == 0) ? 2 : 4;
    }
}

bool Board::check_Win() const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (net[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::check_Gameover() const
{
    for (const auto &row : net)
    {
        for (int cell : row)
        {
            if (cell == 0)
            {
                return false;
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((i < size - 1 && net[i][j] == net[i + 1][j]) ||
                (j < size - 1 && net[i][j] == net[i][j + 1]))
            {
                return false;
            }
        }
    }
    return true;
}

SDL_Color getColorForValue(int value)
{
    switch (value)
    {
    case 0:
        return {205, 193, 180, 255};
    case 2:
        return {238, 228, 218, 255};
    case 4:
        return {237, 224, 200, 255};
    case 8:
        return {242, 177, 121, 255};
    case 16:
        return {245, 149, 99, 255};
    case 32:
        return {246, 124, 95, 255};
    case 64:
        return {246, 94, 59, 255};
    case 128:
        return {237, 207, 114, 255};
    case 256:
        return {237, 204, 97, 255};
    case 512:
        return {237, 200, 80, 255};
    case 1024:
        return {237, 197, 63, 255};
    case 2048:
        return {237, 194, 46, 255};
    default:
        return {60, 58, 50, 255};
    }
}

void Board::drawBoardSDL(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight) const
{
    int size = this->size;
    int margin = 10;
    // Tính kích thước bảng sao cho vừa với cửa sổ và căn giữa
    int availableWidth = windowWidth - 2 * margin;
    int availableHeight = windowHeight - 2 * margin;
    int boardSize = std::min(availableWidth, availableHeight);
    int tileSize = (boardSize - (size + 1) * margin) / size;

    // Căn giữa bảng
    int boardX = (windowWidth - boardSize) / 2;
    int boardY = (windowHeight - boardSize) / 2;

    SDL_Color textColor = {119, 110, 101, 255};

    // Vẽ background bảng
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_Rect boardRect = {boardX, boardY, boardSize, boardSize};
    SDL_RenderFillRect(renderer, &boardRect);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int val = net[i][j];
            SDL_Color tileColor = getColorForValue(val);
            SDL_SetRenderDrawColor(renderer, tileColor.r, tileColor.g, tileColor.b, tileColor.a);

            SDL_Rect tileRect = {
                boardX + margin + (tileSize + margin) * j,
                boardY + margin + (tileSize + margin) * i,
                tileSize,
                tileSize};

            SDL_RenderFillRect(renderer, &tileRect);

            if (val != 0)
            {
                std::stringstream ss;
                ss << val;
                std::string text = ss.str();

                // Điều chỉnh kích thước font dựa trên kích thước ô
                int fontSize = tileSize / 3;
                TTF_SetFontSize(font, fontSize);

                SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
                if (!surface)
                {
                    std::cerr << "TTF_RenderText_Blended error: " << TTF_GetError() << std::endl;
                    continue;
                }
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

                int textW = surface->w;
                int textH = surface->h;

                SDL_FreeSurface(surface);

                SDL_Rect dstRect = {
                    tileRect.x + (tileSize - textW) / 2,
                    tileRect.y + (tileSize - textH) / 2,
                    textW,
                    textH};

                SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
                SDL_DestroyTexture(texture);
            }
        }
    }
}