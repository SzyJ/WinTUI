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

#define CONS_COLOR(FG, BG) (FG + (BG * 16))

namespace WinTIO::Color {

    inline void SetConsoleColor(HANDLE stdHandle, int foreground = COL_WHITE, int background = 0) {
        SetConsoleTextAttribute(stdHandle, CONS_COLOR(foreground, background));
    }

    inline void SetConsoleColor(int foreground = COL_WHITE, int background = 0) {
        SetConsoleColor(GetStdHandle(STD_OUTPUT_HANDLE), foreground, background);
    }

    inline void ResetConsoleColor() {
        SetConsoleColor();
    }

}
