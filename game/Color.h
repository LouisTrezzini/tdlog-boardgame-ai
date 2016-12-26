#ifndef TDLOG_BOARDGAME_AI_COLOR_H
#define TDLOG_BOARDGAME_AI_COLOR_H

#include <iostream>

/**
 * A enumeration that represents the possible states from a grid element
 */

enum class Color : int {
    EMPTY = 0,
    WHITE,
    BLACK
};

Color colorOpponent(const Color& color);

std::ostream& operator<<(std::ostream& stream, const Color& color);

#endif //TDLOG_BOARDGAME_AI_COLOR_H
