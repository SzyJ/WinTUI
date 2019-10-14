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

    std::cout << "Hello";

    unsigned int keycode = WinTUI::Keyboard::WaitForKey();

    std::cout << " World: " << keycode << std::endl;

    const char* array[] = {
        "First entry",
        "Second entry",
        "Third entry"
    };

    WinTUI::MenuSelector menu(array, 3);
    std::cout << menu;
    std::cout << "Chose: " << array[menu.GetLastSelected()] << std::endl;

    return 0;
}
