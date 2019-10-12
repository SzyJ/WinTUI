#pragma once
#include <Windows.h>

#define COL_BLACK 0
#define COL_DARK_BLUE 1
#define COL_DARK_GREEN 2
#define COL_LIGHT_BLUE 3
#define COL_RED 4
#define COL_PURPLE 5
#define COL_GOLD 6
#define COL_LIGHT_GRAY 7
#define COL_DARK_GRAY 8
#define COL_BLUE 9
#define COL_LIGHT_GREEN 10
#define COL_CYAN 11
#define COL_SALMON 12
#define COL_PINK 13
#define COL_LIGHT_YELLOW 14
#define COL_WHITE 15

#define CONS_COLOUR(FG, BG) (FG + (BG * 16))

namespace WinTUI {

    class Console {
        static void SetConsoleColour(HANDLE stdHandle, unsigned int foreground, unsigned int background) {
            SetConsoleTextAttribute(stdHandle, CONS_COLOUR(foreground, background));
        }

        static void SetConsoleColour(unsigned int foreground, unsigned int background) {
            SetConsoleColour(GetStdHandle(STD_OUTPUT_HANDLE), foreground, background);
        }

        static void SetConsoleColour(unsigned int foreground) {
            SetConsoleColour(foreground, 0);
        }

        static void ResetConsoleColour() {
            SetConsoleColour(COL_WHITE);
        }

        static void ClearScreen()
        {
            HANDLE                     hStdOut;
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            DWORD                      count;
            DWORD                      cellCount;
            COORD                      homeCoords = { 0, 0 };

            hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hStdOut == INVALID_HANDLE_VALUE) return;

            /* Get the number of cells in the current buffer */
            if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
            cellCount = csbi.dwSize.X * csbi.dwSize.Y;

            /* Fill the entire buffer with spaces */
            if (!FillConsoleOutputCharacter(
                hStdOut,
                (TCHAR)' ',
                cellCount,
                homeCoords,
                &count
            )) return;

            /* Fill the entire buffer with the current colors and attributes */
            if (!FillConsoleOutputAttribute(
                hStdOut,
                csbi.wAttributes,
                cellCount,
                homeCoords,
                &count
            )) return;

            /* Move the cursor home */
            SetConsoleCursorPosition(hStdOut, homeCoords);
        }

    };

}
