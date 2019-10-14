// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Keyboard.h
// Date: 14/10/2019

#pragma once
#include <Windows.h>
#include <conio.h>

#define WTUI_ARROW_KEYS 224

namespace WinTUI::Keyboard {

    inline unsigned int WaitForKey() {
        int test = _getch();
        if (test != WTUI_ARROW_KEYS) {
            return test;
        }

        test = _getch();
        return test;
    }

}
