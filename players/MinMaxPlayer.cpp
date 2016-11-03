#include "MinMaxPlayer.h"
#include "../game/Game.h"

bool MinMaxOutput::operator<(const MinMaxOutput &other) {
    if (value < other.value) {
        return true;
    }
}

MinMaxOutput::MinMaxOutput(Move move, int value) {
    MinMaxOutput::move = move;
    MinMaxOutput::value = value;
}


Move MinMaxPlayer::getAction(const GameState& gameState) const {
    return Game::getRandomMove(gameState);
}

MinMaxPlayer::~MinMaxPlayer() {

}




