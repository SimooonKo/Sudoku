#pragma once

#include <vector>
#include<array>
#include <iostream>
#include <random>
#include "board.h"
#include "cell.h"


class Board {
    private :
        std::array<std::array<Cell, 3>, 3> m_grid; ///< Grille 3x3 de cellules
    public :
        Board();
        Board(bool autoFill);

        Cell& getCell(int row, int col);
        void setCell(Cell& cell, int row, int col);

        bool IsAvalaible(Cell&, int valeur);
        bool fillCell(Cell& cell);
        bool fillBoard();
        void print() const;
};
