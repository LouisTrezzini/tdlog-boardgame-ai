//
// Created by till034 on 10/15/16.
//

#ifndef TDLOG_BOARDGAME_AI_BOARD_H
#define TDLOG_BOARDGAME_AI_BOARD_H

#include <string>
#include "Grid.h"
#include "Color.h"

/*
 * A class that represents the game board
 */
class Board {
    int blackStones;
    int whiteStones;
    Grid grid;

public:
    Board(int size);

    Board(const Board &other) : grid(other.grid) {
        blackStones = other.blackStones;
        whiteStones = other.whiteStones;
    }

    Board& operator=(const Board& other) {
        blackStones = other.blackStones;
        whiteStones = other.whiteStones;
        grid = other.grid;

        return *this;
    }

    void placeStoneAt(int i, int j, Color color);

    void flipStoneAt(int i, int j);

    const Color& pieceAt(int i, int j) const {
        return grid(i, j);
    }

    int getBlackStones() const {
        return blackStones;
    }

    int getWhiteStones() const {
        return whiteStones;
    }

    int getStonesByColor(Color color) const{
        if (color == Color::WHITE) {
            return whiteStones;
        }
        return blackStones;
    };

    int getTotalStones() const {
        return whiteStones + blackStones;
    }

    bool isFull() const {
        return blackStones + whiteStones == grid.size() * grid.size();
    };

    int getSize() const {
        return grid.size();
    };

    std::string toString() const;

    bool operator==(const Board &board) const;

    inline bool inBounds(int i, int j) const {
        return 0 <= i &&  i < grid.size() && 0 <= j && j < grid.size();
    }
};

#endif //TDLOG_BOARDGAME_AI_BOARD_H
