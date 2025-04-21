#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// Màu ANSI escape
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string CYAN = "\033[36m";
const string YELLOW = "\033[33m";
const string WHITE = "\033[97m";
const string BG_GRAY = "\033[48;5;235m";

int main()
{
    const int size = 4;
    int net[size][size] = {
        {2, 0, 4, 0},
        {0, 8, 0, 2},
        {16, 0, 0, 0},
        {0, 0, 0, 0}};

    const string HORIZ = u8"\u2550"; // ═
    const string VERT = u8"\u2551";  // ║
    const string TOP_LEFT = u8"\u2554", TOP_RIGHT = u8"\u2557";
    const string BOTTOM_LEFT = u8"\u255A", BOTTOM_RIGHT = u8"\u255D";
    const string TOP_T = u8"\u2566", MID_T = u8"\u256C", BOTTOM_T = u8"\u2569";
    const string LEFT_T = u8"\u2560", RIGHT_T = u8"\u2563";

    int cellWidth = 6;

    system("clear");

    cout << CYAN << BOLD << TOP_LEFT;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < cellWidth; j++)
            cout << HORIZ;
        if (i != size - 1)
            cout << TOP_T;
    }
    cout << TOP_RIGHT << RESET << "\n";

    for (int i = 0; i < size; i++)
    {
        cout << CYAN << BOLD << VERT << RESET;
        for (int j = 0; j < size; j++)
        {
            cout << BG_GRAY;
            ostringstream oss;
            oss << right << setw(cellWidth);
            if (net[i][j] == 0)
                oss << ".";
            else
                oss << net[i][j];
            cout << WHITE << oss.str() << RESET;
            cout << CYAN << BOLD << VERT << RESET;
        }
        cout << "\n";

        if (i != size - 1)
        {
            cout << CYAN << BOLD << LEFT_T;
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < cellWidth; k++)
                    cout << HORIZ;
                if (j != size - 1)
                    cout << MID_T;
            }
            cout << RIGHT_T << RESET << "\n";
        }
    }

    cout << CYAN << BOLD << BOTTOM_LEFT;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < cellWidth; j++)
            cout << HORIZ;
        if (i != size - 1)
            cout << BOTTOM_T;
    }
    cout << BOTTOM_RIGHT << RESET << "\n";

    return 0;
}
