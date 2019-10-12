#pragma once
#include <Windows.h>

namespace WinTUI::Keyboard {

    inline unsigned int WaitForKey() {
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        DWORD NumInputs = 0;
        DWORD InputsRead = 0;
        bool running = true;

        INPUT_RECORD irInput;

        GetNumberOfConsoleInputEvents(hInput, &NumInputs);

        ReadConsoleInput(hInput, &irInput, 1, &InputsRead);

        return irInput.Event.KeyEvent.wVirtualKeyCode;
    }

}
