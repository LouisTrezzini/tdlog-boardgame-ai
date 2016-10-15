#include "Color.h"

Color colorOpponent(Color color) {
    switch(color) {
        case Color::BLACK:
            return Color::WHITE;

        case Color::WHITE:
            return Color::BLACK;

        case Color::EMPTY:
            return Color::EMPTY;
    }
}


std::ostream& operator<<(std::ostream& stream, const Color& color) {
    switch(color) {
        case Color::BLACK:
            stream << "BLACK";
            break;
        case Color::WHITE:
            stream << "WHITE";
            break;
        case Color::EMPTY:
            stream << "DRAW";
            break;
    }

    return stream;
}
