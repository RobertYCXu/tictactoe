#include <iostream>
#include <string>

#include "game.h"


int main() {
    std::string p1;
    std::string p2;

    std::cout << "Welcome to tic tac toe!" << std::endl;
    std::cout << "Player 1: " << std::endl;
    std::cin >> p1;
    std::cout << "Player 2: " << std::endl;
    std::cin >> p2;

    Game game(p1, p2);

    std::string prompt = " 's turn. Enter your move in row col format:";

    while (!game.over()) {
        std::cout << game << std::endl;

        if (game.getCurState() == Game::State::P1PLAYS) {
            std::cout << p1 << prompt << std::endl;
        }
        else {
            std::cout << p2 << prompt << std::endl;
        }

        int row, col;
        std::cin >> row;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            row = -1, col = -1;
        }

        std::cin >> col;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            row = -1, col = -1;
        }

        Move curMove = Move(row, col);
        Game::State nextState = game.doMove(curMove);

        if (nextState == Game::State::INVALID) {
            std::cout << "Invalid move!" << std::endl;
        }
    }

    std::cout << game;

    if (game.getCurState() == Game::State::P1WINS) {
        std::cout << p1 << " wins!" << std::endl;
    }
    else if (game.getCurState() == Game::State::P2WINS) {
        std::cout << p2 << " wins!" << std::endl;
    }
    else {
        std::cout << "Tie!" << std::endl;
    }
}
