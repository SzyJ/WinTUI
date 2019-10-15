// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Fixture.h
// Date: 15/10/2019

#pragma once
#include <ostream>
#include <functional>

namespace WinTUI {

    class Fixture {
    public:
        virtual ~Fixture() = default;

        inline void SetFixtureBefore(const std::function<void(std::ostream&)>& lambda) { m_FixtureBefore = lambda; }
        inline void SetFixtureAfter(const std::function<void(std::ostream&)>& lambda) { m_FixtureAfter = lambda; }

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
        std::function<void(std::ostream& ostream)> m_FixtureBefore = NULL;
        std::function<void(std::ostream& ostream)> m_FixtureAfter = NULL;

    };

}
