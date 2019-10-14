// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Selector.h
// Date: 14/10/2019

#pragma once
#include <ostream>
#include <functional>

namespace WinTUI {

    class Selector {
    public:
        virtual ~Selector() = default;

        inline void SetSelectedBefore(const std::function<void(std::ostream&)>& lambda) { m_SelectedBefore = lambda; }
        inline void SetSelectedAfter(const std::function<void(std::ostream&)>& lambda) { m_SelectedAfter = lambda; }
        inline void SetUnselectedBefore(const std::function<void(std::ostream&)>& lambda) { m_UnselectedBefore = lambda; }
        inline void SetUnselectedAfter(const std::function<void(std::ostream&)>& lambda) { m_UnselectedAfter = lambda; }

    protected:
        std::function<void(std::ostream& ostream)> m_SelectedBefore = NULL;
        std::function<void(std::ostream& ostream)> m_SelectedAfter = NULL;
        std::function<void(std::ostream& ostream)> m_UnselectedBefore = NULL;
        std::function<void(std::ostream& ostream)> m_UnselectedAfter = NULL;

    };

}
