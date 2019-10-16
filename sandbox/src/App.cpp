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
#include <cctype>

void ShowMenu();
void BuildMatrix();
void ShowPrompt();

int main() {
    //std::cout << WinTUI::Keyboard::WaitForKey() << std::endl;
    //ShowMenu();
    BuildMatrix();
    //ShowPrompt();

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

    auto before = [](std::ostream& ostream) {
        WinTUI::Color::SetConsoleColor(WTUI_DARK_BLUE, WTUI_LIGHT_YELLOW);
    };
    auto after = [](std::ostream& ostream) {
        WinTUI::Color::ResetConsoleColor();
    };

    matrix.SetSelectedBefore(before);
    matrix.SetSelectedAfter(after);
    const int maxValue = 20;
    const int minValue = 0;

    matrix.SetCStrConv([maxValue, minValue](const char* str, bool& success) {
        try {
            auto value = std::stoi(str);
             success = value >= minValue && value <= maxValue;
            return value;
        } catch (const std::invalid_argument) {
            success = false;
            return -1;
        } catch (const std::out_of_range) {
            success = false;
            return -2;
        } catch (const std::exception) {
            success = false;
            return -3;
        }
     });

    matrix.SetWarning([](std::ostream& ostream) {
        WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
        ostream << "Enter a positive number between 0 and 20" << std::endl;
        });

    WinTUI::Prompt* numberInput = new WinTUI::Prompt("Enter a number between 0 and 20");

    numberInput->SetSelectedBefore(before);
    numberInput->SetSelectedAfter([](std::ostream& ostream) {
        WinTUI::Color::ResetConsoleColor();
        ostream << ": ";
        });
    numberInput->SetCondition([](const char* string) {
        char thisChar;

         for (int cIndex = 0; (thisChar = string[cIndex]) != '\0'; ++cIndex) {
            if (!std::isdigit(thisChar)) {
                return false;
            }

            if (cIndex > 1) {
                return false;
            }
        }

        return true;
        });
    numberInput->SetWarning([](std::ostream& ostream) {
        WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
        ostream << "Only enter number characters" << std::endl;
        });

    matrix.SetPrompt(numberInput);

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

    prompt.SetCondition([](const char* str) {
        return str[0] == 'a';
        });
    prompt.SetWarning([](std::ostream& ostream) {
        WinTUI::Color::SetConsoleColor(WTUI_WHITE, WTUI_RED);
        ostream << "Please enter a value starting with 'a'" << std::endl;
        });

    prompt.Show(std::cout);
    std::cout << prompt.GetLastResponse();

}
