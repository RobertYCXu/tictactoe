#include <array>
#include <iostream>
#include <string>

#include "move.h"

class Game {
    enum class Piece{ X, O, E };
    const std::string p1, p2;
    std::array<std::array<Piece, 3>, 3> board;

    char pieceToChar(const Piece p) const;
    bool validMove(const Move &move) const;
    void placeMove(const Move &move, const Piece p);
    bool hasWinner(const Piece p) const;
    bool rowWin(const Piece p) const;
    bool colWin(const Piece p) const;
    bool diagWin(const Piece p) const;
    bool gameFinished() const;

    public:
        enum class State{ P1PLAYS, P2PLAYS, P1WINS, P2WINS, TIE, INVALID };
        Game(const std::string p1, const std::string p2);
        State getCurState() const;
        State doMove(const Move &move);
        bool over() const;

        friend std::ostream &operator<<(std::ostream &os, const Game &game);

    private:
        State curState;
};
