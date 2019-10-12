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


                // If up, decrease indx
                // If down increase indx
                // If Enter, choosing = false
            }
        }

        return selectedIndex;
    }

}
