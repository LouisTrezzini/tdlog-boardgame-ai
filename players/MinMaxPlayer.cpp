#include "MinMaxPlayer.h"
#include "../game/Game.h"


Move MinMaxPlayer::getAction(const GameState& gameState) const {
    return Game::getRandomMove(gameState);
}

MinMaxPlayer::~MinMaxPlayer() {

}




