// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Menu.h
// Date: 14/10/2019

#pragma once
#include "Base/Selector.h"
#include "Base/Fixture.h"
#include "Utils/Console.h"
#include "Utils/Keyboard.h"
#include "Utils/Keycodes.h"

#include <string>

namespace WinTUI {

    class Menu : public Selector, public Fixture {
    public:
        Menu()
            :m_LastSelected(-1) {
            
        }

        Menu(const char** menuOptionArray, const int optionArraySize)
            :m_LastSelected(-1) {
            InitMenuOptionArray(menuOptionArray, optionArraySize);
        }

        ~Menu() {
            CleanUpMenuOptionArray();
        }

        virtual void Show(std::ostream& ostream) override {
            bool choosing = true;
            int selectedIndex = 0;

            while (choosing) {
                Console::ClearScreen();
                BeforeFixture(ostream);

                PrintOptions(ostream, selectedIndex);
                choosing = GetKeyInput(selectedIndex);

                AfterFixture(ostream);
            }

            m_LastSelected = selectedIndex;
        }

        void SetOptions(const char** menuOptionArray, const int optionArraySize) {
            CleanUpMenuOptionArray();
            InitMenuOptionArray(menuOptionArray, optionArraySize);
        }

        inline int GetLastSelected() { return m_LastSelected; }

    private:
        std::string* m_MenuOptions = nullptr;
        int m_OptionCount;
        int m_LastSelected;

        inline void InitMenuOptionArray(const char** menuOptionArray, const int optionArraySize) {
            m_OptionCount = optionArraySize;
            m_MenuOptions = new std::string[optionArraySize];

            for (int index = 0; index < optionArraySize; ++index) {
                m_MenuOptions[index] = std::string(menuOptionArray[index]);
            }
        }

        inline void CleanUpMenuOptionArray() const {
            if (!m_MenuOptions) {
                return;
            }

            delete[] m_MenuOptions;
        }

        inline void PrintOptions(std::ostream& ostream, int selectedIndex) const {
            for (int index = 0; index < m_OptionCount; ++index) {
                if (index == selectedIndex) {
                    BeforeSelected(ostream);
                    ostream << m_MenuOptions[index];
                    AfterSelected(ostream);
                } else {
                    BeforeUnselected(ostream);
                    ostream << m_MenuOptions[index];
                    AfterUnselected(ostream);
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

}
