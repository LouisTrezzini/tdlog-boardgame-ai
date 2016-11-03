#include "MinMaxPlayer.h"
#include "../game/Game.h"

MinMaxOutput::MinMaxOutput(Move move, float value) {
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


Move MinMaxPlayer::getAction(const GameState& gameState) const {
    return Game::getRandomMove(gameState);
}

MinMaxPlayer::~MinMaxPlayer() {

}




