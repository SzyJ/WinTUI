// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Matrix.h
// Date: 14/10/2019

#pragma once
#include "Base/Selector.h"
#include "Base/Fixture.h"
#include "Utils/Console.h"
#include "Utils/Keyboard.h"
#include "Utils/Keycodes.h"
#include "Fixtures/Prompt.h"

#include <cstring>

#define WTUI_EMPTY_CHAR 254

#define WTUI_ROW_SEPERATOR "\n"
#define WTUI_COLUMN_SEPERATOR " "


#define WTUI_POS(x, y) (x + (y * m_Width))

namespace WinTUI {

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Matrix : public Selector, public Fixture {
    public:
        Matrix();

        Matrix(const int xSize, const int ySize)
            : m_Width(xSize), m_Height(ySize) {
            m_Matrix = new T[m_Width * m_Height];
            std::memset(m_Matrix, 0, sizeof(T) * m_Width * m_Height);
        }

        ~Matrix() {}

        virtual void Show(std::ostream& ostream) override {
            bool choosing = true;
            int selectedX = 0;
            int selectedY = 0;

            while (choosing) {
                Console::ClearScreen();
                BeforeFixture(ostream);

                PrintMatrix(ostream, selectedX, selectedY);
                choosing = GetKeyInput(ostream, selectedX, selectedY);

                AfterFixture(ostream);
            }
        }

        void SetCStrConv(std::function<T(const char*)> lambda) { m_ConvFromCStr = lambda; }

    private:
        int m_Width, m_Height, m_CellWidth = 1;
        T* m_Matrix;
        std::function<T(const char*)> m_ConvFromCStr;

        void PrintCell(std::ostream& ostream, int xPos, int yPos) {
            T cell;
            cell = m_Matrix[WTUI_POS(xPos, yPos)];
            if (cell) {
                ostream << cell;
            } else {
                ostream << (char)(WTUI_EMPTY_CHAR);
            }
        }

        void PrintMatrix(std::ostream& ostream, const int selectedX, const int selectedY) {
            for (int yPos = 0; yPos < m_Height; ++yPos) {
                for (int xPos = 0; xPos < m_Width; ++xPos) {
                    if (selectedX == xPos && selectedY == yPos) {
                        BeforeSelected(ostream);
                        PrintCell(ostream, xPos, yPos);
                        AfterSelected(ostream);
                    } else {
                        BeforeUnselected(ostream);
                        PrintCell(ostream, xPos, yPos);
                        AfterUnselected(ostream);
                    }

                    ostream << WTUI_COLUMN_SEPERATOR;
                }
                ostream << WTUI_ROW_SEPERATOR;
            }
        }

        inline T GetUserInput(std::ostream& ostream) {
            Prompt input("Enter a number");
            input.SetSelectedBefore([](std::ostream& ostream) {
                WinTUI::Color::SetConsoleColor(WTUI_DARK_BLUE, WTUI_LIGHT_YELLOW);
            });
            input.SetSelectedAfter([](std::ostream& ostream) {
                Color::ResetConsoleColor();
                ostream << ": ";
            });

            input.Show(ostream);

            if (m_ConvFromCStr) {
                return m_ConvFromCStr(input.GetLastResponse());
            }

            return (T) (input.GetLastResponse());
        }

        inline bool GetKeyInput(std::ostream& ostream, int& selectedX, int& selectedY) {
            switch (Keyboard::WaitForKey()) {
            case WTUI_ESCAPE:

                return false;

            case WTUI_RETURN:
            case WTUI_SPACE:
                m_Matrix[WTUI_POS(selectedX, selectedY)] = GetUserInput(ostream);
                return true;

            case WTUI_UP_ARROW:
                if ((--selectedY) < 0) {
                    selectedY = 0;
                }
                return true;

            case WTUI_DOWN_ARROW:
                if (++selectedY >= m_Height) {
                    selectedY = m_Height - 1;
                }
                return true;

            case WTUI_RIGHT_ARROW:
                if (++selectedX >= m_Width) {
                    selectedX = m_Width - 1;
                }
                return true;

            case WTUI_LEFT_ARROW:
                if ((--selectedX) < 0) {
                    selectedX = 0;
                }
                return true;

            default:
                return true;
            }
        }
    };

}
