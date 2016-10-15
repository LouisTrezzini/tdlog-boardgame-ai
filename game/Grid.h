//
// Created by till034 on 10/15/16.
//

#ifndef TDLOG_BOARDGAME_AI_GRID_H
#define TDLOG_BOARDGAME_AI_GRID_H

#include <cassert>
#include "Color.h"

/**
 * A class to manipulate the board's underlying grid
 */

class Grid {
    int _size;
    Color* tab;

public:
    Grid(int size) : _size(size) {
        assert(size >= 1);

        tab = new Color[size * size]();
    }

    Grid(const Grid& other) {
        _size = other._size;

        tab = new Color[_size * _size];
        for(int i = 0; i < _size * _size; i++){
            tab[i] = other.tab[i];
        }
    }

    Grid& operator=(const Grid& other) {
        delete[] tab;

        _size = other._size;

        tab = new Color[_size * _size];
        for(int i = 0; i < _size * _size; i++){
            tab[i] = other.tab[i];
        }

        return *this;
    }

    ~Grid(){
        delete[] tab;
    }

    int size() const {
        return _size;
    }

    Color operator()(int i, int j) const {
        return tab[i * _size + j];
    }

    Color& operator()(int i, int j) {
        return tab[i * _size + j];
    }
};


#endif //TDLOG_BOARDGAME_AI_GRID_H
