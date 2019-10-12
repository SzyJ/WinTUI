// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: MenuSelector.h
// Date: 11/10/2019

#pragma once
#include <string>

namespace WinTUI {

    class MenuSelector {
    public:

        MenuSelector(std::string menuOptionArray[], unsigned int optionArraySize)
            : m_MenuOptions(menuOptionArray), m_OptionCount(optionArraySize) {}

        ~MenuSelector() {
            delete[] m_MenuOptions;
        }

        unsigned int show(std::ostream& stream);

    private:
        std::string* m_MenuOptions;
        const unsigned int m_OptionCount;
    };

}
