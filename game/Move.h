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

    Move() {

    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    static Move passing() {
        return Move(-1, -1);
    }

    bool isPassing() const {
        return x == -1 && y == -1;
    }

    bool operator==(const Move& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Move& other) const {
        return !operator==(other);
    }

    bool operator<(const Move& other) const {
        // Lexical order
        return x < other.x || x == other.x && y < other.y;
    }

    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

#endif //TDLOG_BOARDGAME_AI_MOVE_H
