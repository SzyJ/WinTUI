// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Prompt.h
// Date: 15/10/2019

#pragma once

#include "Base/Selector.h"
#include <iostream>
#include <functional>
#include <string>

namespace WinTUI {

    class Prompt : public Selector {
    public:
        Prompt() {}

        Prompt(const char* label)
            : m_Label(label) {}

        ~Prompt() {}

        inline void SetCondition(const std::function<bool(const char* response)>& lambda) { m_IsValid = lambda; }

        inline const char* GetLastResponse() { return m_Response.c_str(); }

        inline friend std::ostream& operator<<(std::ostream& ostream, Prompt& prompt);

    private:
        const char* m_Label;
        std::string m_Response;

        std::function<bool(const char* response)> m_IsValid = NULL;

        void PrintLabel(std::ostream& ostream) {
            if (m_SelectedBefore) {
                m_SelectedBefore(ostream);
            }

            ostream << m_Label;

            if (m_SelectedAfter) {
                m_SelectedAfter(ostream);
            }
        }

        void GetRepsonse(std::ostream& ostream) {
            if (m_UnselectedBefore) {
                m_UnselectedBefore(ostream);
            }

            std::getline(std::cin, m_Response, '\n');
            //std::cin >> m_Response;

            if (m_UnselectedAfter) {
                m_UnselectedAfter(ostream);
            }
        }

    };

    std::ostream& operator<<(std::ostream& ostream, Prompt& prompt) {
        bool isValid = false;

        while (!isValid) {
            prompt.PrintLabel(ostream);
            prompt.GetRepsonse(ostream);
            isValid = true;
        }

        return ostream;
    }

}
