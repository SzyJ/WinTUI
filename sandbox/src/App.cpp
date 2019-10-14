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

    menu.SetSelectedBefore([](std::ostream& ostream) {
        ostream << "-> ";

        WinTUI::Color::SetConsoleColor(WTUI_DARK_BLUE, WTUI_LIGHT_YELLOW);
    });
    menu.SetSelectedAfter([](std::ostream& ostream) {
        WinTUI::Color::ResetConsoleColor();
        ostream << " <-";
    });
    menu.SetUnselectedBefore([](std::ostream& ostream) {
        ostream << "   ";
    });
    menu.SetUnselectedAfter([](std::ostream& ostream) {
        ostream << "   ";
        });

    std::cout << menu;
    std::cout << "Chose: " << array[menu.GetLastSelected()] << std::endl;

    return 0;
}
