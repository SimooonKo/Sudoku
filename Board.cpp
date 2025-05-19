#pragma once

#include "Cell.h"
#include "Board.h"
#include <random>
#include <list>

Board::Board() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            m_grid[row][col] = Cell(row, col); 
        }
    }
}

Board::Board(bool autoFill) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            m_grid[row][col] = Cell(row, col);
        }
    }

    if (autoFill) {
        fillBoard();
    }
}

Cell& Board::getCell(int row, int col) {
    return m_grid[row][col];
}

void Board::setCell(Cell& cell, int row, int col){
    m_grid[row][col] = cell;
}

bool Board::IsAvalaible(Cell& cell, int valeur) {
    int row = cell.getRow();
    int col = cell.getCol();

    for (int i = 0; i < 9; i++) {
        if (m_grid[row][i].getValeur() == valeur || m_grid[i][col].getValeur() == valeur) {
            return false;
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if (m_grid[startRow + i][startCol + j].getValeur() == valeur){
                    return false;
            }
        }
    }
    
    return true;
}

bool Board::fillCell(Cell& cell) {
    while (cell.hasAvailableValues()) {
        int val = cell.getNextAvailableValue();
        if (IsAvalaible(cell, val))  {
            cell.setValeur(val);
            return true;
        }
        cell.removeTriedValue(val);
    }
    return false;
}


bool Board::fillBoard(){
    std::list<Cell*> cells;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cells.push_back(&getCell(i, j));
        }
    }
    std::list<Cell*>::iterator it = cells.begin();

    while (it != cells.end()) {
        Cell* current = *it;

        if (fillCell(*current)) {
            ++it; 
        } else {
            current->setValeur(0); 
            current->resetAvailableValues(); 
            if (it == cells.begin()) {
                return false; 
            }
            --it;
        }
    }
    return true; 
}


bool Board::isValid() {
    // Vérifie lignes
    for (int i = 0; i < 9; ++i) {
        std::array<bool, 10> seen = {};
        for (int j = 0; j < 9; ++j) {
            int val = m_grid[i][j].getValeur();
            if (seen[val]) return false;
            seen[val] = true;
        }
    }

    // Vérifie colonnes
    for (int j = 0; j < 9; ++j) {
        std::array<bool, 10> seen = {};
        for (int i = 0; i < 9; ++i) {
            int val = m_grid[i][j].getValeur();
            if (seen[val]) return false;
            seen[val] = true;
        }
    }

    // Vérifie blocs 3x3
    for (int blockRow = 0; blockRow < 3; ++blockRow) {
        for (int blockCol = 0; blockCol < 3; ++blockCol) {
            std::array<bool, 10> seen = {};
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int val = m_grid[blockRow * 3 + i][blockCol * 3 + j].getValeur();
                    if (seen[val]) return false;
                    seen[val] = true;
                }
            }
        }
    }

    return true;
}

void Board::removeValues(int count) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<int> dist(0, 8);
    int removed = 0;

    while (removed < count) {
        int row = dist(g);
        int col = dist(g);

        if (m_grid[row][col].getValeur() != 0) {
            m_grid[row][col].setValeur(0);
            ++removed;
        }
    }
}


void Board::print() const {
    for (int row = 0; row < 9; ++row) {
        if (row % 3 == 0)
            std::cout << "+-------+-------+-------+\n";

        for (int col = 0; col < 9; ++col) {
            if (col % 3 == 0) std::cout << "| ";

            int val = m_grid[row][col].getValeur();
            if (val == 0)
                std::cout << ". ";
            else
                std::cout << val << " ";
        }

        std::cout << "|\n";
    }
    std::cout << "+-------+-------+-------+\n";
}