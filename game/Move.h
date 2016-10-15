//
// Created by till034 on 10/15/16.
//

#ifndef TDLOG_BOARDGAME_AI_MOVE_H
#define TDLOG_BOARDGAME_AI_MOVE_H


class Move {
    int x;
    int y;

public:
    Move(int x, int y) : x(x), y(y) { };

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    bool isPassing() const{
        return x == -1 && y == -1;
    }
};

#endif //TDLOG_BOARDGAME_AI_MOVE_H
