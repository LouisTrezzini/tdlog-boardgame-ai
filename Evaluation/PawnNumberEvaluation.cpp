#include "PawnNumberEvaluation.h"

double PawnNumberEvaluation::operator()(const GameState& gameState, Color color) const{
        return gameState.getBoard().getStonesByColor(color);
}

PawnNumberEvaluation::~PawnNumberEvaluation() {

}