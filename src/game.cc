#include <iostream>
#include <iterator>
#include <string>

#include "game.h"

Game::Game(unsigned int sideLength) :
    sideLength( sideLength ),
    board(sideLength, (std::vector<Piece>(sideLength, Piece::E))),
    curState( State::P1PLAYS )
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
    if (row < 0 || col < 0 || row >= sideLength || col >= sideLength) return false;
    if (board[row][col] != Piece::E) return false;
    return true;
}

bool Game::rowWin(const Piece p, unsigned int row) const {
    for (unsigned int i = 0; i < sideLength; i++) {
        if (board[row][i] != p) return false;
    }
    return true;
}

bool Game::colWin(const Piece p, unsigned int col) const {
    for (unsigned int i = 0; i < sideLength; i++) {
        if (board[i][col] != p) return false;
    }
    return true;
}

bool Game::diagWin(const Piece p, const Move &move) const {
    if (move.row == move.col) {
        for (unsigned int i = 0; i < sideLength; i++) {
            if (board[i][i] != p) goto SECOND_DIAG;
        }
        return true;
    }

    SECOND_DIAG:;

    if (move.row + move.col == sideLength - 1) {
        for (unsigned int i = 0, j = sideLength - 1; i < sideLength && j >= 0; i++, j--) {
            if (board[i][j] != p) return false;
        }
        return true;
    }
    return false;
}

bool Game::winningMove(const Piece p, const Move &move) const {
    if (rowWin(p, move.row) || colWin(p, move.col) || diagWin(p, move)) return true;
    return false;
}

bool Game::gameFinished() const {
    return numValidMoves == sideLength * sideLength;
}

void Game::placeMove(const Move &move, const Piece p) {
    board[move.row][move.col] = p;
    numValidMoves += 1;
}

Game::State Game::doMove(const Move &move) {
    if (!validMove(move)) return State::INVALID;

    switch (curState) {
        case State::P1PLAYS:
            placeMove(move, Piece::X);
            if (winningMove(Piece::X, move)) curState = State::P1WINS;
            else if (gameFinished()) curState = State::TIE;
            else curState = State::P2PLAYS;
            return curState;
        case State::P2PLAYS:
            placeMove(move, Piece::O);
            if (winningMove(Piece::O, move)) curState = State::P2WINS;
            else if (gameFinished()) curState = State::TIE;
            else curState = State::P1PLAYS;
            return curState;
        default:
            return State::INVALID;
    }
}

std::string generateBorder(unsigned int lngth, char c) {
    std::string border = "";
    for (unsigned int i = 0; i < lngth; i++) {
        border += c;
    }
    return border;
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << generateBorder(game.sideLength * 2 + 1, '-') << std::endl;
    for (unsigned int i = 0; i < game.sideLength; i++) {
        for (unsigned int j = 0; j < game.sideLength; j++) {
            os << '|' << game.pieceToChar(game.board[i][j]);
        }
        os << '|' << std::endl;
        os << generateBorder(game.sideLength * 2 + 1, '-') << std::endl;
    }
    return os;
}
