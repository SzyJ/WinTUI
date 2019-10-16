// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Prompt.h
// Date: 15/10/2019

#pragma once

#include "Base/Selector.h"
#include "Base/Fixture.h"
#include <iostream>
#include <functional>
#include <string>

namespace WinTUI {

    class Prompt : public Selector, public Fixture {
    public:
        Prompt() {}

        Prompt(const char* label)
            : m_Label(label) {}

        ~Prompt() {}

        virtual void Show(std::ostream& ostream) override {
            bool isValid = false;

            while (!isValid) {
                BeforeFixture(ostream);
                PrintLabel(ostream);
                GetResponse(ostream);
                AfterFixture(ostream);
                isValid = true;
            }
        }

        inline void SetCondition(const std::function<bool(const char* response)>& lambda) { m_IsValid = lambda; }

        inline const char* GetLastResponse() { return m_Response.c_str(); }

    private:
        const char* m_Label;
        std::string m_Response;

        std::function<bool(const char* response)> m_IsValid = NULL;

        void PrintLabel(std::ostream& ostream) {
            BeforeSelected(ostream);
            ostream << m_Label;
            AfterSelected(ostream);
        }

        void GetResponse(std::ostream& ostream) {
            BeforeUnselected(ostream);
            std::getline(std::cin, m_Response, '\n');
            AfterUnselected(ostream);
        }

    };

}
