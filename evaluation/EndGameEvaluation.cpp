#include "EndGameEvaluation.h"

double EndGameEvaluation::operator()(const GameState& gameState, Color color) const {
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