// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: MenuSelector.h
// Date: 14/10/2019

#pragma once
#include <ostream>
#include <functional>
#include "Utils/Console.h"
#include "Utils/Keyboard.h"
#include "Utils/Keycodes.h"
#include "Utils/Color.h"

namespace WinTUI {

    class MenuSelector {
    public:
        MenuSelector()
            : m_MenuOptions(nullptr), m_OptionCount(0), m_LastSelected(-1) {}

        MenuSelector(const char** menuOptionArray, int optionArraySize)
            : m_MenuOptions(menuOptionArray), m_OptionCount(optionArraySize), m_LastSelected(-1) {}

        MenuSelector(const MenuSelector& copy) {
            m_LastSelected = copy.m_LastSelected;
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

        inline int GetLastSelected() { return m_LastSelected; }

        inline void SetSelectedBefore(const std::function<void(void)>& lambda) { m_SelectedBefore = lambda; }
        inline void SetSelectedAfter(const std::function<void(void)>& lambda) { m_SelectedAfter = lambda; }
        inline void SetUnselectedBefore(const std::function<void(void)>& lambda) { m_UnselectedBefore = lambda; }
        inline void SetUnselectedAfter(const std::function<void(void)>& lambda) { m_UnselectedAfter = lambda; }

        inline friend std::ostream& operator<<(std::ostream& ostream, MenuSelector& menu);

    private:
        const char** m_MenuOptions;
        int m_OptionCount;
        int m_LastSelected;

        std::function<void(void)> m_SelectedBefore;
        std::function<void(void)> m_SelectedAfter;
        std::function<void(void)> m_UnselectedBefore;
        std::function<void(void)> m_UnselectedAfter;

    };

    std::ostream& operator<<(std::ostream& ostream, WinTUI::MenuSelector& menu) {
        bool choosing = true;
        int selectedIndex = 0;

        while (choosing) {
            Console::ClearScreen();

            for (int index = 0; index < menu.m_OptionCount; ++index) {
                if (index == selectedIndex) {
                    if (menu.m_SelectedBefore) {
                        menu.m_SelectedBefore();
                    }
                    ostream << menu.m_MenuOptions[index];
                    if (menu.m_SelectedAfter) {
                        menu.m_SelectedAfter();
                    }
                } else {
                    if (menu.m_UnselectedBefore) {
                        menu.m_UnselectedBefore();
                    }
                    ostream << menu.m_MenuOptions[index];
                    if (menu.m_UnselectedAfter) {
                        menu.m_UnselectedAfter();
                    }
                }

                ostream << std::endl;

            }
            int c = Keyboard::WaitForKey();
            switch (c) {
            case WTUI_RETURN:
            case WTUI_SPACE:
                choosing = false;
                break;

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

            default:
                break;
            }
        }

        menu.m_LastSelected = selectedIndex;

        return ostream;
    }

}
