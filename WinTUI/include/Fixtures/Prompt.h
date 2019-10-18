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
                isValid = GetResponse(ostream);
                if (!isValid && m_Warning) {
                    m_Warning(ostream);
                }

                AfterFixture(ostream);
            }
        }

        inline void SetCondition(const std::function<bool(const char* response)>& lambda) { m_IsValid = lambda; }

        inline void SetWarning(const std::function<void(std::ostream& warning)>& lambda) { m_Warning = lambda; }

        inline const char* GetLastResponse() { return m_Response.c_str(); }

    private:
        const char* m_Label;
        std::string m_Response;

        std::function<bool(const char* response)> m_IsValid = NULL;
        std::function<void(std::ostream& warning)> m_Warning = NULL;

        void PrintLabel(std::ostream& ostream) {
            BeforeSelected(ostream);
            ostream << m_Label;
            AfterSelected(ostream);
        }

        bool GetResponse(std::ostream& ostream) {
            BeforeUnselected(ostream);

            std::string responseBuffer;
            std::getline(std::cin, responseBuffer, '\n');
            bool success = (!m_IsValid || (m_IsValid(responseBuffer.c_str())));
            if (success) {
                m_Response = responseBuffer;
            }

            AfterUnselected(ostream);

            return success;
        }
    };

}
