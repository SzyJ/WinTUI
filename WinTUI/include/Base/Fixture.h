// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Fixture.h
// Date: 15/10/2019

#pragma once
#include "Base.h"

namespace WinTUI {

    class Fixture {
    public:
        virtual ~Fixture() = default;

        inline void SetFixtureBefore(const ConfigLambda& lambda) { m_FixtureBefore = lambda; }
        inline void SetFixtureAfter(const ConfigLambda& lambda) { m_FixtureAfter = lambda; }

        virtual void Show(std::ostream& ostream) = 0;

    protected:
        inline void BeforeFixture(std::ostream& ostream) const {
            if (m_FixtureBefore) {
                m_FixtureBefore(ostream);
            }
        }

        inline void AfterFixture(std::ostream& ostream) const {
            if (m_FixtureAfter) {
                m_FixtureAfter(ostream);
            }
        }

    private:
        ConfigLambda m_FixtureBefore = NULL;
        ConfigLambda m_FixtureAfter = NULL;

    };

}
