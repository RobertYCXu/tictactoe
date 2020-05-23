#include <iostream>
#include <iterator>
#include <string>

#include "game.h"

Game::Game(std::string p1, std::string p2) :
    p1{ p1 },
    p2{ p2 },
    board{
        {{Piece::E, Piece::E, Piece::E},
        {Piece::E, Piece::E, Piece::E},
        {Piece::E, Piece::E, Piece::E}}
    },
    curState{ State::P1PLAYS }
{};

Game::State Game::getCurState() const {
    return curState;
}

bool Game::over() const {
    return curState == State::P1WINS || curState == State::P2WINS || curState == State::TIE;
}

char Game::pieceToChar(const Piece p) const {
    switch (p) {
        case Piece::X: return 'X';
        case Piece::O: return 'O';
        default: return ' ';
    }
}

bool Game::validMove(const Move &move) const {
    unsigned int row = move.row;
    unsigned int col = move.col;
    if (row < 0 || col < 0 || row >= board.size() || col >= board[0].size()) return false;
    if (board[row][col] != Piece::E) return false;
    return true;
}

bool Game::rowWin(const Piece p) const {
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != p) goto NEXTROW;
        }
        return true;
        NEXTROW:;
    }
    return false;
}

bool Game::colWin(const Piece p) const {
    for (unsigned int i = 0; i < board[0].size(); i++) {
        for (unsigned int j = 0; j < board.size(); j++) {
            if (board[j][i] != p) goto NEXTROW;
        }
        return true;
        NEXTROW:;
    }
    return false;
}

bool Game::diagWin(const Piece p) const {
    for (unsigned int i = 0; i < board.size(); i++) {
        if (board[i][i] != p) goto SECOND_DIAG;
    }
    return true;

    SECOND_DIAG:;

    for (unsigned int i = 0, j = board.size() - 1; i < board.size() && j >= 0; i++, j--) {
        if (board[i][j] != p) return false;
    }
    return true;
}

bool Game::hasWinner(const Piece p) const {
    if (rowWin(p) || colWin(p) || diagWin(p)) return true;
    return false;
}

bool Game::gameFinished() const {
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == Piece::E) return false;
        }
    }
    return true;
}

void Game::placeMove(const Move &move, const Piece p) {
    board[move.row][move.col] = p;
}

Game::State Game::doMove(const Move &move) {
    if (!validMove(move)) return State::INVALID;

    switch (curState) {
        case State::P1PLAYS:
            placeMove(move, Piece::X);
            if (hasWinner(Piece::X)) curState = State::P1WINS;
            else if (gameFinished()) curState = State::TIE;
            else curState = State::P2PLAYS;
            return curState;
        case State::P2PLAYS:
            placeMove(move, Piece::O);
            if (!gameFinished()) {
                curState = State::P1PLAYS;
            }
            if (hasWinner(Piece::O)) curState = State::P2WINS;
            else if (gameFinished()) curState = State::TIE;
            else curState = State::P1PLAYS;
            return curState;
        default:
            return State::INVALID;
    }
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "-------" << std::endl;
    for (unsigned int i = 0; i < game.board.size(); i++) {
        for (unsigned int j = 0; j < game.board[0].size(); j++) {
            os << '|' << game.pieceToChar(game.board[i][j]);
        }
        os << '|' << std::endl;
        os << "-------" << std::endl;
    }
    return os;
}
