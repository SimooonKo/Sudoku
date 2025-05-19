#pragma once
#include "Cell.h"
#include "Board.h"
#include <algorithm>
#include <random>  

Cell::Cell() : m_row(0), m_col(0), m_valeur(0), noneTriedVal({1, 2, 3}) {}

Cell::Cell(int row, int col)
    : m_row(row), m_col(col), m_valeur(0), noneTriedVal({1, 2, 3}) {}


int Cell::getNextAvailableValue() {
    if (noneTriedVal.empty()) {
        return -1;
    }

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> dist(0, noneTriedVal.size() - 1);

    return noneTriedVal[dist(eng)];
}

bool Cell::hasAvailableValues() const {
    return !noneTriedVal.empty();
}

void Cell::removeTriedValue(int val) {
    noneTriedVal.erase(
        std::remove(noneTriedVal.begin(), noneTriedVal.end(), val),
        noneTriedVal.end()
    );
}

void Cell::resetAvailableValues() {
    noneTriedVal = {1, 2, 3};
}

Cell::~Cell() {}
