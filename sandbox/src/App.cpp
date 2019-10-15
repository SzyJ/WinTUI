// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: App.cpp
// Date: 14/10/2019

#include <iostream>
#include <Selector/Menu.h>
#include <Builder/Matrix.h>
#include <Selector/Prompt.h>
#include "Utils/Keyboard.h"

void ShowMenu();
void BuildMatrix();
void ShowPrompt();

int main() {

    //std::cout << WinTUI::Keyboard::WaitForKey() << std::endl;
    //ShowMenu();
    //BuildMatrix();
    ShowPrompt();

    return 0;
}

void ShowMenu() {
    const char* array[] = {
    "First entry",
    "Second entry",
    "Third entry"
    };

    WinTUI::Menu menu(array, 3);

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
    std::cout << "Chosen Item: " << array[menu.GetLastSelected()] << std::endl;
}

void BuildMatrix() {
    WinTUI::Matrix<int> matrix(5, 5);

    matrix.SetSelectedBefore([](std::ostream& ostream) {
        WinTUI::Color::SetConsoleColor(WTUI_DARK_BLUE, WTUI_LIGHT_YELLOW);
        });
    matrix.SetSelectedAfter([](std::ostream& ostream) {
        WinTUI::Color::ResetConsoleColor();
        });

    std::cout << matrix;
}

void ShowPrompt() {
    WinTUI::Prompt prompt("Type something");

    prompt.SetSelectedBefore([](std::ostream& ostream) {
        WinTUI::Color::SetConsoleColor(WTUI_LIGHT_GREEN, WTUI_DARK_GRAY);
        });
    prompt.SetSelectedAfter([](std::ostream& ostream) {
        WinTUI::Color::ResetConsoleColor();
        ostream << ": ";
        });

    std::cout << prompt;

    std::cout << prompt.GetLastResponse();

}
