#include <iostream>
#include <string>
#include <vector>

#include "move.h"

class Game {
    enum class Piece{ X, O, E };
    const std::string p1, p2;
    unsigned int sideLength;
    std::vector<std::vector<Piece>> board;
    unsigned int numValidMoves;

    char pieceToChar(const Piece p) const;
    bool validMove(const Move &move) const;
    void placeMove(const Move &move, const Piece p);
    bool winningMove(const Piece p, const Move &move) const;
    bool rowWin(const Piece p, unsigned int row) const;
    bool colWin(const Piece p, unsigned int col) const;
    bool diagWin(const Piece p) const;
    bool gameFinished() const;

    public:
        enum class State{ P1PLAYS, P2PLAYS, P1WINS, P2WINS, TIE, INVALID };
        Game(const std::string p1, const std::string p2, unsigned int sideLength);
        State getCurState() const;
        State doMove(const Move &move);
        bool over() const;

        friend std::ostream &operator<<(std::ostream &os, const Game &game);

    private:
        State curState;
};
