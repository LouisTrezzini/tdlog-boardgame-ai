#include <random>
#include "RandomPlayer.h"
#include "../game/Game.h"


Move RandomPlayer::getAction(const GameState& gameState) const {
    return Game::getRandomMove(gameState);
}

RandomPlayer::~RandomPlayer() {

}




