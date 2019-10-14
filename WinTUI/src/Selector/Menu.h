// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Menu.h
// Date: 14/10/2019

#pragma once
#include "Base/Selector.h"
#include "Utils/Console.h"
#include "Utils/Keyboard.h"
#include "Utils/Keycodes.h"
#include "Utils/Color.h"

namespace WinTUI {

    class Menu : public Selector {
    public:
        Menu()
            : m_MenuOptions(nullptr), m_OptionCount(0), m_LastSelected(-1) {}

        Menu(const char** menuOptionArray, int optionArraySize)
            : m_MenuOptions(menuOptionArray), m_OptionCount(optionArraySize), m_LastSelected(-1) {}

        Menu(const Menu& copy) {
            m_LastSelected = copy.m_LastSelected;
            m_OptionCount = copy.m_OptionCount;
            m_MenuOptions = new const char*[m_OptionCount];

            for (int index = 0; index < copy.m_OptionCount; ++index) {
                m_MenuOptions[index] = copy.m_MenuOptions[index];
            }
        }

        ~Menu() {}

        void SetOptions(const char** menuOptionArray, int optionArraySize) {
            m_MenuOptions = menuOptionArray;
            m_OptionCount = optionArraySize;
        }

        inline int GetLastSelected() { return m_LastSelected; }

        inline friend std::ostream& operator<<(std::ostream& ostream, Menu& menu);

    private:
        const char** m_MenuOptions;
        int m_OptionCount;
        int m_LastSelected;

        inline void PrintOptions(std::ostream& ostream, int selectedIndex) const {
            for (int index = 0; index < m_OptionCount; ++index) {
                if (index == selectedIndex) {
                    if (m_SelectedBefore) {
                        m_SelectedBefore(ostream);
                    }
                    ostream << m_MenuOptions[index];
                    if (m_SelectedAfter) {
                        m_SelectedAfter(ostream);
                    }
                }
                else {
                    if (m_UnselectedBefore) {
                        m_UnselectedBefore(ostream);
                    }
                    ostream << m_MenuOptions[index];
                    if (m_UnselectedAfter) {
                        m_UnselectedAfter(ostream);
                    }
                }

                ostream << std::endl;
            }
        }

        inline bool GetKeyInput(int& selectedIndex) {
            switch (Keyboard::WaitForKey()) {
            case WTUI_RETURN:
            case WTUI_SPACE:
                return false;

            case WTUI_UP_ARROW:
                if ((--selectedIndex) < 0) {
#ifdef WTUI_ALLOW_MENU_LOOP
                    selectedIndex += m_OptionCount;
#else
                    selectedIndex = 0;
#endif
                }
                return true;

            case WTUI_DOWN_ARROW:
#ifdef WTUI_ALLOW_MENU_LOOP
                ++selectedIndex %= m_OptionCount;
#else
                if (++selectedIndex >= m_OptionCount) {
                    selectedIndex = m_OptionCount - 1;
                }
#endif
                return true;

            default:
                return true;
            }
        }

    };

    std::ostream& operator<<(std::ostream& ostream, WinTUI::Menu& menu) {
        bool choosing = true;
        int selectedIndex = 0;

        while (choosing) {
            Console::ClearScreen();

            menu.PrintOptions(ostream, selectedIndex);
            choosing = menu.GetKeyInput(selectedIndex);
        }

        menu.m_LastSelected = selectedIndex;

        return ostream;
    }

}
