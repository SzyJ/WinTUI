// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: App.cpp
// Date: 14/10/2019

#include <iostream>
#include <Fixtures/Menu.h>
#include <Fixtures/Matrix.h>
#include <Fixtures/Prompt.h>
#include "Utils/Keyboard.h"
#include <string>

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

    menu.Show(std::cout);
    std::cout << "Chosen Item: " << array[menu.GetLastSelected()] << std::endl;
}

void BuildMatrix() {
    WinTUI::Matrix<int> matrix(5, 5);

    matrix.SetFixtureBefore([](std::ostream& ostream) {
        ostream << "1. Navigate to desired location with the arrow keys." << std::endl;
        ostream << "2. Press ENTER/SPACE to modify selected cell." << std::endl;
        ostream << "3. Enter the new desired value." << std::endl;
        ostream << "4. Once you are happy with the matrix, press ESC to exit." << std::endl;
        ostream << std::endl;
    });

    matrix.SetSelectedBefore([](std::ostream& ostream) {
        WinTUI::Color::SetConsoleColor(WTUI_DARK_BLUE, WTUI_LIGHT_YELLOW);
        });
    matrix.SetSelectedAfter([](std::ostream& ostream) {
        WinTUI::Color::ResetConsoleColor();
        });

    matrix.SetCStrConv([](const char* str) {
        // TODO: Do some checks
        return std::stoi(str);
     });

    matrix.Show(std::cout);
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

    prompt.Show(std::cout);
    std::cout << prompt.GetLastResponse();

}
