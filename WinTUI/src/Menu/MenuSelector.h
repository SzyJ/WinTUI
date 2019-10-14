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

        inline void SetSelectedBefore(const std::function<void(std::ostream&)>& lambda) { m_SelectedBefore = lambda; }
        inline void SetSelectedAfter(const std::function<void(std::ostream&)>& lambda) { m_SelectedAfter = lambda; }
        inline void SetUnselectedBefore(const std::function<void(std::ostream&)>& lambda) { m_UnselectedBefore = lambda; }
        inline void SetUnselectedAfter(const std::function<void(std::ostream&)>& lambda) { m_UnselectedAfter = lambda; }

        inline friend std::ostream& operator<<(std::ostream& ostream, MenuSelector& menu);

    private:
        const char** m_MenuOptions;
        int m_OptionCount;
        int m_LastSelected;

        std::function<void(std::ostream& ostream)> m_SelectedBefore = NULL;
        std::function<void(std::ostream& ostream)> m_SelectedAfter = NULL;
        std::function<void(std::ostream& ostream)> m_UnselectedBefore = NULL;
        std::function<void(std::ostream& ostream)> m_UnselectedAfter = NULL;

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

    };

    std::ostream& operator<<(std::ostream& ostream, WinTUI::MenuSelector& menu) {
        bool choosing = true;
        int selectedIndex = 0;

        while (choosing) {
            Console::ClearScreen();

            menu.PrintOptions(ostream, selectedIndex);
            
            switch (Keyboard::WaitForKey()) {
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
