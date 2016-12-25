#include "MobilityEvaluation.h"

double MobilityEvaluation::operator()(const GameState& gameState, Color color) const {
    return Game::getLegalMovesForColor(gameState, color).size();
}

MobilityEvaluation::~MobilityEvaluation() {

}