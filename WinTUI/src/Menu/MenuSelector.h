// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: MenuSelector.h
// Date: 14/10/2019

#pragma once
#include <ostream>
#include "Utils/Console.h"
#include "Utils/Keyboard.h"
#include "Utils/Keycodes.h"
#include "Utils/Colour.h"

namespace WinTUI {

    class MenuSelector {
    public:

        MenuSelector()
            : m_MenuOptions(nullptr), m_OptionCount(0) {}

        MenuSelector(const char** menuOptionArray, int optionArraySize)
            : m_MenuOptions(menuOptionArray), m_OptionCount(optionArraySize) {}

        MenuSelector(const MenuSelector& copy) {
            m_OptionCount = copy.m_OptionCount;
            m_MenuOptions = new const char*[m_OptionCount];

            for (int index = 0; index < copy.m_OptionCount; ++index) {
                m_MenuOptions[index] = copy.m_MenuOptions[index];
            }
        }

        ~MenuSelector() {}

        void SetOptions(const char** menuOptionArray, int optionArraySize) {
            m_MenuOptions = menuOptionArray;
            m_OptionCount = optionArraySize;
        }

        inline friend std::ostream& operator<<(std::ostream& ostream, const MenuSelector& menu);

    private:
        const char** m_MenuOptions;
        int m_OptionCount;

    };

    std::ostream& operator<<(std::ostream& ostream, const WinTUI::MenuSelector& menu) {
        bool choosing = true;
        int selectedIndex = 0;

        while (choosing) {
            Console::ClearScreen();

            for (int index = 0; index < menu.m_OptionCount; ++index) {
                if (index == selectedIndex) {
                    Color::SetConsoleColor(WTUI_GOLD, WTUI_LIGHT_BLUE);
                } else {
                    Color::ResetConsoleColor();
                }

                ostream << menu.m_MenuOptions[index];

                Color::ResetConsoleColor();
                ostream << std::endl;

            }

            switch (Keyboard::WaitForKey()) {
            case WTUI_UP_ARROW:
                if ((--selectedIndex) < 0) {
#ifdef WTUI_ALLOW_MENU_LOOP
                    selectedIndex += menu.m_OptionCount;
#else
                    selectedIndex = 0;
#endif
                }
                break;

            case WTUI_DOWN_ARROW:
#ifdef WTUI_ALLOW_MENU_LOOP
                ++selectedIndex %= menu.m_OptionCount;
#else
                if (++selectedIndex >= menu.m_OptionCount) {
                    selectedIndex = menu.m_OptionCount - 1;
                }
#endif
                break;

            case WTUI_RETURN:
            case WTUI_SPACE:
                choosing = false;
                break;

            default:
                break;
            }
        }

        return ostream;
    }

}
