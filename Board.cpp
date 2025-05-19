#pragma once

#include "Cell.h"
#include "Board.h"
#include <random>
#include <list>

Board::Board() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            m_grid[row][col] = Cell(row, col); // valeur = 0 par défaut
        }
    }
}

Board::Board(bool autoFill) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
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

    for (int i = 0; i < 3; i++) {
        if (m_grid[row][i].getValeur() == valeur || m_grid[i][col].getValeur() == valeur) {
            return false;
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
    for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
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



void Board::print() const {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            int val = m_grid[row][col].getValeur();
            if (val == 0)
                std::cout << ". ";
            else
                std::cout << val << " ";
        }
        std::cout << "\n";
    }
}