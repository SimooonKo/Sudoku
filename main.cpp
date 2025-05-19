#include <iostream>
#include "Board.h"

int main() {
    Board board;
    if (board.fillBoard()) {
        std::cout << "Sudoku valide généré :\n";
        board.print();
    } else {
        std::cout << "Échec de génération\n";
    }

    if (board.isValid()) {
    std::cout << "Grille valide ✅\n";
    } else {
    std::cout << "Grille invalide ❌\n";
    }

    board.removeValues(52); 
    std::cout << "Sudoku a jouer ; :\n";
    board.print();


    return 0;
}