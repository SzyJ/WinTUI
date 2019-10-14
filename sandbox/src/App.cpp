// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: App.cpp
// Date: 14/10/2019

#include <iostream>
#include <Utils/Keyboard.h>
#include <Menu/MenuSelector.h>

void Test(std::ostream& stream);

int main() {
    const char* array[] = {
        "First entry",
        "Second entry",
        "Third entry"
    };

    WinTUI::MenuSelector menu(array, 3);

    menu.SetSelectedBefore([]() {
        WinTUI::Color::SetConsoleColor(WTUI_DARK_BLUE, WTUI_LIGHT_YELLOW);
    });
    menu.SetSelectedAfter([]() {
        WinTUI::Color::ResetConsoleColor();
    });

    std::cout << menu;
    std::cout << "Chose: " << array[menu.GetLastSelected()] << std::endl;

    return 0;
}
