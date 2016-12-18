#include "MobilityEvaluation.h"

//FIXME
// Il faut que la mobilité dépende de la couleur !
double MobilityEvaluation::operator()(const GameState& gameState, Color color) const {
    return Game::getLegalMoves(gameState).size();
}

MobilityEvaluation::~MobilityEvaluation() {

}