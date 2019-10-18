// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Matrix.h
// Date: 18/10/2019

#pragma once
#include "Base/Selector.h"
#include "Base/Fixture.h"
#include "Utils/Console.h"
#include "Utils/Keyboard.h"
#include "Utils/Keycodes.h"
#include "Fixtures/Prompt.h"

#include <iomanip>
#include <cstring>

#define WTUI_EMPTY_CHAR 254

#define WTUI_ROW_SEPERATOR "\n"
#define WTUI_COLUMN_SEPERATOR " "


#define WTUI_POS(x, y) (x + (y * m_Width))

namespace WinTUI {

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Matrix : public Selector, public Fixture {
    public:
        Matrix() = delete;

        Matrix(const int xSize, const int ySize)
            : m_Width(xSize), m_Height(ySize) {
            m_Matrix = new T[m_Width * m_Height];
            std::memset(m_Matrix, 0, sizeof(T) * m_Width * m_Height);
        }

        ~Matrix() {
            delete m_Prompt;
        }

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

        inline void SetCStrConv(std::function<T(const char* str, bool& success)> lambda) { m_ConvFromCStr = lambda; }

        inline void SetWarning(const std::function<void(std::ostream& warning)>& lambda) { m_Warning = lambda; }

        void SetPrompt(Prompt* prompt) { m_Prompt = prompt; }

        T* GetMatrixArray() { return m_Matrix; }

    private:
        const int m_Width, m_Height;

        int m_CellWidth = 1;

        T* m_Matrix;

        Prompt* m_Prompt = nullptr;

        std::function<T(const char* str, bool& success)> m_ConvFromCStr = NULL;

        std::function<void(std::ostream& warning)> m_Warning = NULL;

        void CreateDefaultPrompt() {
            delete m_Prompt;

            m_Prompt = new Prompt("Enter a value");
            m_Prompt->SetSelectedAfter([](std::ostream& ostream) {
                ostream << ": ";
            });
        }

        void PrintCell(std::ostream& ostream, int xPos, int yPos) {
            T cell;
            cell = m_Matrix[WTUI_POS(xPos, yPos)];
            if (cell) {
                ostream << std::setw(m_CellWidth) << cell;
            } else {
                ostream << std::setw(m_CellWidth) << (char) (WTUI_EMPTY_CHAR);
            }
        }

        inline void PrintMatrix(std::ostream& ostream, const int selectedX, const int selectedY) {
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
            if (!m_ConvFromCStr) {
                return NULL;
            }

            if (!m_Prompt) {
                CreateDefaultPrompt();
            }

            bool validVal = false;
            T cellVal;

            while (!validVal) {
                m_Prompt->Show(ostream);

                cellVal = m_ConvFromCStr(m_Prompt->GetLastResponse(), validVal);
                if (!validVal && m_Warning) {
                    m_Warning(ostream);
                }

            }

            int width;
            if ((width = static_cast<int>(std::to_string(cellVal).length())) > m_CellWidth) {
                m_CellWidth = width;
            }

            return cellVal;
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
