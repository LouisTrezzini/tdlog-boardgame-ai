#ifndef TDLOG_BOARDGAME_AI_MINMAXOUTPUT_H
#define TDLOG_BOARDGAME_AI_MINMAXOUTPUT_H

#include "../game/Move.h"

// Structure for outputing the right thing
struct MinMaxOutput {
    Move move;
    double value;

    MinMaxOutput(Move move, double value);
    void max(const MinMaxOutput &other);
    void min(const MinMaxOutput &other);
};

#endif //TDLOG_BOARDGAME_AI_MINMAXOUTPUT_H
