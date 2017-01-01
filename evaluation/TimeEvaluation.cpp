#include "TimeEvaluation.h"

double TimeEvaluation::operator()(const GameState& gameState, Color color, double timePassed) const {
    return - timePassed;
}

TimeEvaluation::~TimeEvaluation() {

}
