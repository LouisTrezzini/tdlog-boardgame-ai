#include "Board.h"

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

std::string Board::toString() const {
    std::string result = "";

    for(int i = 0; i < grid.size(); i++){
        result += std::to_string(i) + " | ";
        for(int j = 0; j < grid.size(); j++) {
            switch (pieceAt(i, j)) {
                case Color::EMPTY:
                    result += ". ";
                    break;
                case Color::WHITE:
                    result += "O ";
                    break;
                case Color::BLACK:
                    result += "X ";
                    break;
            }
        }
        result += "\n";
    }

    return result;
}

bool Board::operator==(const Board &board) const {
    if (board.getSize() != getSize()) {
        return false;
    }

    for (int i = 0; i < this->getSize(); i ++) {
        for (int j = 0; j < this->getSize(); j ++) {
            if (pieceAt(i,j) != board.pieceAt(i,j)) {
                return false;
            }
        }
    }
    return true;
}
