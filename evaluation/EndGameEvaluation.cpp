#include "EndGameEvaluation.h"
#include "../game/Game.h"

double EndGameEvaluation::operator()(const GameState& gameState, Color color, double timePassed) const {
    if (Game::getWinner(gameState) == color) {
        return 1;
    }
    if (Game::getWinner(gameState) == Color::EMPTY) {
        return 0;
    }
    return -1;
}

EndGameEvaluation::~EndGameEvaluation() {

}
