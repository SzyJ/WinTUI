// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Keyboard.h
// Date: 14/10/2019

#pragma once
#include <conio.h>

#define WTUI_ARROW_KEYS 224

namespace WinTUI::Keyboard {

    inline unsigned int WaitForKey() {
        int keycode = _getch();
        if (keycode != WTUI_ARROW_KEYS) {
            return keycode;
        }

        keycode = _getch();
        return keycode;
    }

}
