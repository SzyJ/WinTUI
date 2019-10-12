#include <iostream>
#include <Utils/Keyboard.h>

int main() {

    std::cout << "Hello";

    unsigned int keycode = WinTUI::Keyboard::WaitForKey();

    std::cout << " World: " << keycode << std::endl;

    return 0;
}
