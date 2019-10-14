// Author: Szymon Jackiewicz
// 
// Project: WinTUI
// File: Matrix.h
// Date: 14/10/2019

#pragma once
#include "Base/Selector.h"
#include "Utils/Console.h"
#include "Utils/Keyboard.h"
#include "Utils/Keycodes.h"
#include <cstring>

#define WTUI_EMPTY_CHAR 254

#define WTUI_ROW_SEPERATOR "\n"
#define WTUI_COLUMN_SEPERATOR " "


#define WTUI_POS(x, y) (x + (y * m_Width))

namespace WinTUI {

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Matrix : public Selector {
    public:
        Matrix();

        Matrix(const int xSize, const int ySize)
            : m_Width(xSize), m_Height(ySize) {
            m_Matrix = new T[m_Width * m_Height];
            std::memset(m_Matrix, 0, sizeof(T) * m_Width * m_Height);
        }

        ~Matrix() {}

        template <typename C, typename = typename std::enable_if<std::is_arithmetic<C>::value, C>::type>
        inline friend std::ostream& operator<<(std::ostream& ostream, Matrix<C>& matrix);

    private:
        int m_Width, m_Height;
        T* m_Matrix;

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
                        if (m_SelectedBefore) {
                            m_SelectedBefore(ostream);
                        }
                        PrintCell(ostream, xPos, yPos);
                        if (m_SelectedAfter) {
                            m_SelectedAfter(ostream);
                        }
                    } else {
                        if (m_UnselectedBefore) {
                            m_UnselectedBefore(ostream);
                        }
                        PrintCell(ostream, xPos, yPos);
                        if (m_UnselectedAfter) {
                            m_UnselectedAfter(ostream);
                        }
                    }

                    ostream << WTUI_COLUMN_SEPERATOR;
                }
                ostream << WTUI_ROW_SEPERATOR;
            }
        }

        inline bool GetKeyInput(int& selectedX, int& selectedY) {
            switch (Keyboard::WaitForKey()) {
            case WTUI_RETURN:
            case WTUI_SPACE:
                return false;

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

    template <typename C, typename = typename std::enable_if<std::is_arithmetic<C>::value, C>::type>
    std::ostream& operator<<(std::ostream& ostream, WinTUI::Matrix<C>& matrix) {
        bool choosing = true;
        int selectedX = 0;
        int selectedY = 0;

        while (choosing) {
            Console::ClearScreen();

            matrix.PrintMatrix(ostream, selectedX, selectedY);
            choosing = matrix.GetKeyInput(selectedX, selectedY);
        }

        return ostream;
    }

}
