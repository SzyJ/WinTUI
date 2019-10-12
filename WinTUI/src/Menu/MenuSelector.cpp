// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: MenuSelector.cpp
// Date: 11/10/2019

#include "MenuSelector.h"
#include "Utils/Keyboard.h"
#include "Utils/KeyCodes.h"

namespace WinTUI {

    unsigned int MenuSelector::show(std::ostream& stream) {
        bool choosing = true;
        int selectedIndex = 0;

        while (choosing) {
            // Clear screen

            for (int index = 0; index < m_OptionCount; ++index) {
                if (index == selectedIndex) {
                    // Change colour
                }
                else {
                    // Reset colour
                }

                stream << m_MenuOptions[index];

                // ResetColour
                stream << std::endl;

            }

            switch (Keyboard::WaitForKey()) {
            case WTUI_UP_ARROW:
                if ((--selectedIndex) < 0) {
#ifdef WTUI_ALLOW_MENU_LOOP
                    selectedIndex += m_OptionCount;
#else
                    selectedIndex = 0;
#endif
                }
                break;

            case WTUI_DOWN_ARROW:
#ifdef WTUI_ALLOW_MENU_LOOP
                ++selectedIndex %= m_OptionCount;
#else
                if (++selectedIndex >= m_OptionCount) {
                    selectedIndex = m_OptionCount - 1;
                }
#endif
                break;

            case WTUI_RETURN:
                choosing = false;
                break;

            default:
                break;
            }
        }

        return selectedIndex;
    }

}
