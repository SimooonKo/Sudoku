#pragma once
#include <vector>

class Cell {
    private :
        int m_row;
        int m_col;
        int m_valeur;
        std::vector<int> noneTriedVal;
    public :
        Cell();
        Cell(int row, int col);
        ~Cell();

        int getRow(){ return this->m_row; }
        int getCol(){ return this->m_col; }
        int getValeur() const { return this->m_valeur; }
        std::vector<int> getNoneTriedVal() const;
        int getNextAvailableValue();
        void removeTriedValue(int val);
        bool hasAvailableValues() const;
        void resetAvailableValues();

        void setRow(int row){ this->m_row = row;}
        void setCol(int col){ this->m_col = col;}
        void setValeur(int v){ this->m_valeur = v;}
};