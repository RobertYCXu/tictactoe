#include <iostream>
#include <string>
#include <vector>

#include "move.h"

class Game {
    enum class Piece{ X, O, E };
    enum class State{ P1PLAYS, P2PLAYS, P1WINS, P2WINS, TIE };

    const std::string p1, p2;
    unsigned int sideLength;
    std::vector<std::vector<Piece>> board;
    unsigned int numValidMoves;
    State curState;

    char pieceToChar(const Piece p) const;
    bool validMove(const Move &move) const;
    void placeMove(const Move &move, const Piece p);
    bool winningMove(const Piece p, const Move &move) const;
    bool rowWin(const Piece p, unsigned int row) const;
    bool colWin(const Piece p, unsigned int col) const;
    bool diagWin(const Piece p, const Move &move) const;
    bool gameFinished() const;
    State getNextState(
        const Move &move,
        const Piece &piece,
        const State &winState,
        const State &defaultNextState
    ) const;

    public:
        Game(std::string p1, std::string p2, unsigned int sideLength);
        void processMove();
        bool over() const;
        void printBoard() const;

        friend std::ostream &operator<<(std::ostream &os, const Game &game);
};
