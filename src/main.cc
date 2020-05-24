#include <iostream>
#include <string>

#include "game.h"

int main() {
    std::string p1;
    std::string p2;
    int sideLength;

    std::cout << "Welcome to tic tac toe!" << std::endl;
    std::cout << "Player 1: " << std::endl;
    std::cin >> p1;
    std::cout << "Player 2: " << std::endl;
    std::cin >> p2;
    std::cout << "Size of board: " << std::endl;
    std::cin >> sideLength;

    if (sideLength <= 0) {
        std::cout << "Board length must be >= 0!" << std::endl;
        return 1;
    }

    Game game(p1, p2, sideLength);

    while (!game.over()) {
        game.printBoard();
        game.processMove();
    }
    game.printBoard();
}
