#include "game.h"

Game::Game(std::string p1, std::string p2, unsigned int sideLength) :
    p1( p1 ),
    p2( p2 ),
    sideLength( sideLength ),
    board(sideLength, (std::vector<Piece>(sideLength, Piece::E))),
    numValidMoves( 0 ),
    curState( State::P1PLAYS )
{};

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

Game::State Game::getNextState(
    const Move &move,
    const Piece &piece,
    const State &winState,
    const State &defaultNextState
) const {
    if (winningMove(piece, move)) return winState;
    else if (gameFinished()) return State::TIE;
    else return defaultNextState;

}

void Game::processMove() {
    std::string prompt = "'s turn. Enter your move in row col format:";
    Piece curPiece = Piece::E;
    State winState = State::P1WINS;
    State defaultNextState = State::P2PLAYS;

    if (curState == Game::State::P1PLAYS) {
        std::cout << p1 << prompt << std::endl;
        curPiece = Piece::X;
    }
    else {
        std::cout << p2 << prompt << std::endl;
        curPiece = Piece::O;
        winState = State::P2WINS;
        defaultNextState = State::P1PLAYS;
    }

    unsigned int row, col;

    std::cin >> row;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        row = -1;
    }

    std::cin >> col;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        col = -1;
    }

    Move curMove = Move(row, col);

    if (!validMove(curMove)) {
        std::cout << "Invalid move!" << std::endl;
    }

    placeMove(curMove, curPiece);

    curState = getNextState(curMove, curPiece, winState, defaultNextState);

    if (curState == Game::State::P1WINS) {
        std::cout << p1 << " wins!" << std::endl;
    }
    else if (curState == Game::State::P2WINS) {
        std::cout << p2 << " wins!" << std::endl;
    }
    else if (curState == Game::State::TIE){
        std::cout << "Tie!" << std::endl;
    }
}

bool Game::over() const {
    return curState == State::P1WINS || curState == State::P2WINS || curState == State::TIE;
}

void Game::printBoard() const {
    std::cout << *this << std::endl;
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
