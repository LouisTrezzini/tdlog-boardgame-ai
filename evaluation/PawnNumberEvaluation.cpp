#include "PawnNumberEvaluation.h"

double PawnNumberEvaluation::operator()(const GameState& gameState, Color color, double timePassed) const {
    return gameState.getBoard().getStonesByColor(color);
}

PawnNumberEvaluation::~PawnNumberEvaluation() {

}
