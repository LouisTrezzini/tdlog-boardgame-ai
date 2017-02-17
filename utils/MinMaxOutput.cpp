#include "MinMaxOutput.h"

MinMaxOutput::MinMaxOutput(Move move, double value) {
    MinMaxOutput::move = move;
    MinMaxOutput::value = value;
}

void MinMaxOutput::max(const MinMaxOutput &other) {
    if (value < other.value) {
        value = other.value;
        move = other.move;
    }
}

void MinMaxOutput::min(const MinMaxOutput &other) {
    if (value > other.value) {
        value = other.value;
        move = other.move;
    }
}




