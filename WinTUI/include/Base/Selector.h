// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Selector.h
// Date: 14/10/2019

#pragma once
#include "Base.h"

namespace WinTUI {

    class Selector {
    public:
        virtual ~Selector() = default;

        inline void SetSelectedBefore(const ConfigLambda& lambda) { m_SelectedBefore = lambda; }
        inline void SetSelectedAfter(const ConfigLambda& lambda) { m_SelectedAfter = lambda; }
        inline void SetUnselectedBefore(const ConfigLambda& lambda) { m_UnselectedBefore = lambda; }
        inline void SetUnselectedAfter(const ConfigLambda& lambda) { m_UnselectedAfter = lambda; }

    protected:
        inline void BeforeSelected(std::ostream& ostream) const {
            if (m_SelectedBefore) {
                m_SelectedBefore(ostream);
            }
        }

        inline void AfterSelected(std::ostream& ostream) const {
            if (m_SelectedAfter) {
                m_SelectedAfter(ostream);
            }
        }

        inline void BeforeUnselected(std::ostream& ostream) const {
            if (m_UnselectedBefore) {
                m_UnselectedBefore(ostream);
            }
        }

        inline void AfterUnselected(std::ostream& ostream) const {
            if (m_UnselectedAfter) {
                m_UnselectedAfter(ostream);
            }
        }

    private:
        ConfigLambda m_SelectedBefore = NULL;
        ConfigLambda m_SelectedAfter = NULL;
        ConfigLambda m_UnselectedBefore = NULL;
        ConfigLambda m_UnselectedAfter = NULL;

    };

}
