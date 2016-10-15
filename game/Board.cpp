#include "Board.h"

std::ostream& operator<<(std::ostream& stream, const Board& board) {
    for(int i = 0; i < board.getSize(); i++){
        stream << i << " | ";
        for(int j = 0; j < board.getSize(); j++) {
            switch (board.pieceAt(i, j)) {
                case Color::EMPTY:
                    stream << ". ";
                    break;
                case Color::WHITE:
                    stream << "O ";
                    break;
                case Color::BLACK:
                    stream << "X ";
                    break;
            }
        }
        stream << std::endl;
    }

    return stream;
}


Board::Board(int size) : grid(size) {
    assert(size >= 4 && size % 2 == 0);

    grid(size / 2 - 1, size / 2 - 1) = Color::BLACK;
    grid(size / 2 - 1, size / 2) = Color::WHITE;
    grid(size / 2, size / 2 - 1) = Color::WHITE;
    grid(size / 2, size / 2) = Color::BLACK;

    blackStones = 2;
    whiteStones = 2;
}

void Board::placeStoneAt(int i, int j, Color color) {
    grid(i, j) = color;

    if(color == Color::WHITE) {
        whiteStones++;
    }
    else if (color == Color::BLACK) {
        blackStones++;
    }
}

void Board::flipStoneAt(int i, int j) {
    Color color = pieceAt(i, j);

    if(color == Color::WHITE) {
        whiteStones--;
        placeStoneAt(i, j, Color::BLACK);
    }
    else if (color == Color::BLACK) {
        blackStones--;
        placeStoneAt(i, j, Color::WHITE);
    }
}

void Board::display() const {
    std::cout << *this << std::endl;
}


