// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Colour.h
// Date: 14/10/2019

#pragma once
#include <Windows.h>

#define WTUI_BLACK 0
#define WTUI_DARK_BLUE 1
#define WTUI_DARK_GREEN 2
#define WTUI_LIGHT_BLUE 3
#define WTUI_RED 4
#define WTUI_PURPLE 5
#define WTUI_GOLD 6
#define WTUI_LIGHT_GRAY 7
#define WTUI_DARK_GRAY 8
#define WTUI_BLUE 9
#define WTUI_LIGHT_GREEN 10
#define WTUI_CYAN 11
#define WTUI_SALMON 12
#define WTUI_PINK 13
#define WTUI_LIGHT_YELLOW 14
#define WTUI_WHITE 15

#define WTUI_CONS_COLOR(FG, BG) (FG + (BG * 16))

namespace WinTUI::Color {

    inline void SetConsoleColor(HANDLE stdHandle, int foreground = WTUI_WHITE, int background = WTUI_BLACK) {
        SetConsoleTextAttribute(stdHandle, WTUI_CONS_COLOR(foreground, background));
    }

    inline void SetConsoleColor(int foreground = WTUI_WHITE, int background = WTUI_BLACK) {
        SetConsoleColor(GetStdHandle(STD_OUTPUT_HANDLE), foreground, background);
    }

    inline void ResetConsoleColor() {
        SetConsoleColor();
    }

}
