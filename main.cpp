#include <iostream>
#include "Board.h"

int main() {
    Board board;
    if (board.fillBoard()) {
        std::cout << "Grille remplie :\n";
        board.print();
    } else {
        std::cout << "Échec du remplissage.\n";
    }
    return 0;
}